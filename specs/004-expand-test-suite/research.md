# Research: Expand Test Suite for Missing Coverage

**Feature**: Expand Test Suite for Missing Coverage  
**Date**: 2026-05-05  
**Status**: Complete

## Decisions

### RD-001: Desktop HAL is the authoritative test implementation

**Decision**: `lib/hal/hal_desktop.cpp` is the source of truth for test mocks. Any duplication in `test/test_hal.cpp` is removed.

**Rationale**: The desktop HAL already implements every HAL function with mock state. Duplicating it in tests is maintenance overhead and invalidates the premise of "test the production code."

**Alternatives considered**:
- Keep duplication for test isolation — rejected. Violates constitution principle of testing production code.
- Generate mocks from `hal.h` automatically — rejected. Overkill for 17 functions; manual refactoring is faster and more maintainable.

### RD-002: `test/desktop/` is the canonical test directory for native tests

**Decision**: Move HAL tests from `test/test_hal.cpp` (root) to `test/desktop/test_hal.cpp`.

**Rationale**: PlatformIO discovers tests per-environment. `desktop` env should look in `test/desktop/`. Having tests at root causes confusion about which env owns them. This also prepares the structure for future `test/desktop/test_core_*.cpp` files.

**Alternatives considered**:
- Keep root `test/` for shared tests, `test/desktop/` for desktop-only — rejected. All current tests are desktop-only. Root directory should be reserved for cross-environment tests if any exist in future.

### RD-003: Test helper functions remain in `hal_desktop.cpp`

**Decision**: Test helpers (`test_lcd_get_row`, `test_advance_time`, `test_eeprom_reset`) stay in `hal_desktop.cpp`, conditionally compiled with `PIO_ENV_DESKTOP`. Tests call them directly.

**Rationale**: Helpers are already there and are useful for both the desktop runner and tests. Moving them out creates a new module with no benefit.

### RD-004: No changes to `platformio.ini` expected

**Decision**: Existing `desktop` environment configuration already supports test discovery.

**Rationale**: `platformio.ini` has `[env:desktop]` with `lib_deps = throwtheswitch/Unity@^2.6.0`. The `test/` directory is automatically scanned. If `test/desktop/` is not auto-discovered, we may need to add `test_dir` — but this is a config change, not a code change, and falls under FR-004/FR-005 acceptance criteria.

## Unknowns Resolved

| Unknown | Resolution | Source |
|---------|-----------|--------|
| Unity version | ^2.6.0 declared in `platformio.ini` | Build config |
| Desktop HAL function count | 17 public + 3 test helpers | `lib/hal/hal.h` and `hal_desktop.cpp` |
| Existing test coverage | 5 functions: millis, delay, lcd_clear, random, eeprom | `test/test_hal.cpp` |
| Missing coverage | 12 functions: micros, delay_us, tone_*3, button_*2, key, lcd_*4, led, serial_*2 | Comparison of `hal.h` vs `test/test_hal.cpp` |
| Test discovery path | PlatformIO auto-scans `test/` and subdirectories | PlatformIO docs |

## Open Questions (none remaining)

All scope questions resolved. No [NEEDS CLARIFICATION] markers.
