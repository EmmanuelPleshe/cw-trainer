# Research: 002-pio-project

## Decision: PlatformIO Project Setup

### PlatformIO Desktop Testing

**Chosen**: Use PlatformIO native environment for Tier 1 tests

**Rationale**:
- PlatformIO supports `[env:desktop]` with `platform = native`
- No Arduino headers when framework = none
- Unity test framework available via lib_deps
- Enables fast TDD loop without flashing hardware

**Alternative Considered**: Use separate CMake + Unity project
- Rejected: Extra build system to maintain, deviates from Constitution project structure

### HAL Abstraction Strategy

**Chosen**: Single hal.h with conditional compilation

**Rationale**:
- Clean separation between interface and implementation
- hal_nano.cpp: #ifdef ARDUINO — uses Arduino.h
- hal_desktop.cpp: #ifdef PIO_ENV_DESKTOP — uses mock state
- No runtime polymorphism (saves SRAM)

**API Design**:
- C-style functions (no classes per Constitution)
- All Arduino-specific calls go through HAL
- Mock HAL provides controllable time, LCD buffer inspection, tone tracking

### Wokwi Integration

**Chosen**: Use Wokwi CLI with scenario YAML files

**Rationale**:
- Wokwi provides complete Arduino simulation
- CLI enables CI integration
- diagram.json defines hardware (Uno, LCD, buttons)

**Verification**:
- Run `wokwi-cli --scenario test/wokwi/smoke-test.yaml`
- Requires WOKWI_CLI_TOKEN env var

## References

- PlatformIO Testing: https://docs.platformio.org/en/latest/plus/unit-testing.html
- Unity Test Framework: https://github.com/ThrowTheSwitch/Unity
- Wokwi CLI: https://docs.wokwi.com/wokwi-ci/cli-usage