# Tasks: Expand Test Suite for Missing Coverage

**Input**: Design documents from `specs/004-expand-test-suite/`
**Prerequisites**: plan.md (required), spec.md (required), research.md, data-model.md

**Organization**: Tasks grouped by user story. This is a test-infrastructure feature.

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this belongs to (US1, US2, US3)

---

## Phase 1: Setup (Repository State)

**Purpose**: Establish baseline before any test changes

- [x] T001 [P] Record current test state: `pio test -e desktop` output, test count, pass/fail status
- [x] T002 [P] Record current HAL contract: list all 17 functions in `lib/hal/hal.h`
- [x] T003 [P] Map existing tests to HAL functions: identify which of the 5 existing tests cover which functions
- [x] T004 [P] Identify missing HAL function tests: list 12 functions with no coverage

**Checkpoint**: Baseline documented. Gap list exists.

---

## Phase 2: Foundational (Directory Structure)

**Purpose**: Create `test/desktop/` directory structure before moving/writing tests

**⚠️ CRITICAL**: No test writing can begin until directory structure is established

- [x] T005 Create `test/desktop/` directory
- [x] T006 Verify PlatformIO discovers `test/desktop/` tests with `pio test -e desktop --list-tests`
- [x] T007 If discovery fails, update `platformio.ini` to include `test_dir = test/desktop` for desktop env
- [x] T008 Move existing `test/test_hal.cpp` to `test/desktop/test_hal.cpp`
- [x] T009 Verify `pio test -e desktop` still passes after move (5 tests)
- [x] T010 Remove or empty `test/test_hal.cpp` at root (leave thin runner or delete)

**Checkpoint**: Tests run from `test/desktop/`. Old root test file cleaned up.

---

## Phase 3: User Story 1 - Complete HAL Contract Tests (Priority: P1) 🎯 MVP

**Goal**: Expand from 5 to 17+ passing HAL tests

**Independent Test**: `pio test -e desktop` reports ≥17 tests, all passing

### Existing Tests (preserve)

- `test_hal_millis_starts_at_zero` — time
- `test_hal_advance_time` — time
- `test_hal_lcd_clear` — LCD
- `test_hal_random_range` — random
- `test_hal_eeprom_read_write` — EEPROM

### New Tests to Add

- [x] T011 [P] [US1] Add time tests: `test_hal_micros`, `test_hal_delay_us` in `test/desktop/test_hal.cpp`
- [x] T012 [P] [US1] Add tone tests: `test_hal_tone_start_stop`, `test_hal_tone_is_active` in `test/desktop/test_hal.cpp`
- [x] T013 [P] [US1] Add input tests: `test_hal_button_read`, `test_hal_button_get`, `test_hal_key_read` in `test/desktop/test_hal.cpp`
- [x] T014 [P] [US1] Add LCD tests: `test_hal_lcd_set_cursor`, `test_hal_lcd_print`, `test_hal_lcd_write_char`, `test_hal_lcd_backlight` in `test/desktop/test_hal.cpp`
- [x] T015 [P] [US1] Add EEPROM test: `test_hal_eeprom_update` in `test/desktop/test_hal.cpp`
- [x] T016 [P] [US1] Add random test: `test_hal_random_seed_determinism` in `test/desktop/test_hal.cpp`
- [x] T017 [P] [US1] Add debug tests: `test_hal_led_set`, `test_hal_serial_print` in `test/desktop/test_hal.cpp`
- [x] T018 [US1] Run `pio test -e desktop` and verify all 17+ tests pass

**Checkpoint**: All HAL functions have at least one test. Suite passes.

---

## Phase 4: User Story 2 - Use Desktop HAL in Tests (Priority: P2)

**Goal**: Remove duplicated HAL mock from test file, link against `lib/hal/hal_desktop.cpp`

**Independent Test**: `grep -c "uint32_t hal_millis" test/desktop/test_hal.cpp` returns 0

- [x] T019 [US2] Remove all duplicated HAL function implementations from `test/desktop/test_hal.cpp`
- [x] T020 [US2] Add `#include "hal.h"` and ensure `lib/hal/hal_desktop.cpp` is linked
- [x] T021 [US2] Replace inline mock state (`g_mock_millis`, `g_lcd_buffer`, `g_eeprom`) with calls to desktop HAL test helpers (`test_advance_time`, `test_lcd_get_row`, `test_eeprom_reset`)
- [x] T022 [US2] Verify `pio test -e desktop` still passes after deduplication
- [x] T023 [US2] Cross-check: every HAL function in `test/desktop/test_hal.cpp` is a declaration (from `hal.h`) or a test helper call, never a re-implementation

**Checkpoint**: Zero duplicated HAL implementations in test files.

---

## Phase 5: User Story 3 - Add Desktop Test Directory (Priority: P2)

**Goal**: Establish module-based test directory structure

**Independent Test**: `test/desktop/` contains organized test files; `pio test -e desktop` discovers and runs them

- [x] T024 [US3] Verify `test/desktop/` is the canonical directory for all desktop tests
- [x] T025 [US3] Document directory convention in `test/desktop/README.md`: one file per module, naming pattern `test_[module].cpp`
- [x] T026 [US3] Verify `pio test -e desktop --list-tests` shows `test/desktop/test_hal.cpp`
- [x] T027 [US3] Verify `pio run -e nano` compiles with zero errors (compilation gate)

**Checkpoint**: Test directory structure is established and documented.

---

## Phase 6: Polish & Cross-Cutting Concerns

**Purpose**: Validate determinism, performance, and constitution compliance

- [x] T028 [P] Run `pio test -e desktop` 3 times and verify identical results each time (determinism check)
- [x] T029 [P] Time `pio test -e desktop` and verify execution under 5 seconds
- [x] T030 [P] Review all new test functions: max 50 lines each, C-style naming, no `String`/`malloc`/`float`
- [x] T031 [P] Verify no Arduino-specific headers (`<Arduino.h>`, `<EEPROM.h>`, etc.) are included in `test/desktop/test_hal.cpp`
- [x] T032 [P] Verify `test/desktop/test_hal.cpp` includes `unity.h` and `hal.h` only

**Checkpoint**: All polish criteria pass.

---

## Dependencies & Execution Order

### Phase Dependencies

- **Setup (Phase 1)**: No dependencies — can start immediately
- **Foundational (Phase 2)**: Depends on Setup completion — BLOCKS all user stories
- **User Stories (Phase 3-5)**: All depend on Foundational phase completion
  - US1 can proceed independently (test writing)
  - US2 depends on US1 (needs tests to exist before deduplicating)
  - US3 can proceed in parallel with US1 (directory structure is independent of test content)
- **Polish (Phase 6)**: Depends on all user story phases

### User Story Dependencies

- **User Story 1 (P1)**: Can start after Foundational (Phase 2). No dependencies on other stories.
- **User Story 2 (P2)**: Depends on US1. Cannot deduplicate until tests exist.
- **User Story 3 (P2)**: Can start after Foundational (Phase 2). Independent of US1/US2.

### Within Each User Story

- US1: Write tests per HAL category → Run suite → Verify count
- US2: Remove duplication → Link desktop HAL → Verify pass
- US3: Create directory → Document → Verify discovery

### Parallel Opportunities

- All Phase 1 tasks marked [P] can run in parallel
- All Phase 2 tasks can run in parallel (directory + move + verify)
- US1 test writing tasks (T011–T017) can run in parallel (different test functions in same file)
- US3 can run in parallel with US1
- All Phase 6 tasks marked [P] can run in parallel

---

## Parallel Example: User Story 1

```bash
# Launch all US1 test writing tasks together:
Task: "Add time tests"
Task: "Add tone tests"
Task: "Add input tests"
Task: "Add LCD tests"
Task: "Add EEPROM test"
Task: "Add random test"
Task: "Add debug tests"
```

---

## Implementation Strategy

### MVP First (User Story 1 Only)

1. Complete Phase 1: Setup
2. Complete Phase 2: Foundational (directory structure)
3. Complete Phase 3: User Story 1 (write all missing HAL tests)
4. **STOP and VALIDATE**: Verify `pio test -e desktop` passes with ≥17 tests
5. If time remains, proceed to US2 and US3

### Incremental Delivery

1. Setup + Foundational → Directory ready
2. Add US1 → HAL tests complete → Deliverable chunk 1
3. Add US2 → Deduplication complete → Deliverable chunk 2
4. Add US3 → Directory structure documented → Final deliverable
5. Each chunk adds value without breaking previous tests

### Parallel Team Strategy

With multiple developers:

1. Team completes Setup + Foundational together
2. Once Foundational is done:
   - Developer A: US1 (write missing HAL tests by category)
   - Developer B: US3 (directory structure and documentation)
3. Both developers sync to Developer C for US2 (deduplication)

---

## Notes

- [P] tasks = different test categories or checks, no dependencies
- [Story] label maps task to specific user story for traceability
- Each user story produces an independently testable increment
- No production code changes in this feature — all tasks are test refactoring and writing
- Stop at any checkpoint to validate story independently
- Avoid: test functions longer than 50 lines, Arduino dependencies in test files, non-deterministic inputs
