# Tasks: 002-pio-project

**Input**: Design documents from `/specs/002-pio-project/`
**Prerequisites**: plan.md (required), spec.md (required)

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this task belongs to

---

## Phase 1: Setup (Project Initialization)

**Purpose**: Create PlatformIO configuration and directory structure

- [ ] T001 Create platformio.ini with nano and desktop environments
- [ ] T002 [P] Create lib/hal/ directory structure
- [ ] T003 [P] Create src/nano/ directory for Arduino code
- [ ] T004 [P] Create src/desktop/ directory for test runner
- [ ] T005 Create test/desktop/ directory for Tier 1 tests
- [ ] T006 Create test/wokwi/ directory for Tier 3 scenarios

---

## Phase 2: HAL Interface (Foundational)

**Purpose**: Define and implement hardware abstraction layer

- [ ] T007 Create lib/hal/hal.h with complete HAL interface
- [ ] T008 [P] Create lib/hal/hal_nano.cpp (Arduino implementation)
- [ ] T009 [P] Create lib/hal/hal_desktop.cpp (mock implementation)
- [ ] T010 Add test helpers to hal_desktop.cpp (test_lcd_get_row, test_advance_time)

---

## Phase 3: User Story 1 - PlatformIO Project Builds (Priority: P1)

**Goal**: `pio run` compiles for Arduino Uno without errors

**Independent Test**: Run `pio run` and verify .hex file produced

- [ ] T011 [US1] Create minimal src/nano/main.cpp with setup/loop
- [ ] T012 [US1] Verify platformio.ini builds with `pio run`
- [ ] T013 [US1] Verify .hex output for ATmega328P

---

## Phase 4: User Story 2 - Native Tests Pass (Priority: P1)

**Goal**: `pio test --environment desktop` executes and passes

**Independent Test**: Run tests, verify Unity test runner works

- [ ] T014 [US2] Create src/desktop/main.cpp test runner stub
- [ ] T015 [US2] Create test/desktop/test_hal/test_hal.cpp with basic test
- [ ] T016 [US2] Verify tests run with `pio test --environment desktop`

---

## Phase 5: User Story 3 - HAL Abstraction Works (Priority: P2)

**Goal**: Game logic runs without Arduino dependencies via HAL

**Independent Test**: Native tests compile and run without Arduino headers

- [ ] T017 [US3] Verify hal_desktop.cpp compiles without ARDUINO define
- [ ] T018 [US3] Add HAL mock test: hal_millis returns controllable time
- [ ] T019 [US3] Add HAL mock test: LCD buffer inspection works

---

## Phase 6: User Story 4 - Wokwi Integration Ready (Priority: P2)

**Goal**: Wokwi CLI can run scenario tests

**Independent Test**: Run `wokwi-cli --scenario test/wokwi/smoke-test.yaml`

- [ ] T020 [US4] Create wokwi/diagram.json for Arduino Uno setup
- [ ] T021 [US4] Create test/wokwi/smoke-test.yaml scenario
- [ ] T022 [US4] Verify Wokwi CLI starts simulation

---

## Phase 7: Polish & Integration

**Purpose**: Final verification and documentation

- [ ] T023 Verify full build: `pio run` completes without errors
- [ ] T024 Verify full test: `pio test --environment desktop` passes
- [ ] T025 Update quickstart.md with new project structure
- [ ] T026 Verify Constitution compliance: no String, no malloc in lib/

---

## Dependency Graph

```
Phase 1 (Setup)
T001 ─────┬──────────────► Phase 2 (HAL)
T002 ─────┤                    T007 ──┬─► Phase 3 (US1)
T003 ─────┤                    T008    │      T011 ──► T012 ──► T013
T004 ─────┤                    T009    │      │
T005 ─────┤                    T010    │      ▼
T006 ─────┘                       │      Phase 4 (US2)
                                   │      T014 ──► T015 ──► T016
                                   │      │
                                   ▼      ▼
                              Phase 5 (US3)
                              T017 ──► T018 ──► T019
                                   │
                                   ▼
                              Phase 6 (US4)
                              T020 ──► T021 ──► T022
                                   │
                                   ▼
                              Phase 7 (Polish)
                              T023 ──► T024 ──► T025 ──► T026
```

**Parallel Opportunities**:
- T002, T003, T004, T005, T006 can run in parallel (directory creation)
- T008, T009, T010 can run in parallel (HAL implementations)

---

## Summary

- **Total tasks**: 26
- **Parallelizable**: 7 tasks
- **MVP scope**: Phase 1-4 (T001-T016) — builds and tests work
- **User Story mapping**:
  - US1: T011-T013 (build for Arduino)
  - US2: T014-T016 (native tests)
  - US3: T017-T019 (HAL abstraction)
  - US4: T020-T022 (Wokwi integration)