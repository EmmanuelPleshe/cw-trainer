# Implementation Plan: Expand Test Suite for Missing Coverage

**Branch**: `004-expand-test-suite` | **Date**: 2026-05-05 | **Spec**: [spec.md](spec.md)
**Input**: Feature specification from `specs/004-expand-test-suite/spec.md`

## Summary

Expand the existing HAL test suite from 5 tests to cover all 17 public HAL functions, refactor tests to use the desktop HAL implementation instead of duplicated mocks, and establish a module-based directory structure under `test/desktop/`. This is a pure test-infrastructure feature: no production code changes, no new runtime logic.

## Technical Context

**Language/Version**: C++11, Arduino-compatible C-style  
**Primary Dependencies**: Unity test framework (throwtheswitch/Unity ^2.6.0), PlatformIO Core 6.x  
**Storage**: N/A (tests use in-memory mocks only)  
**Testing**: Unity via PlatformIO `desktop` (native) environment  
**Target Platform**: x86_64 Linux (native); Arduino Uno (compilation gate only)  
**Project Type**: Embedded firmware test expansion  
**Performance Goals**: Test suite completes in under 5 seconds for desktop env  
**Constraints**: No Arduino-specific code in tests; no `String`, no `malloc`, no `float`; deterministic execution  
**Scale/Scope**: 17 HAL functions, 1 existing test file, 1 target HAL implementation file

## Constitution Check

*GATE: Must pass before Phase 0 research. Re-check after Phase 1 design.*

| Gate | Check | Status |
|------|-------|--------|
| I. Hardware-First | No changes to Nano flash/SRAM; desktop-only test additions | Pass |
| II. Memory Discipline | Tests run on host; no new globals on target | Pass |
| III. Layered Architecture | Tests validate HAL contract; strengthens module boundaries | Pass |
| IV. Test-First | Feature is entirely test creation; no code without tests | Pass |
| V. Code Quality Standards | C-style naming, no STL, max 50 lines per test function | Pass |

No constitutional violations. All gates pass.

## Project Structure

### Documentation (this feature)

```text
specs/004-expand-test-suite/
├── plan.md              # This file
├── research.md          # Phase 0 output (minimal: scope and framework decisions)
├── data-model.md        # Phase 1 output (test entities and state machines)
├── quickstart.md        # Phase 1 output (how to run expanded test suite)
├── contracts/           # Phase 1 output (test-to-HAL interface contract)
└── tasks.md             # Phase 2 output (/speckit-tasks)
```

### Source Code (repository root)

No source code changes for this feature. Files read/written:

```text
cw-trainer/
├── lib/hal/hal.h                      # HAL contract (read-only, validate against)
├── lib/hal/hal_desktop.cpp            # Desktop HAL impl (read; tests now link against it)
├── lib/hal/hal_nano.cpp               # Nano HAL impl (read-only; verify contract parity)
├── test/test_hal.cpp                  # Existing tests (refactor: remove duplicated mock)
├── test/desktop/                      # Empty (create: test/desktop/test_hal.cpp)
└── platformio.ini                     # Build config (read; verify test discovery paths)
```

**Structure Decision**: Tests organized under `test/desktop/` following PlatformIO convention for environment-specific test directories. Desktop HAL stays in `lib/hal/` as the production mock.

## Complexity Tracking

No violations. This feature is test-infrastructure-only with no production code changes.

## Research Decisions (Phase 0)

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

### RD-003: Test helper functions (`test_lcd_get_row`, `test_advance_time`, `test_eeprom_reset`) remain in `hal_desktop.cpp`

**Decision**: Test helpers stay in `hal_desktop.cpp`, conditionally compiled with `PIO_ENV_DESKTOP`. Tests call them directly.

**Rationale**: Helpers are already there and are useful for both the desktop runner and tests. Moving them out creates a new module with no benefit.

### RD-004: No changes to `platformio.ini` expected

**Decision**: Existing `desktop` environment configuration already supports test discovery.

**Rationale**: `platformio.ini` has `[env:desktop]` with `lib_deps = throwtheswitch/Unity@^2.6.0`. The `test/` directory is automatically scanned. If `test/desktop/` is not auto-discovered, we may need to add `test_dir` — but this is a config change, not a code change, and falls under FR-004/FR-005 acceptance criteria.

## Data Model

See `data-model.md` for test entity definitions (HAL function, test case, mock state).

## Quickstart

See `quickstart.md` for how to run the expanded test suite and verify all acceptance criteria.
