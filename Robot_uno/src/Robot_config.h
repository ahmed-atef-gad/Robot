#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

#define MOTOR_R1 5    // Right motor pole 1
#define MOTOR_R2 4    // Right motor pole 2
#define MOTOR_L1 3    // left motor pole 1
#define MOTOR_L2 2    // left motor pole 2
#define RMOTOR_vel 9  // Right motor speed
#define LMOTOR_vel 10 // Right motor speed
// #define center_ir 11     //SS3
#define LEFT_IR A2     // ss2
#define RIGHT_IR A3    // ss4
#define EXTLEFT_IR A1  // ss1
#define EXTRIGHT_IR A0 // ss5
// #define SDA A4
// #define SCL A5

void toggle_mode();

#endif