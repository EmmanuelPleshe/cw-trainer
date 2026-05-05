#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <stdbool.h>

// --- Time ---
uint32_t hal_millis(void);
uint32_t hal_micros(void);
void hal_delay_ms(uint16_t ms);
void hal_delay_us(uint16_t us);

// --- Tone / Audio ---
void hal_tone_start(uint8_t pin, uint16_t freq_hz);
void hal_tone_stop(uint8_t pin);
bool hal_tone_is_active(void);

// --- Input ---
bool hal_button_read(uint8_t button_id);
uint8_t hal_button_get(void);
bool hal_key_read(void);

// --- Output ---
void hal_lcd_init(void);
void hal_lcd_clear(void);
void hal_lcd_set_cursor(uint8_t col, uint8_t row);
void hal_lcd_print(const char* str);
void hal_lcd_write_char(char c);
void hal_lcd_backlight(bool on);

// --- EEPROM ---
uint8_t hal_eeprom_read(uint16_t addr);
void hal_eeprom_write(uint16_t addr, uint8_t val);
void hal_eeprom_update(uint16_t addr, uint8_t val);

// --- Random ---
uint16_t hal_random(uint16_t max);
void hal_random_seed(uint16_t seed);

// --- Debug ---
void hal_led_set(bool on);
void hal_serial_print(const char* str);
void hal_serial_println(const char* str);

#endif