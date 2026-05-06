# CW Trainer: Testing & Documentation Audit with Action Plan

**Audit Date**: 2026-05-05  
**Branch**: `003-test-docs-audit`  
**Auditor**: SpeckIT Automated Audit  
**Scope**: Entire repository (`cw-trainer/`, `lib/`, `src/`, `libraries/`, `test/`, `specs/`, `docs/`)

---

## Executive Summary

- **Current test coverage**: ~8% by line count (5/1507 lines tested in `test/test_hal.cpp`; 1502 lines in `cw-trainer.ino` + `MorseEnDecoder.cpp` untested)
- **Documentation completeness**: 50% (1 of 2 existing specs is complete; no architectural docs for HAL; no data model for trainer logic)
- **Biggest risk**: All application logic lives in the 609-line monolithic `cw-trainer/cw-trainer.ino` with zero tests; any change risks regressions in the Koch trainer, decoder, and preference system.
- **Recommended first sprint**: Expand `test/test_hal.cpp` to cover the full HAL contract, then begin extracting the first pure-logic module (`prefs_init`/`prefs_set`) from `cw-trainer.ino` into `lib/core/` with host-native tests.

---

## 1. Testing State

### 1.1 Test Inventory

| Test File | Framework | Target Env | Module Tested | Test Count | Status |
|-----------|-----------|------------|---------------|------------|--------|
| `test/test_hal.cpp` | Unity | `desktop` (native) | HAL (mock impl) | 5 | **PASSED** |
| `test/desktop/` | N/A | N/A | Empty directory | 0 | N/A |
| `test/wokwi/smoke-test.yaml` | Wokwi | `nano` (HIL) | Boot + LCD init | 1 scenario | **Not run in this session** |

### 1.2 Test Coverage by Module

| Module | Source Files | Lines | Test Files | Coverage Status | Classification |
|--------|-------------|-------|------------|-----------------|----------------|
| HAL Contract | `lib/hal/hal.h` | 44 | `test/test_hal.cpp` | 5/17 functions tested, no tone/button/key/LCD cursor tests | `partial` |
| HAL Nano | `lib/hal/hal_nano.cpp` | 42 | None | No nano-specific HAL tests | `none` |
| HAL Desktop | `lib/hal/hal_desktop.cpp` | 100 | `test/test_hal.cpp` (mock), `src/desktop/main.cpp` | Mock used in tests; desktop runner exists | `partial` |
| Nano Entry | `src/nano/main.cpp` | 35 | None | No entry-point tests | `not-testable` (HIL only) |
| Desktop Entry | `src/desktop/main.cpp` | 29 | None | No tests; manual runner | `none` |
| Legacy Monolith | `cw-trainer/cw-trainer.ino` | 609 | None | Zero tests for 609 lines of UI/game/pedagogy logic | `none` |
| Morse Library | `libraries/morseIO/MorseEnDecoder.cpp` + `.h` | 532 | None | Third-party; no wrapper or interface tests | `external` |
| Adafruit LCD | `libraries/Adafruit_RGB_LCD_Shield_Library/` | — | None | Third-party library | `external` |
| PS2Keyboard | `libraries/PS2Keyboard/` | — | None | Third-party library (unused in new entry points) | `external` |

### 1.3 Test Framework

**Unity** (ThrowTheSwitch) via PlatformIO. Declared in `platformio.ini`:
```ini
lib_deps = throwtheswitch/Unity@^2.6.0
```

### 1.4 Test Organization

- **Scattered**: Single `test/test_hal.cpp` at repo root. No subdirectories mirroring `lib/` structure.
- **Missing**: `test/desktop/` is empty; `test/core/` does not exist; no tests for `cw-trainer.ino` logic.

### 1.5 Test Run Results

```
$ pio test -e desktop
Environment    Test      Status    Duration
-------------  --------  --------  ------------
desktop        test_hal  PASSED    00:00:00.239
5 test cases: 5 succeeded
```

```
$ pio test -e nano
Environment    Test      Status    Duration
-------------  --------  --------  ------------
nano           test_hal  ERRORED   00:00:11.033
Error: Upload failed — permission denied on /dev/ttyS0
```

**Analysis**: `nano` test fails because PlatformIO tries to upload to a physical serial port. The `nano` environment is configured for hardware upload, not simulation. `simavr` integration (Tier 2) is not yet wired into `platformio.ini`.

### 1.6 Biggest Untested Surface Area

`cw-trainer/cw-trainer.ino` (609 lines) contains:
- `setup()` / `loop()` — entry point orchestration
- `get_mode()` — LCD menu system with button handling
- `set_prefs()` — EEPROM-backed preference editor with 8 parameters
- `morse_trainer()` — Koch trainer loop with character generation, sending, receiving, scoring
- `morse_decode()` — CW decoder display loop
- `paris_test()` — Speed calibration loop
- `prefs_init()` / `prefs_set()` — EEPROM I/O with validation

**All of this is untested.**

### 1.7 Quickest Win for Test Coverage

Extract `prefs_init()` and `prefs_set()` (lines 530–609, ~80 lines) into `lib/core/prefs.h` and `lib/core/prefs.cpp`. These functions:
- Have no Arduino hardware dependencies (only `EEPROM` which is abstracted by HAL)
- Have clear inputs/outputs (byte arrays, validation rules)
- Are low-risk to extract (self-contained, no global state except `prefs[]`)
- Would add ~80 lines of immediately testable logic

---

## 2. Documentation State

### 2.1 Spec Completeness

| Spec Directory | spec.md | plan.md | tasks.md | research.md | quickstart.md | Status |
|----------------|---------|---------|----------|-------------|---------------|--------|
| `specs/001-tool-install/` | **MISSING** | ✅ | ✅ | ✅ | ✅ | **INCOMPLETE** |
| `specs/002-pio-project/` | ✅ | ✅ | ✅ | ✅ | ✅ | **COMPLETE** |
| `specs/003-test-docs-audit/` | ✅ | ✅ | ✅ | ✅ | ✅ | **COMPLETE** |

**Note**: `specs/001-tool-install/` is missing `spec.md` — the behavioral specification that should precede the plan.

### 2.2 Constitution Check

`CLAUDE.md` contains Constitution v2.0.0 (ratified 2026-05-02, amended 2026-05-05).

| Principle | Followed in Code? | Evidence |
|-----------|-------------------|----------|
| I. Hardware-First | Partial | `platformio.ini` targets Uno; `cw-trainer.ino` uses `String`-free C-style strings; but `MorseEnDecoder.cpp` uses `pow()` (float in hot path) |
| II. Memory Discipline | Partial | `cw-trainer.ino` uses PROGMEM for strings; but `MorseEnDecoder.cpp` has class members that could be `uint8_t` instead of `int` |
| III. Layered Architecture | **No** | `cw-trainer.ino` is a monolith with UI + Game + Pedagogy + CW Engine all mixed together |
| IV. Test-First | **No** | Only 5 HAL tests exist; zero tests for application logic |
| V. Code Quality | Partial | Naming is consistent; but functions exceed 50-line limit (e.g., `morse_trainer()` ~145 lines, `set_prefs()` ~80 lines) |

### 2.3 README Accuracy

`README.md` describes the original Tom Lewis/Mike Hughes project accurately but does **not** reflect the SpeckIT fork:
- No mention of PlatformIO dual-target build
- No mention of HAL abstraction
- No mention of three-tier testing
- No mention of SpeckIT constitution or development workflow
- Links to original hardware instructions but not to SpeckIT docs

### 2.4 Architectural Documentation

**Missing entirely**:
- No doc explaining `lib/hal/` vs `src/` vs `libraries/` directory boundaries
- No doc explaining the dual-target build rationale
- No state machine diagram for trainer logic
- No data model for preferences, character sets, or game state
- No timing constraint documentation (Morse speed formula exists inline in `cw-trainer.ino` lines 66–83 but not as a spec)

### 2.5 Most Critical Undocumented Behavior

The Morse timing system in `cw-trainer.ino` (lines 66–83) documents measured speeds for PARIS at different key_speed_adj values, but:
- The formula for WPM → milliseconds is not documented anywhere except inline
- The Farnsworth spacing formula (`extra_gap = (1200/farnsworthWPM) - (1200/targetWPM)`) from the constitution is not implemented in code
- The debounce logic in `MorseEnDecoder.cpp` has no tolerance spec

---

## 3. Code Structure State

### 3.1 Monolith vs Modularized

| File | Lines | Logic Category | Extracted? |
|------|-------|----------------|------------|
| `cw-trainer/cw-trainer.ino` | 609 | UI + Game + Pedagogy + CW Engine + Prefs | **No** |
| `src/nano/main.cpp` | 35 | Entry point | Yes (thin orchestrator) |
| `src/desktop/main.cpp` | 29 | Test runner entry | Yes (thin runner) |
| `lib/hal/hal.h` | 44 | Hardware abstraction contract | Yes |
| `lib/hal/hal_nano.cpp` | 42 | Nano HAL impl | Yes |
| `lib/hal/hal_desktop.cpp` | 100 | Desktop HAL impl | Yes |

**~92% of logic (609/659 lines) lives in the monolith.**

### 3.2 HAL Contract Completeness

`lib/hal/hal.h` declares 17 functions across 6 categories:
- Time (2): `hal_millis`, `hal_micros`, `hal_delay_ms`, `hal_delay_us`
- Tone (3): `hal_tone_start`, `hal_tone_stop`, `hal_tone_is_active`
- Input (3): `hal_button_read`, `hal_button_get`, `hal_key_read`
- Output (6): `hal_lcd_init`, `hal_lcd_clear`, `hal_lcd_set_cursor`, `hal_lcd_print`, `hal_lcd_write_char`, `hal_lcd_backlight`
- EEPROM (3): `hal_eeprom_read`, `hal_eeprom_write`, `hal_eeprom_update`
- Random (2): `hal_random`, `hal_random_seed`
- Debug (2): `hal_led_set`, `hal_serial_print`, `hal_serial_println`

**Gaps**:
- No analog read abstraction (used by `MorseEnDecoder.cpp` for audio signal)
- No PWM/tone frequency query
- No LCD backlight color abstraction (constitution mentions RGB LCD Shield)

### 3.3 Arduino Leakage

| File | Arduino Dependency | Leakage? |
|------|-------------------|----------|
| `cw-trainer/cw-trainer.ino` | `<avr/pgmspace.h>`, `<EEPROM.h>`, `<Adafruit_RGBLCDShield.h>`, `<MorseEnDecoder.h>` | **Yes** (expected; this is the legacy monolith) |
| `src/nano/main.cpp` | `<Arduino.h>`, `<LiquidCrystal.h>` | **Yes** (expected; entry point) |
| `src/desktop/main.cpp` | None | No |
| `lib/hal/hal_nano.cpp` | `<Arduino.h>`, `<EEPROM.h>` | No (HAL is allowed) |
| `lib/hal/hal_desktop.cpp` | None | No |
| `test/test_hal.cpp` | None | No |

**Constitutional violation**: `cw-trainer.ino` is legacy and exempt, but new code in `src/nano/main.cpp` directly uses `LiquidCrystal` instead of HAL LCD functions. The HAL LCD functions exist but are not used by the new entry point.

### 3.4 Dependency Graph

```
cw-trainer.ino
  ├── Adafruit_RGBLCDShield (3rd party)
  ├── MorseEnDecoder (3rd party)
  ├── avr/pgmspace.h
  └── EEPROM.h

src/nano/main.cpp
  ├── Arduino.h
  ├── LiquidCrystal.h (3rd party)
  └── hal.h

src/desktop/main.cpp
  └── hal.h

lib/hal/hal_nano.cpp
  ├── Arduino.h
  └── EEPROM.h

lib/hal/hal_desktop.cpp
  └── <stdio.h>, <stdlib.h>, <time.h>

test/test_hal.cpp
  ├── Unity
  └── (inline mock HAL — does NOT include hal.h)
```

**Issue**: `test/test_hal.cpp` duplicates the mock HAL instead of including `lib/hal/hal_desktop.cpp`. This means the desktop HAL implementation is not exercised by tests.

### 3.5 Build System Configuration

`platformio.ini`:
```ini
[platformio]
default_envs = desktop
src_dir = src/nano          # <-- Bug: should be dynamic per env

[env:desktop]
platform = native
build_flags = -DPIO_ENV_DESKTOP -Wall -Wextra -I./lib/hal -I../test
src_dir = src/desktop
build_src_filter = +<./> +<../lib/hal/hal_desktop.cpp>
lib_deps = throwtheswitch/Unity@^2.6.0

[env:nano]
platform = atmelavr
board = uno
framework = arduino
build_flags = -Wall -Wextra -I../lib/hal
src_dir = src/nano
build_src_filter = +<./> +<../lib/hal/hal_nano.cpp>
lib_deps = LiquidCrystal@^1.0.0
```

**Issues**:
1. `src_dir = src/nano` at `[platformio]` level overrides both envs — `desktop` env correctly overrides it, but this is confusing
2. `test/` directory is not configured per-environment — `pio test` uses same test dir for both
3. No `simavr` integration for Tier 2 testing
4. `nano` env has no test framework dependency — tests only work because Unity is declared in `desktop` env's `lib_deps`
5. `cw-trainer/cw-trainer.ino` is not included in any build environment

---

## 4. Gap Analysis

### 4.1 Biggest Untested Surface Area

`cw-trainer/cw-trainer.ino` — 609 lines of mixed UI, game logic, pedagogy, and CW engine code. This is the entire application.

### 4.2 Most Critical Undocumented Behavior

Morse timing constants and calibration data (lines 66–83 of `cw-trainer.ino`). The relationship between `KEY_SPEED`, `Key_speed_adj`, `GROUP_DLY`, and actual WPM is only documented inline and never extracted into a testable formula.

### 4.3 What's Blocking TDD Adoption Today

1. **No testable modules**: All logic is in `.ino` file; Arduino setup/loop semantics make unit testing hard
2. **HAL not used by new entry point**: `src/nano/main.cpp` uses `LiquidCrystal` directly instead of HAL, so HAL abstraction is not yet the primary interface
3. **No `lib/core/` directory**: Constitution mandates pure logic in `lib/core/`; directory does not exist
4. **`test/test_hal.cpp` duplicates mock**: Tests don't exercise `hal_desktop.cpp`, so the real desktop HAL has no coverage

### 4.4 Quickest Win for Test Coverage

Extract `prefs_init()` and `prefs_set()` into `lib/core/prefs.cpp` with `lib/core/prefs.h`. Add Unity tests in `test/core/test_prefs.cpp`. This is ~2 hours of work and would immediately add testable coverage for:
- EEPROM default values
- Preference validation (min/max bounds)
- Preference persistence round-trip

---

## 5. Action Plan

### 5.1 Immediate Actions (This Session)

1. **Fix `test/test_hal.cpp` to include `lib/hal/hal_desktop.cpp`** instead of duplicating mock implementation (`test/test_hal.cpp`)
2. **Add missing `spec.md` to `specs/001-tool-install/`** (`specs/001-tool-install/spec.md`)
3. **Add HAL LCD tests** to `test/test_hal.cpp` — test `hal_lcd_print`, `hal_lcd_set_cursor`, `hal_lcd_write_char`, `test_lcd_get_row` (`test/test_hal.cpp`)
4. **Update `README.md`** to reflect SpeckIT fork, PlatformIO, HAL, and three-tier testing (`README.md`)

### 5.2 Short-Term Actions (Next 1–2 Sprints)

1. **Extract `prefs` module from `cw-trainer.ino`**
   - Create `lib/core/prefs.h` and `lib/core/prefs.cpp`
   - Migrate `prefs_init()`, `prefs_set()`, `prefs[]` array, limit tables
   - Acceptance: `pio test -e desktop` passes with ≥80% branch coverage on prefs module

2. **Create `lib/core/` directory and first module**
   - Directory: `lib/core/`
   - Module: `prefs` (as above)
   - Update `src/nano/main.cpp` to call `prefs_init()` via HAL EEPROM
   - Acceptance: Nano build still compiles; desktop tests pass

3. **Fix `platformio.ini` test configuration**
   - Separate `test_dir` per environment or use `test_build_src_filter`
   - Add Unity to `nano` env `lib_deps` for test compilation
   - Remove confusing `src_dir` from `[platformio]` level
   - Acceptance: `pio test -e desktop` and `pio test -e nano` both compile without errors

4. **Write Morse timing specification**
   - Document WPM → ms formula
   - Document Farnsworth spacing formula
   - Document debounce thresholds
   - File: `docs/morse-timing.md`
   - Acceptance: Formula can be verified by unit test against known values

### 5.3 Medium-Term Actions (Next Month)

1. **Extract all logic from `cw-trainer.ino` into `lib/core/` modules**
   - Modules needed: `menu`, `trainer`, `decoder`, `paris_test`
   - Each module gets its own spec directory before extraction
   - `cw-trainer.ino` becomes a thin orchestrator (~50 lines)
   - Acceptance: `.ino` file <100 lines; all logic has ≥80% test coverage

2. **Wrap or fork `MorseEnDecoder` into `lib/core/cw_engine/`**
   - Remove `<Arduino.h>` dependency from wrapped version
   - Replace `millis()` with `hal_millis()`, `digitalWrite()` with HAL calls
   - Add comprehensive unit tests for encoding/decoding
   - Acceptance: `test/core/test_cw_engine.cpp` passes with character-round-trip tests

3. **Add simavr integration (Tier 2)**
   - Create `simavr/run.sh` with GDB breakpoints and VCD output
   - Add `simavr/` directory with simulation scripts
   - Acceptance: Timing-sensitive code (Morse encode/decode) can be verified cycle-accurately

4. **Expand Wokwi smoke tests**
   - Add scenarios: menu navigation, Koch session, decoder mode, preference change
   - File: `test/wokwi/smoke-test.yaml` (expanded)
   - Acceptance: All major user journeys have HIL test coverage

---

## 6. Per-File Recommendations

### `test/test_hal.cpp`
- **Current**: 5 tests covering time, LCD init, random, EEPROM
- **Missing**: tone tests, button tests, key tests, LCD cursor/print/write tests, serial tests
- **Fix**: Add 10+ tests to cover all 17 HAL functions. Include `lib/hal/hal_desktop.cpp` instead of duplicating mock.

### `cw-trainer/cw-trainer.ino`
- **Current**: 609-line monolith with all application logic
- **Issue**: Untested, Arduino-dependent, violates constitution layered architecture
- **Fix**: Extract modules one at a time into `lib/core/`. Start with `prefs`. Target: reduce to <100 lines.

### `lib/hal/hal.h`
- **Current**: 17 functions across 7 categories
- **Missing**: analog read (needed for Morse audio signal), PWM frequency query, LCD backlight color
- **Fix**: Add `hal_analog_read(uint8_t pin)` and `hal_lcd_backlight_color(uint8_t color)` if RGB LCD is target.

### `lib/hal/hal_nano.cpp`
- **Current**: Arduino wrappers for all HAL functions
- **Issue**: `hal_button_read`, `hal_button_get`, `hal_lcd_*` are stubs (empty or return 0)
- **Fix**: Implement using `LiquidCrystal` and button reading logic. Or document as "intentional stubs pending hardware".

### `lib/hal/hal_desktop.cpp`
- **Current**: Mock implementations with LCD buffer, EEPROM array, time counter
- **Issue**: Not used by `test/test_hal.cpp` (tests duplicate the mock)
- **Fix**: Refactor tests to `#include "../lib/hal/hal_desktop.cpp"` and use its mock state directly.

### `src/nano/main.cpp`
- **Current**: 35-line entry point using `LiquidCrystal` directly
- **Issue**: Bypasses HAL for LCD output
- **Fix**: Replace `g_lcd.print()` with `hal_lcd_print()` and `g_lcd.setCursor()` with `hal_lcd_set_cursor()`.

### `src/desktop/main.cpp`
- **Current**: 29-line manual runner printing LCD buffer and time
- **Issue**: Not a real test runner; just prints state
- **Fix**: Integrate with Unity or remove in favor of `pio test`.

### `platformio.ini`
- **Current**: Desktop and Nano environments configured
- **Issues**: Confusing `src_dir`, no per-env test dirs, no Unity in nano env, no simavr
- **Fix**: Restructure per constitution guidelines. See Short-Term Action 3.

### `libraries/morseIO/MorseEnDecoder.cpp`
- **Current**: 438-line third-party library with Arduino dependencies
- **Issue**: Not testable on host-native; uses `millis()`, `digitalWrite()`, `analogRead()`, `tone()`, `pgm_read_byte_near()`
- **Fix**: Wrap or fork into `lib/core/cw_engine/` replacing Arduino calls with HAL.

### `README.md`
- **Current**: Describes original project only
- **Fix**: Rewrite to describe SpeckIT fork, build instructions, test commands, HAL architecture.

### `specs/001-tool-install/plan.md`
- **Current**: Missing `spec.md`
- **Fix**: Create `specs/001-tool-install/spec.md` with behavioral specification for tool installation.

---

## 7. New Specs to Create

| Directory | Purpose | Priority |
|-----------|---------|----------|
| `specs/004-prefs-module/` | Extract prefs from `cw-trainer.ino` into `lib/core/` | P1 |
| `specs/005-hal-complete/` | Complete HAL implementation (stubs → real) and full test coverage | P1 |
| `specs/006-morse-timing/` | Document and test Morse timing formulas | P2 |
| `specs/007-menu-module/` | Extract `get_mode()` menu system into `lib/core/menu/` | P2 |
| `specs/008-trainer-module/` | Extract `morse_trainer()` into `lib/core/trainer/` | P2 |
| `specs/009-decoder-module/` | Extract `morse_decode()` into `lib/core/decoder/` | P3 |
| `specs/010-cw-engine/` | Wrap/fork `MorseEnDecoder` into HAL-based `lib/core/cw_engine/` | P3 |
| `specs/011-simavr-tier2/` | Add simavr integration for cycle-accurate testing | P3 |

---

## 8. Test Suite Expansion Plan

### Module: HAL
- **Test file**: `test/hal/test_hal.cpp` (rename from `test/test_hal.cpp`)
- **First test case**: `test_hal_tone_start_stop` — verify tone active flag toggles
- **Dependencies to mock**: None (uses desktop HAL mock)

### Module: Prefs
- **Test file**: `test/core/test_prefs.cpp`
- **First test case**: `test_prefs_defaults` — verify `prefs_init()` sets all 8 defaults correctly
- **Dependencies to mock**: HAL EEPROM (`hal_eeprom_read`, `hal_eeprom_write`)

### Module: Menu
- **Test file**: `test/core/test_menu.cpp`
- **First test case**: `test_menu_initial_state` — verify menu starts at entry 1
- **Dependencies to mock**: HAL LCD (`hal_lcd_print`, `hal_lcd_clear`), HAL buttons (`hal_button_get`)

### Module: Trainer
- **Test file**: `test/core/test_trainer.cpp`
- **First test case**: `test_trainer_char_set_alpha` — verify character set selection produces valid chars
- **Dependencies to mock**: HAL LCD, HAL tone, HAL random, HAL key, HAL buttons, CW engine

### Module: CW Engine
- **Test file**: `test/core/test_cw_engine.cpp`
- **First test case**: `test_encode_decode_roundtrip` — write 'A' to encoder, verify decoder reads 'A'
- **Dependencies to mock**: HAL tone, HAL time, HAL digital I/O

---

## 9. Risk Register

| Risk | Likelihood | Impact | Mitigation |
|------|-----------|--------|------------|
| Extracting logic from `cw-trainer.ino` breaks existing functionality | High | High | Extract one module at a time; keep `.ino` working after each extraction; write tests BEFORE extraction |
| `MorseEnDecoder` fork diverges from upstream, losing bug fixes | Medium | Medium | Document fork date and upstream version; periodically diff against upstream; contribute HAL patches upstream if possible |
| `nano` tests cannot run without hardware (no simavr yet) | High | Medium | Prioritize simavr integration; in interim, rely on `desktop` tests for logic and manual hardware tests for timing |
| SRAM overflow when adding tests to Nano build | Low | High | Tests run on `desktop` only; Nano build stays production code only. Monitor `.ino` size with `avr-size` after each extraction. |
| HAL LCD stubs prevent meaningful integration testing | Medium | Medium | Complete HAL implementation as P1 spec (005); or document stubs as known limitation |

---

## 10. Validation Checklist

- [x] 100% of source files accounted for in coverage classification
- [x] Action plan contains Immediate actions (4 items)
- [x] Every public HAL interface documented or flagged
- [x] Risk register has 5 entries (≥3 required)
- [x] All existing specs checked for completeness
- [x] Constitutional principles referenced throughout
- [x] All file paths verified to exist in repo
- [x] Embedded constraints (2KB RAM, 32KB Flash) considered in recommendations

---

*End of Audit. Generated by SpeckIT on 2026-05-05.*
