#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include "config.h"

extern Servo servoRed;
extern Servo servoGreen;
extern Servo servoBlue;

inline void initServos()
{
    servoRed.attach(SERVO_RED_PIN);
    servoGreen.attach(SERVO_GREEN_PIN);
    servoBlue.attach(SERVO_BLUE_PIN);

    servoRed.write(0);
    servoGreen.write(0);
    servoBlue.write(0);
}

inline void triggerPushRed()
{
    Serial.println("Sorting RED");
    servoRed.write(90);
    delay(800);
    servoRed.write(0);
}

inline void triggerPushGreen()
{
    Serial.println("Sorting GREEN");
    servoGreen.write(90);
    delay(800);
    servoGreen.write(0);
}

inline void triggerPushBlue()
{
    Serial.println("Sorting BLUE");
    servoBlue.write(90);
    delay(800);
    servoBlue.write(0);
}

#endif
