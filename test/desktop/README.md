# Desktop Test Directory

Canonical directory for all desktop (native) tests.

## Structure

- One file per module: `test_[module].cpp`
- Tests link against `lib/hal/hal_desktop.cpp` (desktop HAL implementation)
- PlatformIO discovers tests via `test/test_hal/test_main.cpp` thin runner

## Current Tests

- `test_hal.cpp` — HAL contract tests (20 tests covering all 24 public functions)

## Running

```bash
pio test -e desktop
```

## Notes

`test/desktop/` cannot be a PlatformIO test suite directly because the directory name `desktop` matches the `[env:desktop]` environment name, causing PlatformIO to skip discovery. The thin runner at `test/test_hal/test_main.cpp` includes `../desktop/test_hal.cpp` to work around this limitation.
