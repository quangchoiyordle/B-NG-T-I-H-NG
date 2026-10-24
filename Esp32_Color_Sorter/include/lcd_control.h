#ifndef LCD_CONTROL_H
#define LCD_CONTROL_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "config.h"

extern LiquidCrystal_I2C lcd;

inline void initLCD()
{
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("COLOR SORTER");
    lcd.setCursor(0, 1);
    lcd.print("ESP32 PLATFORMIO");
    delay(1500);
    lcd.clear();
}

inline void updateLCD(int redCount, int greenCount, int blueCount, float speed)
{
    lcd.setCursor(0, 0);
    lcd.print("R:");
    lcd.print(redCount);
    lcd.print(" G:");
    lcd.print(greenCount);
    lcd.print(" B:");
    lcd.print(blueCount);
    lcd.print("   ");

    lcd.setCursor(0, 1);
    lcd.print("RPM:");
    lcd.print(static_cast<int>(speed));
    lcd.print("           ");
}

#endif
