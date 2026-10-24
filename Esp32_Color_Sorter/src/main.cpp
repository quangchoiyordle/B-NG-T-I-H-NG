#include <Arduino.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>

#include "config.h"
#include "color_sensor.h"
#include "ir_sensor.h"
#include "servo_control.h"
#include "encoder_speed.h"
#include "conveyor_control.h"
#include "alert_system.h"
#include "lcd_control.h"

// Starting calibration values; tune these using readings from your sensor.
int redMin = 30;
int redMax = 250;
int greenMin = 30;
int greenMax = 250;
int blueMin = 30;
int blueMax = 250;

TargetColor currentDetectedColor = NONE;
volatile long encoderPulseCount = 0;
unsigned long lastTimeCheck = 0;
float currentRPM = 0.0f;

Servo servoRed;
Servo servoGreen;
Servo servoBlue;
LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);

namespace {
int countRed = 0;
int countGreen = 0;
int countBlue = 0;
unsigned long lastLcdUpdate = 0;
}

void IRAM_ATTR pulseCounterISR()
{
    ++encoderPulseCount;
}

void setup()
{
    Serial.begin(115200);

    initColorSensor();
    initIRSensors();
    initServos();
    initEncoder();
    initConveyor();
    initAlerts();
    initLCD();

    startConveyor();
    updateLCD(countRed, countGreen, countBlue, currentRPM);
    Serial.println("ESP32 color sorter ready");
}

void loop()
{
    calculateSpeed();

    const TargetColor detectedColor = readAndProcessColor();
    if (detectedColor != NONE) {
        currentDetectedColor = detectedColor;
    }

    if (currentDetectedColor == RED && isObjectAtRed()) {
        triggerPushRed();
        triggerSuccessBeep();
        ++countRed;
        currentDetectedColor = NONE;
    } else if (currentDetectedColor == GREEN && isObjectAtGreen()) {
        triggerPushGreen();
        triggerSuccessBeep();
        ++countGreen;
        currentDetectedColor = NONE;
    } else if (currentDetectedColor == BLUE && isObjectAtBlue()) {
        triggerPushBlue();
        triggerSuccessBeep();
        ++countBlue;
        currentDetectedColor = NONE;
    }

    const unsigned long now = millis();
    if (now - lastLcdUpdate >= 250) {
        updateLCD(countRed, countGreen, countBlue, currentRPM);
        lastLcdUpdate = now;
    }

    delay(20);
}
