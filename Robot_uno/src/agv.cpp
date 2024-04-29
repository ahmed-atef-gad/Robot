#include "agv.h"

int left_ir, right_ir, extleft_ir, extright_ir; // Define variables which used to store digital inputs values
int Intersection_mask = 0, start_mask = 0, mark1 = 0, mark2 = 0, serial_mask = 0;
int x = 0, y = 0, ox = 0, oy = 0, nx = 0, ny = 0, pos = 0;
int pxy[2], prev[2];
int income[2];
int state = 0; // orientation state (1=Forward, 2=Reverse, 3=Right, 4=Left)Zero is initial state
int command = 0;
float targetAngle = 0;
int TURN_FROWARD_DELAY = 320;
int TURN_SPEED = 150;
int offset = 10;

MPU6050 mpu6050(Wire);

void agv()
{
    while (true)
    {

        mpu6050.update();
        if (serial_mask == 0)
        {
            while (!Serial.available())
                ;
            if (Serial.available())
            {
                command = Serial.parseInt();
                income[0] = command / 10;
                income[1] = command % 10;
            }
            serial_mask = 1;
        }
        Serial.print("Command: ");
        Serial.println(command);
        if (command == -1)
        {
            reset();
        }
        else if (command == -2)
        {
            Serial.print("(");
            Serial.print(ox);
            Serial.print(",");
            Serial.print(oy);
            Serial.println(")");
        }
        else if (command == -3)
        {
            Serial.print("set turn delay: ");
            delay(200);
            while (!Serial.available())
                ;
            if (Serial.available())
            {
                TURN_FROWARD_DELAY = Serial.parseInt();
            }
            Serial.println(TURN_FROWARD_DELAY);
            command = -1;
        }
        else if (command == -100)
        {
            toggle_mode();
            command = -1;
            break;
        }
        else
        {
            getxy();
            calc();
        }
    }
}
void initMpu()
{
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
    Serial.println("\nRobot is ready to go  (●'◡'●)");
}

void reset()
{
    Serial.println("Resetting>>>>");
    delay(200);
    ox = 0;
    oy = 0;
    x = 0;
    y = 0;
    nx = 0;
    ny = 0;
    pos = 0;
    pxy[0] = 0;
    pxy[1] = 0;
    prev[0] = 0;
    prev[1] = 0;
    command = 0;
    serial_mask = 0;
    Serial.println("Reset Done>>>>");
    delay(200);
}

void compare()
{
    if (extleft_ir == 1 && left_ir == 1 && right_ir == 1 && extright_ir == 1)
    {

        if (start_mask == 0)
        {
            inertia();
            start_mask = 1;
        }
        forward();
    }
    if ((extleft_ir == 1 && left_ir == 0 && right_ir == 1 && extright_ir == 1) || (extleft_ir == 0 && left_ir == 1 && right_ir == 1 && extright_ir == 1))
    {
        Tleft();
    }
    if ((extleft_ir == 1 && left_ir == 1 && right_ir == 0 && extright_ir == 1) || (extleft_ir == 1 && left_ir == 1 && right_ir == 1 && extright_ir == 0))
    {
        Tright();
    }

    if (extleft_ir == 0 && left_ir == 0 && right_ir == 0 && extright_ir == 0 && Intersection_mask == 0)
    {
        off();
        delay(100);
        Intersection_mask = 1;
        if ((y > 0 && x < 0 /*&& mark1 == 1*/) || (y < 0 && x > 0 /*&& mark1 == 1*/))
        {
            pos--;
        }
        else if ((x < 0 && y < 0 /*&& mark2 == 1*/) || (y < 0 && x == 0) || (x < 0 && y == 0))
        {
            pos--;
        }
        else
            pos++;

        // inertia();
        forward();
    }
    if (extleft_ir == 1 && extright_ir == 1)
    {
        Intersection_mask = 0;
    }
}

void getxy()
{
    nx = income[0];
    ny = income[1];

    Serial.print("nx: ");
    Serial.print(nx);
    Serial.print(" ny: ");
    Serial.println(ny);
}
void calc()
{
    x = nx - ox;
    y = ny - oy;

    if (x == 0 && y == 0)
    {
        Serial.println("Already at the destination");
        Serial.print("(");
        Serial.print(ox);
        Serial.print(",");
        Serial.print(oy);
        Serial.println(")");

        delay(200);
        serial_mask = 0;
        return;
    }

    if (x > 0 && y > 0)
    {
        moveY();
        state = 3;
        orientation();
        moveX();
        state = 4;
        orientation();
        ox = nx;
        oy = ny;
        serial_mask = 0;
        return;
    }
    else if (x < 0 && y < 0)
    {
        mark2 = 1;
        getvalues();
        state = 2;
        orientation();
        moveY_neg();
        state = 3;
        orientation();
        moveX_neg();
        state = 3;
        orientation();
        mark2 = 0;
        ox = nx;
        oy = ny;
        serial_mask = 0;
        return;
    }
    else if (x == 0 && y > 0)
    {
        getvalues();
        moveY();
        ox = nx;
        oy = ny;
        serial_mask = 0;
        return;
    }
    else if (x == 0 && y < 0)
    {
        getvalues();
        state = 2;
        orientation();
        moveY_neg();
        state = 2;
        orientation();
        ox = nx;
        oy = ny;
        serial_mask = 0;
        return;
    }
    else if (y == 0 && x > 0)
    {
        getvalues();
        state = 3;
        orientation();
        moveX();
        state = 4;
        orientation();
        ox = nx;
        oy = ny;
        serial_mask = 0;
        return;
    }
    else if (y == 0 && x < 0)
    {
        getvalues();
        state = 4;
        orientation();
        moveX_neg();
        state = 3;
        orientation();
        ox = nx;
        oy = ny;
        serial_mask = 0;
        return;
    }
    else if (x > 0 && y < 0)
    {
        getvalues();
        state = 3;
        orientation();
        moveX();
        state = 3;
        orientation();
        mark1 = 1;
        moveY_neg();
        state = 2;
        orientation();
        mark1 = 0;
        ox = nx;
        oy = ny;
        serial_mask = 0;
        return;
    }
    else if (x < 0 && y > 0)
    {
        getvalues();
        moveY();
        state = 4;
        orientation();
        mark1 = 1;
        moveX_neg();
        state = 3;
        orientation();
        mark1 = 0;
        ox = nx;
        oy = ny;
        serial_mask = 0;
        return;
    }
}

void orientation()
{
    mpu6050.update();
    if (state == 2)
    { // reverse Orientation
        // delay(TURN_FROWARD_DELAY);
        // off();
        // delay(200);
        // targetAngle = fmod(mpu6050.getAngleZ() - 90.0 , 360.0);
        // targetAngle = mpu6050.getAngleZ() - 90.0;
        // while (targetAngle < mpu6050.getAngleZ())
        // {
        Tright180();
        off();
        state = 0;
    }
    else if (state == 3)
    {
        // inertia();
        Tright90();
        off();
        state = 0;
    }
    else if (state == 4)
    {
        // inertia();
        Tleft90();
        off();
        state = 0;
    }
}

void moveY()
{
    while (true)
    {
        pxy[1] = oy + pos;
        if (pxy[1] != prev[1])
        {
            Serial.print("(");
            Serial.print(pxy[0]);
            Serial.print(",");
            Serial.print(pxy[1]);
            Serial.println(")");
        }
        prev[1] = pxy[1];
        if (y > pos)
        {
            getvalues();
            compare();
        }
        else if (y == pos)
        {
            off();
            pos = 0;
            break;
        }
    }
    pos = 0;
}

void moveX()
{
    while (true)
    {
        pxy[0] = ox + pos;
        if (pxy[0] != prev[0])
        {
            Serial.print("(");
            Serial.print(pxy[0]);
            Serial.print(",");
            Serial.print(pxy[1]);
            Serial.println(")");
        }
        prev[0] = pxy[0];
        if (x > pos)
        {
            getvalues();
            compare();
        }
        else if (x == pos)
        {
            off();
            pos = 0;
            break;
        }
    }
    pos = 0;
}

void moveY_neg()
{
    while (true)
    {
        pxy[1] = pos + oy;
        if (pxy[1] != prev[1])
        {
            Serial.print("(");
            Serial.print(pxy[0]);
            Serial.print(",");
            Serial.print(pxy[1]);
            Serial.println(")");
        }
        prev[1] = pxy[1];
        if (y < pos)
        {
            getvalues();
            compare();
        }
        else if (y == pos)
        {
            off();
            pos = 0;
            break;
        }
    }
    pos = 0;
}

void moveX_neg()
{
    while (true)
    {
        pxy[0] = pos + ox;
        if (pxy[0] != prev[0])
        {
            Serial.print("(");
            Serial.print(pxy[0]);
            Serial.print(",");
            Serial.print(pxy[1]);
            Serial.println(")");
        }
        prev[0] = pxy[0];
        if (x < pos)
        {
            getvalues();
            compare();
        }
        else if (x == pos)
        {
            off();
            pos = 0;
            break;
        }
    }
    pos = 0;
}

void getvalues()
{
    left_ir = digitalRead(LEFT_IR);
    right_ir = digitalRead(RIGHT_IR);
    extleft_ir = digitalRead(EXTLEFT_IR);
    extright_ir = digitalRead(EXTRIGHT_IR);
    mpu6050.update();
}

void Tleft90()
{
    forward();
    delay(TURN_FROWARD_DELAY);
    off();
    delay(200);
    // targetAngle = fmod(mpu6050.getAngleZ() + 90.0, 360.0);
    targetAngle = mpu6050.getAngleZ() + (90.0 - offset);
    while (targetAngle > mpu6050.getAngleZ())
    {
        analogWrite(RMOTOR_vel, TURN_SPEED);
        analogWrite(LMOTOR_vel, TURN_SPEED);
        digitalWrite(MOTOR_R1, HIGH);
        digitalWrite(MOTOR_R2, LOW);
        digitalWrite(MOTOR_L1, LOW);
        digitalWrite(MOTOR_L2, HIGH);
        getvalues();
    }
}

void Tright90()
{
    forward();
    delay(TURN_FROWARD_DELAY);
    off();
    delay(200);
    targetAngle = mpu6050.getAngleZ() - (90.0 - offset);
    while (targetAngle < mpu6050.getAngleZ())
    {
        analogWrite(RMOTOR_vel, TURN_SPEED);
        analogWrite(LMOTOR_vel, TURN_SPEED);
        digitalWrite(MOTOR_R1, LOW);
        digitalWrite(MOTOR_R2, HIGH);
        digitalWrite(MOTOR_L1, HIGH);
        digitalWrite(MOTOR_L2, LOW);
        getvalues();
    }
}

void Tright180()
{
    forward();
    delay(TURN_FROWARD_DELAY);
    off();
    delay(200);
    targetAngle = mpu6050.getAngleZ() - (180.0 - 2*offset);
    while (targetAngle < mpu6050.getAngleZ())
    {
        analogWrite(RMOTOR_vel, TURN_SPEED);
        analogWrite(LMOTOR_vel, TURN_SPEED);
        digitalWrite(MOTOR_R1, LOW);
        digitalWrite(MOTOR_R2, HIGH);
        digitalWrite(MOTOR_L1, HIGH);
        digitalWrite(MOTOR_L2, LOW);
        getvalues();
    }
}
