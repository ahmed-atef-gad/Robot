#ifndef AVG_H
#define AVG_H

#include "l298_driver.h"
#include <MPU6050_tockn.h>

void getvalues();
void compare();
void getxy();
void calc();
void orientation();
void moveY();
void moveX();
void moveY_neg();
void moveX_neg();
void reset();
void agv();
void Tleft90();
void Tright90();
void Tright180();
void initMpu();

#endif