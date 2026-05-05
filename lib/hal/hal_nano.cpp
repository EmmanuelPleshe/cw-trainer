#ifdef ARDUINO

#include "hal.h"
#include <Arduino.h>
#include <EEPROM.h>

// Pin definitions for Adafruit LCD shield + CW trainer
static const uint8_t PIN_TONE = 3;
static const uint8_t PIN_KEY  = 9;
static const uint8_t PIN_LED  = 13;

uint32_t hal_millis(void) { return millis(); }
uint32_t hal_micros(void) { return micros(); }
void hal_delay_ms(uint16_t ms) { delay(ms); }
void hal_delay_us(uint16_t us) { delayMicroseconds(us); }

void hal_tone_start(uint8_t pin, uint16_t freq_hz) { tone(pin, freq_hz); }
void hal_tone_stop(uint8_t pin) { noTone(pin); }
bool hal_tone_is_active(void) { return false; }

bool hal_button_read(uint8_t button_id) { return false; }
uint8_t hal_button_get(void) { return 0; }
bool hal_key_read(void) { return digitalRead(PIN_KEY) == LOW; }

void hal_lcd_init(void) {}
void hal_lcd_clear(void) {}
void hal_lcd_set_cursor(uint8_t col, uint8_t row) {}
void hal_lcd_print(const char* str) {}
void hal_lcd_write_char(char c) {}
void hal_lcd_backlight(bool on) {}

uint8_t hal_eeprom_read(uint16_t addr) { return EEPROM.read(addr); }
void hal_eeprom_write(uint16_t addr, uint8_t val) { EEPROM.write(addr, val); }
void hal_eeprom_update(uint16_t addr, uint8_t val) { EEPROM.update(addr, val); }

uint16_t hal_random(uint16_t max) { return random(max); }
void hal_random_seed(uint16_t seed) { randomSeed(seed); }

void hal_led_set(bool on) { digitalWrite(PIN_LED, on ? HIGH : LOW); }
void hal_serial_print(const char* str) { Serial.print(str); }
void hal_serial_println(const char* str) { Serial.println(str); }

#endif