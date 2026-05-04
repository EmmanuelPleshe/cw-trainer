# Data Model: 002-pio-project

## HAL Interface

The Hardware Abstraction Layer provides a C-style API for all hardware operations.

### Time Functions

```c
// Get milliseconds since startup
uint32_t hal_millis(void);

// Get microseconds since startup
uint32_t hal_micros(void);

// Blocking delay
void hal_delay_ms(uint16_t ms);
void hal_delay_us(uint16_t us);
```

### Tone/Audio

```c
// Start tone on pin (PWM)
void hal_tone_start(uint8_t pin, uint16_t freq_hz);

// Stop tone
void hal_tone_stop(uint8_t pin);

// Check if tone is active
bool hal_tone_is_active(void);
```

### Input

```c
// Read button state (true = pressed)
// button_id: 0=left, 1=up, 2=down, 3=right, 4=select
bool hal_button_read(uint8_t button_id);

// Blocking button read with debounce
uint8_t hal_button_get(void);

// Read CW key/paddle state
bool hal_key_read(void);
```

### Output - LCD

```c
// Initialize LCD
void hal_lcd_init(void);

// Clear display
void hal_lcd_clear(void);

// Set cursor position
void hal_lcd_set_cursor(uint8_t col, uint8_t row);

// Print string
void hal_lcd_print(const char* str);

// Write single char
void hal_lcd_write_char(char c);

// Control backlight
void hal_lcd_backlight(bool on);
```

### EEPROM

```c
// Read byte from EEPROM
uint8_t hal_eeprom_read(uint16_t addr);

// Write byte to EEPROM
void hal_eeprom_write(uint16_t addr, uint8_t val);

// Write only if changed
void hal_eeprom_update(uint16_t addr, uint8_t val);
```

### Random

```c
// Random 0 to max-1
uint16_t hal_random(uint16_t max);

// Seed random generator
void hal_random_seed(uint16_t seed);
```

### Debug

```c
// LED control
void hal_led_set(bool on);

// Serial print (uses F() macro in nano)
void hal_serial_print(const char* str);
void hal_serial_println(const char* str);
```

## Mock State (Desktop Testing)

The desktop HAL maintains internal mock state:

```c
static uint32_t g_mock_millis;
static bool g_tone_active;
static uint16_t g_tone_freq;
static char g_lcd_buffer[2][16];
static uint8_t g_eeprom[1024];
```

## Testing Helpers (Desktop Only)

```c
// Get current mock time
const char* test_lcd_get_row(uint8_t row);

// Advance mock time
void test_advance_time(uint32_t ms);

// Reset EEPROM
void test_eeprom_reset(void);
```

## Implementation Locations

| File | Purpose |
|------|---------|
| lib/hal/hal.h | Interface definition |
| lib/hal/hal_nano.cpp | Arduino implementation |
| lib/hal/hal_desktop.cpp | Mock implementation |