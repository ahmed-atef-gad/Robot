#ifndef L298_DRIVER_H
#define L298_DRIVER_H

#include <Arduino.h>
#include "Robot_config.h"

void inertia();
void forward();
void reverse();
void Tleft();
void Tright();
void off();
void backward();

#endif
