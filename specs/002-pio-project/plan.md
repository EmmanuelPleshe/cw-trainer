# Implementation Plan: 002-pio-project

**Branch**: `002-pio-project` | **Date**: 2026-05-03 | **Spec**: [spec.md](./spec.md)
**Input**: Feature specification from `/specs/002-pio-project/spec.md`

## Summary

Create PlatformIO project structure for SpeckIT CW Trainer. Establish three-tier testing (native, simavr, Wokwi) per Constitution Addendum A. Target Arduino Uno (ATmega328P) with HAL abstraction enabling TDD.

## Technical Context

**Language/Version**: C++17 (Arduino), Bash scripts | **Primary Dependencies**: PlatformIO 6.x, Unity test framework
**Storage**: N/A | **Testing**: PlatformIO test (desktop + nano environments)
**Target Platform**: Arduino Uno (ATmega328P) + Linux desktop (native testing) | **Project Type**: Embedded project with TDD
**Performance Goals**: Compile <60s, native test <10s | **Constraints**: 2KB SRAM, 31.5KB flash (Constitution limits)
**Scale/Scope**: Single developer machine setup

## Constitution Check

| Gate | Status | Notes |
|------|--------|-------|
| I. Hardware-First | PASS | Target Uno R3, ATmega328P constraints noted |
| II. Memory Discipline | PASS | Constitution limits built into design |
| III. Layered Architecture | PASS | HAL abstraction required |
| IV. Test-First | PASS | Three-tier testing per Addendum A |
| V. Code Quality | PASS | No String, no malloc, C-style APIs |

**Result**: GATE PASS

## Project Structure

### Documentation (this feature)

```text
specs/002-pio-project/
├── plan.md              # This file
├── research.md          # Phase 0 (platformio setup, unity integration)
├── data-model.md       # Phase 1 (HAL interface design)
├── quickstart.md       # Phase 1 (how to build/test)
└── tasks.md            # Phase 2 (/speckit-tasks output)
```

### Source Code (repository root)

Per Constitution Addendum A:

```text
cw-trainer/
├── lib/                    # Shared logic - tested at Tier 1
│   └── hal/                # Hardware Abstraction Layer
│       ├── hal.h           # Interface definition
│       ├── hal_nano.cpp    # Arduino implementation
│       └── hal_desktop.cpp # Mock for native tests
├── src/
│   ├── nano/               # Arduino entry point
│   │   └── main.cpp
│   └── desktop/            # Native test runner
│       └── main.cpp
├── test/
│   ├── desktop/            # Tier 1 unit tests
│   └── wokwi/              # Tier 3 scenarios
├── simavr/                # Tier 2 scripts
├── wokwi/                 # Wokwi config
│   └── diagram.json
└── platformio.ini         # Build configuration
```

**Structure Decision**: PlatformIO project with dual environments (nano = Arduino, desktop = native tests). HAL in lib/hal/ per Constitution.

---

## Phase 0: Research

**Research Tasks**:

1. **PlatformIO Desktop Testing**: Verify PlatformIO native environment works for testing without Arduino headers
   - Check platformio.ini [env:desktop] configuration
   - Verify Unity test framework integration

2. **HAL Design for Testing**: How to abstract hardware calls for mockable interface
   - Define hal.h API (time, gpio, tone, lcd, eeprom)
   - Implement hal_desktop.cpp with mock state

3. **Wokwi Integration**: Verify Wokwi CLI can run scenario tests
   - Check diagram.json structure for Arduino Uno
   - Verify test/wokwi/ scenario format

**Output**: `research.md`

## Phase 1: Design & Contracts

**HAL Interface Design** (data-model.md):

```c
// hal.h - Key functions to abstract
uint32_t hal_millis(void);
void hal_delay_ms(uint16_t ms);
void hal_tone_start(uint8_t pin, uint16_t freq_hz);
void hal_tone_stop(uint8_t pin);
bool hal_button_read(uint8_t button_id);
void hal_lcd_clear(void);
void hal_lcd_set_cursor(uint8_t col, uint8_t row);
void hal_lcd_print(const char* str);
uint8_t hal_eeprom_read(uint16_t addr);
void hal_eeprom_write(uint16_t addr, uint8_t val);
```

**PlatformIO Configuration** (platformio.ini):
- [env:nano]: Arduino Uno, atmega328p, LiquidCrystal library
- [env:desktop]: native, no framework, Unity test runner
- Common: src_filter, lib_deps

**Quickstart Guide** (quickstart.md):
- `pio run` — build for Arduino
- `pio run -e desktop` — build native
- `pio test -e desktop` — run Tier 1 tests

---

## Complexity Tracking

> Not applicable - no constitution violations.

---

## Next Steps

After this plan:
1. Run `/speckit-tasks` to generate implementation tasks
2. Create platformio.ini
3. Create lib/hal/ with hal.h and implementations
4. Create test structure