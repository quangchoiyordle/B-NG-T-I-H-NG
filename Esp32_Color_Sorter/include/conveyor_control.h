#ifndef CONVEYOR_CONTROL_H
#define CONVEYOR_CONTROL_H

#include <Arduino.h>
#include "config.h"

// This assumes an active-LOW relay module. Verify the relay polarity before use.
inline void initConveyor()
{
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);
}

inline void startConveyor()
{
    digitalWrite(RELAY_PIN, LOW);
}

inline void stopConveyor()
{
    digitalWrite(RELAY_PIN, HIGH);
}

#endif
