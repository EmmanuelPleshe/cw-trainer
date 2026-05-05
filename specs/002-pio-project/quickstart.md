# Quick Start: SpeckIT Development

## Prerequisites

- PlatformIO installed (`pipx install platformio`)
- Wokwi CLI installed (`curl -L https://wokwi.com/ci/install.sh | sh`)
- AVR toolchain (`yay -S simavr avr-gdb avr-libc`)

## Build Commands

### Arduino Build (Tier 3)

```bash
# Build for Arduino Uno (explicit environment)
pio run -e nano

# Build and upload (requires avrdude)
pio run -e nano --target upload
```

### Native Tests (Tier 1)

```bash
# Run unit tests (default_envs = desktop)
pio test

# Run specific test
pio test --filter test_hal
```

### Wokwi Simulation (Tier 3)

```bash
# Run smoke test scenario
wokwi-cli --scenario test/wokwi/smoke-test.yaml
```

### simAVR Simulation (Tier 2)

```bash
# Run firmware in simAVR (requires .elf from pio run -e nano)
simavr -m atmega328p -f 16000000 .pio/build/nano/firmware.elf
```

## Project Structure

```
cw-trainer/
├── lib/hal/              # HAL implementations
│   ├── hal.h             # Interface
│   ├── hal_nano.cpp      # Arduino impl
│   └── hal_desktop.cpp   # Mock impl
├── src/
│   ├── nano/main.cpp     # Arduino entry point
│   └── desktop/main.cpp  # Native test runner stub
├── test/
│   ├── test_hal.cpp      # Tier 1 Unity tests
│   └── wokwi/
│       └── smoke-test.yaml
├── wokwi/                # Wokwi assets
├── diagram.json          # Wokwi circuit (repo root)
├── wokwi.toml            # Wokwi config
└── platformio.ini        # Build config
```

## Environments

| Environment | Platform | Purpose |
|-------------|----------|---------|
| `desktop`   | `native` | Tier 1: Unity tests on host |
| `nano`      | `atmelavr` | Tier 3: Arduino Uno build |

## First Run

```bash
# Verify Arduino build
pio run -e nano

# Verify tests run
pio test

# Check flash/RAM usage
avr-size .pio/build/nano/firmware.elf
```

## Troubleshooting

### "pio: command not found"
```bash
export PATH="$HOME/.local/bin:$PATH"
```

### Test fails with "undefined reference"
- Check `build_src_filter` in `platformio.ini`
- Verify `hal.h` is included

### Wokwi fails with "token not set"
```bash
export WOKWI_CLI_TOKEN=your-token
```

### Wokwi "diagram.json not found"
`diagram.json` must be at repo root. Already there.

## Constitution Compliance

- No `String` class in `lib/` or `src/`
- No `malloc`/`new` in `lib/` or `src/`
- PROGMEM for constants on Arduino
- HAL abstraction for all hardware access
