#ifdef PIO_ENV_DESKTOP

#include "hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Mock state
static uint32_t g_mock_millis = 0;
static bool g_tone_active = false;
static uint16_t g_tone_freq = 0;
static char g_lcd_buffer[2][16] = {{0}};
static uint8_t g_lcd_cursor_col = 0;
static uint8_t g_lcd_cursor_row = 0;
static uint8_t g_eeprom[1024] = {0};

uint32_t hal_millis(void) { return g_mock_millis; }
uint32_t hal_micros(void) { return g_mock_millis * 1000; }
void hal_delay_ms(uint16_t ms) { g_mock_millis += ms; }
void hal_delay_us(uint16_t us) { g_mock_millis += (us / 1000); }

void hal_tone_start(uint8_t pin, uint16_t freq_hz) {
    (void)pin;
    g_tone_active = true;
    g_tone_freq = freq_hz;
}
void hal_tone_stop(uint8_t pin) {
    (void)pin;
    g_tone_active = false;
}
bool hal_tone_is_active(void) { return g_tone_active; }

bool hal_button_read(uint8_t button_id) {
    (void)button_id;
    return false;
}
uint8_t hal_button_get(void) { return 0; }
bool hal_key_read(void) { return false; }

void hal_lcd_init(void) {
    for (int r = 0; r < 2; r++)
        for (int c = 0; c < 16; c++)
            g_lcd_buffer[r][c] = ' ';
}
void hal_lcd_clear(void) {
    for (int r = 0; r < 2; r++)
        for (int c = 0; c < 16; c++)
            g_lcd_buffer[r][c] = ' ';
}
void hal_lcd_set_cursor(uint8_t col, uint8_t row) {
    g_lcd_cursor_col = col % 16;
    g_lcd_cursor_row = row % 2;
}
void hal_lcd_print(const char* str) {
    for (const char* p = str; *p && g_lcd_cursor_col < 16; p++) {
        g_lcd_buffer[g_lcd_cursor_row][g_lcd_cursor_col++] = *p;
    }
}
void hal_lcd_write_char(char c) {
    if (g_lcd_cursor_col < 16)
        g_lcd_buffer[g_lcd_cursor_row][g_lcd_cursor_col++] = c;
}
void hal_lcd_backlight(bool on) {
    (void)on;
}

uint8_t hal_eeprom_read(uint16_t addr) {
    return (addr < 1024) ? g_eeprom[addr] : 0;
}
void hal_eeprom_write(uint16_t addr, uint8_t val) {
    if (addr < 1024) g_eeprom[addr] = val;
}
void hal_eeprom_update(uint16_t addr, uint8_t val) {
    hal_eeprom_write(addr, val);
}

uint16_t hal_random(uint16_t max) {
    return (uint16_t)(rand() % max);
}
void hal_random_seed(uint16_t seed) {
    srand(seed);
}

void hal_led_set(bool on) {
    (void)on;
}
void hal_serial_print(const char* str) { printf("%s", str); }
void hal_serial_println(const char* str) { printf("%s\n", str); }

// --- Test helpers (not part of public HAL API) ---
const char* test_lcd_get_row(uint8_t row) {
    return g_lcd_buffer[row % 2];
}
void test_advance_time(uint32_t ms) {
    g_mock_millis += ms;
}
void test_eeprom_reset(void) {
    for (int i = 0; i < 1024; i++) g_eeprom[i] = 0;
}

#endif