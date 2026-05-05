#include <unity.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// === HAL MOCK IMPLEMENTATION ===

// Mock state
static uint32_t g_mock_millis = 0;
static char g_lcd_buffer[2][16] = {{0}};
static uint8_t g_eeprom[1024] = {0};
static uint16_t g_random_value = 42;

// HAL function implementations for testing
uint32_t hal_millis(void) { return g_mock_millis; }
uint32_t hal_micros(void) { return g_mock_millis * 1000; }
void hal_delay_ms(uint16_t ms) { g_mock_millis += ms; }
void hal_delay_us(uint16_t us) { g_mock_millis += (us / 1000); }

void hal_tone_start(uint8_t pin, uint16_t freq_hz) { (void)pin; (void)freq_hz; }
void hal_tone_stop(uint8_t pin) { (void)pin; }
bool hal_tone_is_active(void) { return false; }

bool hal_button_read(uint8_t button_id) { (void)button_id; return false; }
uint8_t hal_button_get(void) { return 0; }
bool hal_key_read(void) { return false; }

void hal_lcd_init(void) { memset(g_lcd_buffer, ' ', sizeof(g_lcd_buffer)); }
void hal_lcd_clear(void) { memset(g_lcd_buffer, ' ', sizeof(g_lcd_buffer)); }
void hal_lcd_set_cursor(uint8_t col, uint8_t row) { (void)col; (void)row; }
void hal_lcd_print(const char* str) { (void)str; }
void hal_lcd_write_char(char c) { (void)c; }
void hal_lcd_backlight(bool on) { (void)on; }

uint8_t hal_eeprom_read(uint16_t addr) { return (addr < 1024) ? g_eeprom[addr] : 0; }
void hal_eeprom_write(uint16_t addr, uint8_t val) { if (addr < 1024) g_eeprom[addr] = val; }
void hal_eeprom_update(uint16_t addr, uint8_t val) { hal_eeprom_write(addr, val); }

uint16_t hal_random(uint16_t max) {
    return (uint16_t)(g_random_value++ % max);
}
void hal_random_seed(uint16_t seed) { g_random_value = seed; }

void hal_led_set(bool on) { (void)on; }
void hal_serial_print(const char* str) { (void)str; }
void hal_serial_println(const char* str) { (void)str; }

// Test helpers
const char* test_lcd_get_row(uint8_t row) {
    return g_lcd_buffer[row % 2];
}
void test_advance_time(uint32_t ms) {
    g_mock_millis += ms;
}
void test_eeprom_reset(void) {
    memset(g_eeprom, 0, sizeof(g_eeprom));
}

// === TESTS ===

void setUp(void) {
    hal_lcd_init();
    hal_random_seed(42);
}

void tearDown(void) {
}

void test_hal_millis_starts_at_zero(void) {
    TEST_ASSERT_EQUAL_UINT32(0, hal_millis());
}

void test_hal_advance_time(void) {
    test_advance_time(1000);
    TEST_ASSERT_EQUAL_UINT32(1000, hal_millis());
}

void test_hal_lcd_clear(void) {
    hal_lcd_clear();
    const char* row = test_lcd_get_row(0);
    TEST_ASSERT_EQUAL_INT8(' ', row[0]);
}

void test_hal_random_range(void) {
    uint16_t r = hal_random(10);
    TEST_ASSERT_TRUE(r < 10);
}

void test_hal_eeprom_read_write(void) {
    test_eeprom_reset();
    hal_eeprom_write(0, 42);
    TEST_ASSERT_EQUAL_UINT8(42, hal_eeprom_read(0));
}

// Main function required by Unity
void setUp(void);
void tearDown(void);
void test_hal_millis_starts_at_zero(void);
void test_hal_advance_time(void);
void test_hal_lcd_clear(void);
void test_hal_random_range(void);
void test_hal_eeprom_read_write(void);

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    UNITY_BEGIN();
    RUN_TEST(test_hal_millis_starts_at_zero);
    RUN_TEST(test_hal_advance_time);
    RUN_TEST(test_hal_lcd_clear);
    RUN_TEST(test_hal_random_range);
    RUN_TEST(test_hal_eeprom_read_write);
    UNITY_END();
    return 0;
}