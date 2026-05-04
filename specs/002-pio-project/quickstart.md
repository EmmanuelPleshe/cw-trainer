# Quick Start: SpeckIT Development

## Prerequisites

- PlatformIO installed (`pipx install platformio`)
- Wokwi CLI installed (`curl -L https://wokwi.com/ci/install.sh | sh`)
- AVR toolchain (`yay -S simavr avr-gdb`)

## Build Commands

### Arduino Build (Tier 3 prep)

```bash
# Build for Arduino Uno
pio run

# Build and upload (requires avrdude)
pio run --target upload
```

### Native Tests (Tier 1)

```bash
# Run unit tests
pio test --environment desktop

# Run specific test
pio test --environment desktop --filter test_koch
```

### Wokwi Simulation (Tier 3)

```bash
# Run smoke test scenario
wokwi-cli --scenario test/wokwi/smoke-test.yaml
```

## Project Structure

```
cw-trainer/
├── lib/hal/           # HAL implementations
│   ├── hal.h          # Interface
│   ├── hal_nano.cpp   # Arduino
│   └── hal_desktop.cpp # Mock
├── src/nano/         # Arduino code
├── src/desktop/       # Test runner
├── test/desktop/     # Tier 1 tests
├── test/wokwi/       # Tier 3 scenarios
└── platformio.ini    # Build config
```

## First Run

```bash
# Verify project builds
pio run

# Verify tests run
pio test --environment desktop
```

## Troubleshooting

### "pio: command not found"
```bash
export PATH="$HOME/.local/bin:$PATH"
```

### Test fails with "undefined reference"
- Check test_build_src in platformio.ini
- Verify hal.h is included

### Wokwi fails with "token not set"
```bash
export WOKWI_CLI_TOKEN=your-token
```