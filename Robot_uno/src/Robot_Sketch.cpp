#include <Arduino.h>
#include "Robot_config.h"
#include "manual.h"
#include "l298_driver.h"
#include <agv.h>
#include <Wire.h>

bool mode = true; // true for autonomous mode and false for manual mode

void setup()
{
  Serial.println("Initializing>>>>");

  Serial.begin(9600);
  Wire.begin();
  pinMode(MOTOR_R1, OUTPUT);
  pinMode(MOTOR_R2, OUTPUT);
  pinMode(MOTOR_L1, OUTPUT);
  pinMode(MOTOR_L2, OUTPUT);
  pinMode(RMOTOR_vel, OUTPUT);
  pinMode(LMOTOR_vel, OUTPUT);
  // pinMode(center_ir,INPUT);
  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);
  pinMode(EXTLEFT_IR, INPUT);
  pinMode(EXTRIGHT_IR, INPUT);
  analogWrite(RMOTOR_vel, 100);
  analogWrite(LMOTOR_vel, 100);

  initMpu();
}

void loop()
{
  if (mode)
  {
    agv();
  }
  else
  {
    manual();
  }
}

void toggle_mode()
{
  mode = !mode;
  if (mode)
  {
    Serial.println("Switching to Autonomous mode");
  }
  else
  {
    Serial.println("Switching to Manual mode");
  }
}
