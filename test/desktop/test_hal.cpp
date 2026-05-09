#include <unity.h>
#include "hal.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

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

void test_hal_micros(void) {
    uint32_t before = hal_micros();
    test_advance_time(5);
    TEST_ASSERT_EQUAL_UINT32(before + 5000, hal_micros());
}

void test_hal_delay_us(void) {
    uint32_t before = hal_millis();
    hal_delay_us(2500);
    TEST_ASSERT_EQUAL_UINT32(before + 2, hal_millis());
}

void test_hal_tone_start_stop(void) {
    hal_tone_start(3, 440);
    TEST_ASSERT_TRUE(hal_tone_is_active());
    hal_tone_stop(3);
    TEST_ASSERT_FALSE(hal_tone_is_active());
}

void test_hal_tone_is_active(void) {
    TEST_ASSERT_FALSE(hal_tone_is_active());
    hal_tone_start(5, 880);
    TEST_ASSERT_TRUE(hal_tone_is_active());
}

void test_hal_button_read(void) {
    TEST_ASSERT_FALSE(hal_button_read(0));
    TEST_ASSERT_FALSE(hal_button_read(1));
}

void test_hal_button_get(void) {
    TEST_ASSERT_EQUAL_UINT8(0, hal_button_get());
}

void test_hal_key_read(void) {
    TEST_ASSERT_FALSE(hal_key_read());
}

void test_hal_lcd_clear(void) {
    hal_lcd_clear();
    const char* row = test_lcd_get_row(0);
    TEST_ASSERT_EQUAL_INT8(' ', row[0]);
}

void test_hal_lcd_set_cursor(void) {
    hal_lcd_set_cursor(3, 1);
    hal_lcd_write_char('X');
    const char* row = test_lcd_get_row(1);
    TEST_ASSERT_EQUAL_INT8('X', row[3]);
}

void test_hal_lcd_print(void) {
    hal_lcd_set_cursor(0, 0);
    hal_lcd_print("hi");
    const char* row = test_lcd_get_row(0);
    TEST_ASSERT_EQUAL_INT8('h', row[0]);
    TEST_ASSERT_EQUAL_INT8('i', row[1]);
}

void test_hal_lcd_write_char(void) {
    hal_lcd_set_cursor(5, 0);
    hal_lcd_write_char('A');
    const char* row = test_lcd_get_row(0);
    TEST_ASSERT_EQUAL_INT8('A', row[5]);
}

void test_hal_lcd_backlight(void) {
    hal_lcd_backlight(true);
    hal_lcd_backlight(false);
}

void test_hal_eeprom_read_write(void) {
    test_eeprom_reset();
    hal_eeprom_write(0, 42);
    TEST_ASSERT_EQUAL_UINT8(42, hal_eeprom_read(0));
}

void test_hal_eeprom_update(void) {
    test_eeprom_reset();
    hal_eeprom_update(10, 99);
    TEST_ASSERT_EQUAL_UINT8(99, hal_eeprom_read(10));
}

void test_hal_random_range(void) {
    uint16_t r = hal_random(10);
    TEST_ASSERT_TRUE(r < 10);
}

void test_hal_random_seed_determinism(void) {
    hal_random_seed(123);
    uint16_t a = hal_random(100);
    hal_random_seed(123);
    uint16_t b = hal_random(100);
    TEST_ASSERT_EQUAL_UINT16(a, b);
}

void test_hal_led_set(void) {
    hal_led_set(true);
    hal_led_set(false);
}

void test_hal_serial_print(void) {
    hal_serial_print("test");
    hal_serial_println("test");
}

// Forward declarations for Unity runner
void setUp(void);
void tearDown(void);
void test_hal_millis_starts_at_zero(void);
void test_hal_advance_time(void);
void test_hal_micros(void);
void test_hal_delay_us(void);
void test_hal_tone_start_stop(void);
void test_hal_tone_is_active(void);
void test_hal_button_read(void);
void test_hal_button_get(void);
void test_hal_key_read(void);
void test_hal_lcd_clear(void);
void test_hal_lcd_set_cursor(void);
void test_hal_lcd_print(void);
void test_hal_lcd_write_char(void);
void test_hal_lcd_backlight(void);
void test_hal_eeprom_read_write(void);
void test_hal_eeprom_update(void);
void test_hal_random_range(void);
void test_hal_random_seed_determinism(void);
void test_hal_led_set(void);
void test_hal_serial_print(void);

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    UNITY_BEGIN();
    RUN_TEST(test_hal_millis_starts_at_zero);
    RUN_TEST(test_hal_advance_time);
    RUN_TEST(test_hal_micros);
    RUN_TEST(test_hal_delay_us);
    RUN_TEST(test_hal_tone_start_stop);
    RUN_TEST(test_hal_tone_is_active);
    RUN_TEST(test_hal_button_read);
    RUN_TEST(test_hal_button_get);
    RUN_TEST(test_hal_key_read);
    RUN_TEST(test_hal_lcd_clear);
    RUN_TEST(test_hal_lcd_set_cursor);
    RUN_TEST(test_hal_lcd_print);
    RUN_TEST(test_hal_lcd_write_char);
    RUN_TEST(test_hal_lcd_backlight);
    RUN_TEST(test_hal_eeprom_read_write);
    RUN_TEST(test_hal_eeprom_update);
    RUN_TEST(test_hal_random_range);
    RUN_TEST(test_hal_random_seed_determinism);
    RUN_TEST(test_hal_led_set);
    RUN_TEST(test_hal_serial_print);
    UNITY_END();
    return 0;
}
