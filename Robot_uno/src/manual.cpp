#include "manual.h"

void manual()
{
    while (true)
    {
        char command;

        while (!Serial.available())
            ;
        if (Serial.available())
        {
            command = Serial.read();
        }

        if (command == '1')
        {
            forward();
        }
        else if (command == '2')
        {
            backward();
        }
        else if (command == '3')
        {
            analogWrite(RMOTOR_vel, 150);
            analogWrite(LMOTOR_vel, 150);
            digitalWrite(MOTOR_R1, HIGH);
            digitalWrite(MOTOR_R2, LOW);
            digitalWrite(MOTOR_L1, LOW);
            digitalWrite(MOTOR_L2, HIGH);
        }
        else if (command == '4')
        {
            analogWrite(RMOTOR_vel, 150);
            analogWrite(LMOTOR_vel, 150);
            digitalWrite(MOTOR_R1, LOW);
            digitalWrite(MOTOR_R2, HIGH);
            digitalWrite(MOTOR_L1, HIGH);
            digitalWrite(MOTOR_L2, LOW);
        }
        else if (command == '-')
        {
            toggle_mode();
            break;
        }
        else
        {
            Serial.println("Invalid command");
        }
        delay(100);
        off();
    }
}