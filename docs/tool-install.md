# SpeckIT Tool Installation Guide

This guide covers installing the complete SpeckIT development toolchain on EndeavourOS/Arch Linux.

## Overview

SpeckIT uses a three-tier testing approach:

| Tier | Tool | Purpose |
|------|------|---------|
| Tier 1 | PlatformIO + Unity | Native unit tests (fastest) |
| Tier 2 | simavr + GDB | Cycle-accurate AVR simulation |
| Tier 3 | Wokwi | Full hardware-in-loop testing |

## Prerequisites

- EndeavourOS or Arch Linux (x86_64)
- sudo access
- AUR helper installed (yay or paru)

## Quick Install

### One-Liner

```bash
curl -sL https://raw.githubusercontent.com/eman/cw-trainer/001-tool-install/scripts/install-arch.sh | bash
```

### Manual Step-by-Step

#### 1. Install Official Packages

```bash
sudo pacman -S --needed \
    base-devel \
    python-pipx \
    nodejs \
    npm \
    avr-gcc \
    avr-binutils \
    avr-libc \
    avrdude \
    gtkwave
```

#### 2. Install AUR Packages

```bash
# Install yay if not already installed
git clone https://aur.archlinux.org/yay.git
cd yay && makepkg -si

# Install AVR tools
yay -S simavr avr-gdb
```

#### 3. Install PlatformIO

```bash
pipx install platformio
```

Add to PATH if needed:
```bash
export PATH="$HOME/.local/bin:$PATH"
```

#### 4. Install Wokwi CLI

```bash
curl -L https://wokwi.com/ci/install.sh | sh
wokwi login
```

## Verification

Run this command to verify all tools:

```bash
pio --version && avr-gcc --version | head -1 && simavr --help | head -1 && wokwi --version
```

Expected output:
- PlatformIO: `PlatformIO Core, version 6.x`
- AVR-GCC: `avr-gcc version 12.x+`
- simavr: Help output
- Wokwi: `2.x.x`

## Tool Details

### PlatformIO

Embedded development platform. Provides:
- Native test runner (Unity framework)
- Arduino build system
- Library management

### AVR Toolchain

| Tool | Package | Purpose |
|------|---------|---------|
| avr-gcc | `avr-gcc` | C compiler for ATmega328P |
| avr-binutils | `avr-binutils` | Binary tools (ld, ar, objdump) |
| avr-libc | `avr-libc` | C standard library |
| avrdude | `avrdude` | Flash programmer |
| avr-size | `avr-size` | Size analysis |
| avr-nm | `avr-nm` | Symbol table |

### simavr

Cycle-accurate AVR simulator. Enables:
- Debugging without hardware
- Timing verification
- ISR testing

### Wokwi

Web-based Arduino simulator. Provides:
- Complete Arduino environment
- LCD, buttons, buzzer simulation
- CLI for CI integration

## Troubleshooting

### pipx: command not found

```bash
# Add to ~/.bashrc or ~/.zshrc
export PATH="$HOME/.local/bin:$PATH"
source ~/.bashrc
```

### yay: command not found

```bash
sudo pacman -S --needed git base-devel
git clone https://aur.archlinux.org/yay.git
cd yay && makepkg -si
```

### wokwi login fails

1. Get token from https://wokwi.com/dashboard
2. Run: `wokwi login --token YOUR_TOKEN`

### Permission denied running install script

```bash
chmod +x scripts/install-arch.sh
```

## Project Structure

After installation, your SpeckIT project should look like:

```
speckit/
├── lib/               # Shared logic
│   ├── koch/
│   ├── srs/
│   ├── cw_engine/
│   ├── game/
│   └── hal/
├── src/
│   ├── nano/         # Arduino entry
│   └── desktop/       # Test runner
├── test/
│   ├── desktop/       # Tier 1 tests
│   └── wokwi/         # Tier 3 tests
├── simavr/            # Tier 2 scripts
├── wokwi/             # Wokwi config
└── platformio.ini
```

## Next Steps

1. Verify installation with the verification command above
2. Run `pio test --environment desktop` to confirm Tier 1 works
3. Proceed to create PlatformIO project structure