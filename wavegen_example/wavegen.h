#ifndef WAVEGEN_H
#define WAVEGEN_H
#include "arduino.h"

#define SINESHAPE 0
#define PULSESHAPE 1
#define RAMPSHAPE 2
#define DCSHAPE 3

int get_sample(uint8_t, float, float, uint8_t);

#endif // WAVEGEN_H

