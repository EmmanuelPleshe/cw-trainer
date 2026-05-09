# Feature Specification: Expand Test Suite for Missing Coverage

**Feature Branch**: `004-expand-test-suite`  
**Created**: 2026-05-05  
**Status**: Draft  
**Input**: User description: "write the specs to write the tests that we've now identified are missing"

## User Scenarios & Testing *(mandatory)*

### User Story 1 - Complete HAL Contract Tests (Priority: P1)

As a developer making changes to hardware abstraction layer, I want every HAL function to have a unit test so that regressions in any HAL capability are caught immediately in native tests.

**Why this priority**: HAL is the foundation. All other tests depend on it. Currently only 5 of 17 public functions are tested.

**Independent Test**: Can be validated by running native tests and verifying all 17 HAL functions have at least one passing test case.

**Acceptance Scenarios**:

1. **Given** the HAL contract defines time functions, **When** native tests run, **Then** `hal_millis`, `hal_micros`, `hal_delay_ms`, `hal_delay_us` are all exercised with timing assertions.
2. **Given** the HAL contract defines tone functions, **When** native tests run, **Then** `hal_tone_start`, `hal_tone_stop`, `hal_tone_is_active` are exercised with state assertions.
3. **Given** the HAL contract defines input functions, **When** native tests run, **Then** `hal_button_read`, `hal_button_get`, `hal_key_read` are exercised with simulated input assertions.
4. **Given** the HAL contract defines LCD output functions, **When** native tests run, **Then** `hal_lcd_init`, `hal_lcd_clear`, `hal_lcd_set_cursor`, `hal_lcd_print`, `hal_lcd_write_char`, `hal_lcd_backlight` are exercised with buffer assertions.
5. **Given** the HAL contract defines EEPROM functions, **When** native tests run, **Then** `hal_eeprom_read`, `hal_eeprom_write`, `hal_eeprom_update` are exercised with persistence assertions.
6. **Given** the HAL contract defines random functions, **When** native tests run, **Then** `hal_random`, `hal_random_seed` are exercised with determinism assertions.
7. **Given** the HAL contract defines debug functions, **When** native tests run, **Then** `hal_led_set`, `hal_serial_print`, `hal_serial_println` are exercised with output capture assertions.

---

### User Story 2 - Use Desktop HAL in Tests (Priority: P2)

As a developer maintaining tests, I want the native test suite to use the real desktop HAL implementation instead of a duplicated mock so that tests actually verify the production code.

**Why this priority**: Duplicated mock means tests exercise test code, not production code. The desktop HAL could be broken and tests would still pass.

**Independent Test**: Can be validated by deleting the duplicated mock from `test/test_hal.cpp` and verifying tests still pass using `lib/hal/hal_desktop.cpp` directly.

**Acceptance Scenarios**:

1. **Given** the desktop HAL implementation exists in `lib/hal/hal_desktop.cpp`, **When** tests are refactored, **Then** no HAL function is re-implemented inside test files.
2. **Given** test helpers exist in `hal_desktop.cpp`, **When** tests need to inspect mock state, **Then** they call `test_lcd_get_row`, `test_advance_time`, `test_eeprom_reset` directly from the desktop HAL.

---

### User Story 3 - Add Desktop Test Directory (Priority: P2)

As a developer running native tests, I want tests organized by module in `test/desktop/` so that the test suite scales and remains maintainable as more modules get tests.

**Why this priority**: Constitution mandates test-first development. A scattered single test file will not scale to the planned `lib/core/` modules.

**Independent Test**: Can be validated by verifying `test/desktop/` contains test files grouped by module (e.g., `test/desktop/test_hal.cpp`, `test/desktop/test_prefs.cpp`) and `pio test -e desktop` discovers and runs them.

**Acceptance Scenarios**:

1. **Given** new modules will be added to `lib/core/`, **When** test organization is established, **Then** each new module gets a corresponding test file in `test/desktop/`.
2. **Given** the existing `test/test_hal.cpp` is a catch-all, **When** reorganization happens, **Then** HAL tests move to `test/desktop/test_hal.cpp` and the root `test/test_hal.cpp` is removed or becomes a thin runner.

---

### Edge Cases

- What happens when a HAL function is a stub (e.g., `hal_lcd_init` in `hal_nano.cpp`)? Tests must verify the contract is defined even if the implementation is intentionally empty.
- How do tests handle non-deterministic functions like `hal_random`? Tests must use seeded randomness and verify deterministic sequences.
- What if the desktop HAL test helpers conflict with future core logic? Test helpers must be namespaced or conditionally compiled.

## Requirements *(mandatory)*

### Functional Requirements

- **FR-001**: System MUST provide passing unit tests for every function declared in the HAL contract.
- **FR-002**: System MUST remove duplicated HAL mock implementations from test files, using the desktop HAL implementation as the authoritative test implementation.
- **FR-003**: System MUST organize native tests under a module-based directory structure, with one test file per module.
- **FR-004**: System MUST verify `pio test -e desktop` passes with zero failures after expansion.
- **FR-005**: System MUST verify `pio test -e nano` compiles successfully (upload may fail due to hardware absence, but compilation must succeed).
- **FR-006**: System MUST preserve existing test behavior — all previously passing tests must continue to pass.
- **FR-007**: System MUST ensure tests are deterministic: no reliance on unseeded randomness, no timing-dependent assertions without time control.

### Key Entities

- **HAL Test Suite**: Tests covering all 17 HAL functions. Attributes: function name, test case count, assertion types.
- **Desktop HAL**: The authoritative mock implementation used by tests. Attributes: function implementations, test helper functions, mock state buffers.
- **Test Directory Structure**: Organized test files under `test/desktop/`. Attributes: module name, test file path, coverage scope.

## Success Criteria *(mandatory)*

### Measurable Outcomes

- **SC-001**: 100% of HAL contract functions (17 total) have at least one passing unit test.
- **SC-002**: Zero duplicated HAL function implementations exist in test files.
- **SC-003**: The native test runner reports all tests passing with no structural warnings.
- **SC-004**: Test suite execution time remains under 5 seconds for the desktop environment.
- **SC-005**: All tests use deterministic inputs and produce identical results on every run.

## Assumptions

- The desktop HAL implementation is the correct authoritative mock for native testing.
- The established test framework is in use and will not change during this work.
- Hardware upload failure is expected in CI environments without a connected board; compilation success is the required gate.
- New core logic modules are out of scope for this feature; only test infrastructure and HAL tests are included.
- Test helper functions in the desktop HAL are stable and will not change during this work.
