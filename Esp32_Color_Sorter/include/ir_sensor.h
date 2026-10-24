#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <Arduino.h>
#include "config.h"

inline void initIRSensors()
{
    pinMode(IR_RED_PIN, INPUT);
    pinMode(IR_GREEN_PIN, INPUT);
    pinMode(IR_BLUE_PIN, INPUT);
}

// These LM393 modules are assumed to output LOW when an object is detected.
inline bool isObjectAtRed()
{
    return digitalRead(IR_RED_PIN) == LOW;
}

inline bool isObjectAtGreen()
{
    return digitalRead(IR_GREEN_PIN) == LOW;
}

inline bool isObjectAtBlue()
{
    return digitalRead(IR_BLUE_PIN) == LOW;
}

#endif
