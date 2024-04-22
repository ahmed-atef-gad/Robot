#include "l298_driver.h"

void inertia()
{
    analogWrite(RMOTOR_vel, 100);
    analogWrite(LMOTOR_vel, 100);
    digitalWrite(MOTOR_R1, LOW);
    digitalWrite(MOTOR_R2, HIGH);
    digitalWrite(MOTOR_L1, LOW);
    digitalWrite(MOTOR_L2, HIGH);
    delay(100);
}
void forward()
{
    analogWrite(RMOTOR_vel, 85);
    analogWrite(LMOTOR_vel, 85);
    digitalWrite(MOTOR_R1, LOW);
    digitalWrite(MOTOR_R2, HIGH);
    digitalWrite(MOTOR_L1, LOW);
    digitalWrite(MOTOR_L2, HIGH);
}
void backward()
{
    analogWrite(RMOTOR_vel, 85);
    analogWrite(LMOTOR_vel, 85);
    digitalWrite(MOTOR_R1, HIGH);
    digitalWrite(MOTOR_R2, LOW);
    digitalWrite(MOTOR_L1, HIGH);
    digitalWrite(MOTOR_L2, LOW);
}

void reverse()
{
    digitalWrite(MOTOR_R1, HIGH);
    digitalWrite(MOTOR_R2, LOW);
    digitalWrite(MOTOR_L1, HIGH);
    digitalWrite(MOTOR_L2, LOW);
}

void Tright()
{
    analogWrite(RMOTOR_vel, 130);
    analogWrite(LMOTOR_vel, 110);
    digitalWrite(MOTOR_R1, LOW);
    digitalWrite(MOTOR_R2, HIGH);
    digitalWrite(MOTOR_L1, HIGH);
    digitalWrite(MOTOR_L2, LOW);
    // delay(100);
}
void Tleft()
{
    analogWrite(RMOTOR_vel, 110);
    analogWrite(LMOTOR_vel, 130);
    digitalWrite(MOTOR_R1, HIGH);
    digitalWrite(MOTOR_R2, LOW);
    digitalWrite(MOTOR_L1, LOW);
    digitalWrite(MOTOR_L2, HIGH);
    // delay(100);
}
void off()
{
    digitalWrite(MOTOR_R1, LOW);
    digitalWrite(MOTOR_R2, LOW);
    digitalWrite(MOTOR_L1, LOW);
    digitalWrite(MOTOR_L2, LOW);
}
