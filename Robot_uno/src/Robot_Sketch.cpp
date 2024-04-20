#include <Arduino.h>

#define motor_R1 5    // Right motor pole 1
#define motor_R2 4    // Right motor pole 2
#define motor_L1 3    // left motor pole 1
#define motor_L2 2    // left motor pole 2
#define Rmotor_vel 9  // Right motor speed
#define Lmotor_vel 10 // Right motor speed
// #define center_ir 11     //SS3
#define LEFT_IR A2     // ss2
#define RIGHT_IR A3    // ss4
#define extLEFT_IR A1  // ss1
#define extRIGHT_IR A4 // ss5

int TURN_90_DELAY = 880;
int TURN_180_DELAY = 1800;
int TURN_FROWARD_DELAY = 210;

int left_ir, right_ir, extleft_ir, extright_ir; // Define variables which used to store digital inputs values
int Intersection_mask = 0, start_mask = 0, mark1 = 0, mark2 = 0, serial_mask = 0;
int x = 0, y = 0, ox = 0, oy = 0, nx = 0, ny = 0, pos = 0;
int pxy[2], prev[2];
// boolean tx_mode=false;
int income[2];
int state = 0; // orientation state (1=Forward, 2=Reverse, 3=Right, 4=Left)Zero is initial state
int cordinates = 0;
// function prototypes

void inertia();
void forward();
void reverse();
void Tleft();
void Tright();
void off();
void Tleft90();
void Tright90();
void Tright180();
void getvalues();
void compare();
void getxy();
void calc();
void orientation();
void moveY();
void moveX();
void moveY_neg();
void moveX_neg();
void setDelay();
void reset();

void setup()
{
  Serial.begin(9600);
  pinMode(motor_R1, OUTPUT);
  pinMode(motor_R2, OUTPUT);
  pinMode(motor_L1, OUTPUT);
  pinMode(motor_L2, OUTPUT);
  pinMode(Rmotor_vel, OUTPUT);
  pinMode(Lmotor_vel, OUTPUT);
  // pinMode(center_ir,INPUT);
  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);
  pinMode(extLEFT_IR, INPUT);
  pinMode(extRIGHT_IR, INPUT);
  analogWrite(Rmotor_vel, 100);
  analogWrite(Lmotor_vel, 100);
  Serial.println("Initializing>>>>");
}
void loop()
{

  if (serial_mask == 0)
  {
    while (!Serial.available())
      ;
    if (Serial.available())
    {
      cordinates = Serial.parseInt();
      income[0] = cordinates / 10;
      income[1] = cordinates % 10;
    }
    serial_mask = 1;
  }
  Serial.print("Cordinates: ");
  Serial.println(cordinates);
  if (cordinates == 0)
  {
    reset();
  }
  else if (cordinates == 1000)
  {
    setDelay();
  }
  else
  {
    getxy();
    calc();
  }
}

void setDelay()
{
  Serial.println("Setting Delay>>>>");
  delay(100);
  Serial.println("Set Turn 90 Delay>>>>");
  while (!Serial.available())
    ;
  if (Serial.available())
  {
    TURN_90_DELAY = Serial.parseInt();
  }
  Serial.println("Set Turn 180 Delay>>>>");
  while (!Serial.available())
    ;
  if (Serial.available())
  {
    TURN_180_DELAY = Serial.parseInt();
  }
  Serial.println("Set Turn Forward Delay>>>>");
  while (!Serial.available())
    ;
  if (Serial.available())
  {
    TURN_FROWARD_DELAY = Serial.parseInt();
  }
  Serial.println("Delay Has Been Set>>>>");
  serial_mask = 0;
  delay(100);
}

void reset()
{
  Serial.println("Resetting>>>>");
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
  cordinates = 0;
  serial_mask = 0;
  Serial.println("Reset Done>>>>");
}

void inertia()
{
  analogWrite(Rmotor_vel, 100);
  analogWrite(Lmotor_vel, 100);
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, HIGH);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, HIGH);
  delay(100);
}
void forward()
{
  analogWrite(Rmotor_vel, 85);
  analogWrite(Lmotor_vel, 85);
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, HIGH);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, HIGH);
}

void reverse()
{
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
}

void Tright()
{
  analogWrite(Rmotor_vel, 130);
  analogWrite(Lmotor_vel, 110);
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, HIGH);
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
  // delay(100);
}
void Tleft()
{
  analogWrite(Rmotor_vel, 110);
  analogWrite(Lmotor_vel, 130);
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, HIGH);
  // delay(100);
}
void off()
{
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, LOW);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, LOW);
}
void Tleft90()
{
  forward();
  delay(TURN_FROWARD_DELAY);
  off();
  delay(200);
  analogWrite(Rmotor_vel, 120);
  analogWrite(Lmotor_vel, 120);
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, HIGH);
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
  delay(TURN_90_DELAY);
}
void Tright90()
{
  forward();
  delay(TURN_FROWARD_DELAY);
  off();
  delay(200);
  analogWrite(Rmotor_vel, 110);
  analogWrite(Lmotor_vel, 110);
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, HIGH);
  delay(TURN_90_DELAY);
}

void Tright180()
{
  forward();
  delay(TURN_FROWARD_DELAY);
  off();
  analogWrite(Rmotor_vel, 120);
  analogWrite(Lmotor_vel, 120);
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, HIGH);
  delay(TURN_180_DELAY);
}

void getvalues()
{
  // If value is equal to 0 means Black and other 1 means White
  extleft_ir = digitalRead(extLEFT_IR);
  left_ir = digitalRead(LEFT_IR);
  // c=digitalRead(center_ir);
  right_ir = digitalRead(RIGHT_IR);
  extright_ir = digitalRead(extRIGHT_IR);
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
    if ((y > 0 && x < 0 && mark1 == 1) || (y < 0 && x > 0 && mark1 == 1))
    {
      pos--;
    }
    else if ((x < 0 && y < 0 && mark2 == 1) || (y < 0 && x == 0) || (x < 0 && y == 0))
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
  if (state == 2)
  { // reverse Orientation
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