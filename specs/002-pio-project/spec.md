# Feature Specification: Create PlatformIO Project Structure

**Feature Branch**: `002-pio-project`  
**Created**: 2026-05-03  
**Status**: Draft  
**Input**: User description: "create platformio project structure"

## User Scenarios & Testing *(mandatory)*

### User Story 1 - PlatformIO project builds (Priority: P1)

Developer can run `pio run` and compile the SpeckIT firmware for Arduino Uno.

**Why this priority**: Without a buildable project, nothing else works. This is the foundation.

**Independent Test**: Run `pio run` in project root, verify compilation succeeds with output showing Uno binary.

**Acceptance Scenarios**:

1. **Given** PlatformIO is installed, **When** running `pio run`, **Then** firmware compiles without errors
2. **Given** PlatformIO is installed, **When** running `pio run --environment nano`, **Then** produces .hex file for ATmega328P

---

### User Story 2 - Native tests pass (Priority: P1)

Developer can run `pio test --environment desktop` and execute Tier 1 unit tests.

**Why this priority**: Constitution requires TDD. Native tests are the fastest feedback loop.

**Independent Test**: Run `pio test --environment desktop`, verify tests execute and pass.

**Acceptance Scenarios**:

1. **Given** PlatformIO desktop environment is configured, **When** running `pio test`, **Then** test runner executes
2. **Given** test files exist in test/desktop/, **When** running tests, **Then** test results are reported

---

### User Story 3 - HAL abstraction works (Priority: P2)

Game logic runs in native environment using mock HAL without Arduino dependencies.

**Why this priority**: Constitution requires hardware access through HAL. This enables TDD.

**Independent Test**: Compile and run native tests, verify no direct Arduino calls in game logic.

**Acceptance Scenarios**:

1. **Given** HAL is abstracted, **When** running native tests, **Then** code compiles without Arduino headers
2. **Given** mock HAL exists, **When** tests call hal_millis(), **Then** mock returns controllable time

---

### User Story 4 - Wokwi integration ready (Priority: P2)

Project includes Wokwi configuration for Tier 3 integration testing.

**Why this priority**: Constitution requires three-tier testing. Wokwi provides hardware-in-loop.

**Independent Test**: Run `wokwi-cli --scenario test/wokwi/smoke-test.yaml`, verify simulation starts.

**Acceptance Scenarios**:

1. **Given** Wokwi CLI is installed, **When** running with scenario, **Then** simulation starts
2. **Given** diagram.json exists, **When** Wokwi loads, **Then** shows Arduino Uno with components

---

### Edge Cases

- What happens when PlatformIO is not installed? → Script should detect and report error
- What if Unity test framework is missing? → platformio.ini should declare dependency
- What if HAL implementation is incomplete? → Tests should fail with clear error

## Requirements *(mandatory)*

### Functional Requirements

- **FR-001**: Project MUST compile with `pio run` targeting Arduino Uno (atmega328p)
- **FR-002**: Native tests MUST run with `pio test --environment desktop`
- **FR-003**: HAL MUST be abstracted with mock implementation for desktop testing
- **FR-004**: Project structure MUST follow Constitution (lib/, src/nano/, src/desktop/, test/)
- **FR-005**: platformio.ini MUST define both desktop and nano environments
- **FR-006**: Wokwi configuration MUST exist for integration testing
- **FR-007**: All code MUST follow Constitution memory constraints (no String, no malloc)

### Key Entities

- **PlatformIO Configuration**: Build settings, environments, library dependencies
- **HAL Interface**: Abstract hardware calls (time, GPIO, tone, LCD, EEPROM)
- **Test Structure**: Tier 1 (desktop), Tier 3 (wokwi) test organization

## Success Criteria *(mandatory)*

### Measurable Outcomes

- **SC-001**: `pio run` completes without errors within 60 seconds
- **SC-002**: `pio test --environment desktop` runs and reports results
- **SC-003**: Native test execution completes in under 10 seconds
- **SC-004**: Flash size reported by PIO is under 28KB (Constitution limit)

## Assumptions

- PlatformIO 6.x will work on EndeavourOS with pipx installation
- Unity test framework is available via platformio lib_deps
- Wokwi CLI can be invoked via command line for CI integration
- User has already run install-arch.sh and tools are available