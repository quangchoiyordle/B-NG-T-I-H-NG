#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// TCS3200 color sensor
#define S0 25
#define S1 33
#define S2 27
#define S3 26
#define SENSOR_OUT 14

// LM393 infrared sensors (digital outputs)
#define IR_RED_PIN 32
#define IR_GREEN_PIN 35
#define IR_BLUE_PIN 34

// Sorting servos
#define SERVO_RED_PIN 18
#define SERVO_GREEN_PIN 19
#define SERVO_BLUE_PIN 23

// Conveyor, encoder, buzzer and status LED
#define ENCODER_PIN 16
#define RELAY_PIN 5
#define BUZZER_PIN 4
#define LED_PIN 2

// LCD1602 I2C address; common values are 0x27 and 0x3F.
#define LCD_ADDR 0x27

constexpr uint16_t ENCODER_PULSES_PER_REV = 20;

extern int redMin;
extern int redMax;
extern int greenMin;
extern int greenMax;
extern int blueMin;
extern int blueMax;

enum TargetColor {
    NONE,
    RED,
    GREEN,
    BLUE
};

extern TargetColor currentDetectedColor;
extern volatile long encoderPulseCount;
extern unsigned long lastTimeCheck;
extern float currentRPM;

#endif
