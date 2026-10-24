#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include <Arduino.h>
#include "config.h"

inline void initColorSensor()
{
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(SENSOR_OUT, INPUT);

    // TCS3200 output frequency scaling: 20%.
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
}

inline unsigned long getAveragePulse(bool s2State, bool s3State)
{
    digitalWrite(S2, s2State);
    digitalWrite(S3, s3State);
    delay(10);

    constexpr int samples = 5;
    unsigned long total = 0;
    int validSamples = 0;

    for (int i = 0; i < samples; ++i) {
        const unsigned long pulse = pulseIn(SENSOR_OUT, LOW, 50000);
        if (pulse > 0) {
            total += pulse;
            ++validSamples;
        }
    }

    return validSamples == 0 ? 0 : total / validSamples;
}

inline int scaleColorReading(unsigned long raw, int rawMin, int rawMax)
{
    if (raw == 0 || rawMin == rawMax) {
        return 0;
    }

    const long scaled = map(static_cast<long>(raw), rawMax, rawMin, 0, 255);
    return constrain(static_cast<int>(scaled), 0, 255);
}

inline TargetColor readAndProcessColor()
{
    // TCS3200 filter selection: red LOW/LOW, green HIGH/HIGH, blue LOW/HIGH.
    const unsigned long rawR = getAveragePulse(LOW, LOW);
    const unsigned long rawG = getAveragePulse(HIGH, HIGH);
    const unsigned long rawB = getAveragePulse(LOW, HIGH);

    const int r = scaleColorReading(rawR, redMin, redMax);
    const int g = scaleColorReading(rawG, greenMin, greenMax);
    const int b = scaleColorReading(rawB, blueMin, blueMax);

    TargetColor detected = NONE;
    if (r > g + 30 && r > b + 30 && r > 90) {
        detected = RED;
    } else if (g > r + 25 && g > b + 25 && g > 90) {
        detected = GREEN;
    } else if (b > r + 25 && b > g + 25 && b > 90) {
        detected = BLUE;
    }

    if (detected != NONE) {
        Serial.printf(
            "RAW R:%lu G:%lu B:%lu | RGB R:%d G:%d B:%d | color: %s\n",
            rawR,
            rawG,
            rawB,
            r,
            g,
            b,
            detected == RED ? "RED" : detected == GREEN ? "GREEN" : "BLUE");
    }

    return detected;
}

#endif
