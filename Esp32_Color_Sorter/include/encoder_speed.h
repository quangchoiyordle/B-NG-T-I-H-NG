#ifndef ENCODER_SPEED_H
#define ENCODER_SPEED_H

#include <Arduino.h>
#include "config.h"

void IRAM_ATTR pulseCounterISR();

inline void initEncoder()
{
    pinMode(ENCODER_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), pulseCounterISR, RISING);
    lastTimeCheck = millis();
}

inline void calculateSpeed()
{
    const unsigned long now = millis();
    const unsigned long elapsed = now - lastTimeCheck;
    if (elapsed < 500) {
        return;
    }

    noInterrupts();
    const long pulses = encoderPulseCount;
    encoderPulseCount = 0;
    interrupts();

    currentRPM = (static_cast<float>(pulses) * 60000.0f) /
                 (static_cast<float>(ENCODER_PULSES_PER_REV) *
                  static_cast<float>(elapsed));
    lastTimeCheck = now;
}

#endif
