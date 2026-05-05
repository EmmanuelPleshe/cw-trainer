// SpeckIT CW Trainer - Arduino Entry Point
// Target: Arduino Uno R3 (ATmega328P)

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <hal.h>

// LCD pin configuration (Adafruit LCD Shield)
static const uint8_t LCD_RS = 8;
static const uint8_t LCD_EN = 9;
static const uint8_t LCD_D4 = 4;
static const uint8_t LCD_D5 = 5;
static const uint8_t LCD_D6 = 6;
static const uint8_t LCD_D7 = 7;

static LiquidCrystal g_lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
    // Initialize serial for debugging
    Serial.begin(9600);

    // Initialize LCD
    g_lcd.begin(16, 2);
    g_lcd.print("SpeckIT v0.1");
    g_lcd.setCursor(0, 1);
    g_lcd.print("CW Trainer");

    // Initialize HAL
    hal_lcd_init();
    hal_random_seed(analogRead(0));
}

void loop() {
    // Placeholder: Koch trainer logic will go here
    hal_delay_ms(1000);
}