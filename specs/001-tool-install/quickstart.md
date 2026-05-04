# Quick Start: Tool Installation

## Prerequisites

- EndeavourOS/Arch Linux (x86_64)
- sudo access
- AUR helper installed (yay or paru)

## One-Line Install

```bash
curl -sL https://raw.githubusercontent.com/eman/cw-trainer/001-tool-install/scripts/install-arch.sh | bash
```

Or manual:

```bash
# 1. Install core tools
sudo pacman -S --needed \
    base-devel python-pipx nodejs npm \
    avr-gcc avr-binutils avr-libc avrdude \
    gtkwave

# 2. Install AUR tools
yay -S --needed simavr avr-gdb

# 3. Install PlatformIO
pipx install platformio

# 4. Install Wokwi CLI
curl -L https://wokwi.com/ci/install.sh | sh
wokwi login
```

## Verify Installation

```bash
# All tools
pio --version && avr-gcc --version && simavr --help | head -1 && wokwi --version
```

Expected output examples:
- PlatformIO: `PlatformIO Core, version 6.x`
- AVR-GCC: `avr-gcc version 12.x`
- simavr: usage output
- Wokwi: `2.x.x`

## Troubleshooting

### pipx: command not found
Add to PATH: `export PATH="$HOME/.local/bin:$PATH"` or restart shell.

### yay: command not found
Install yay first: `sudo pacman -S --needed git base-devel && git clone aur.archlinux.org/yay && cd yay && makepkg -si`

### wokwi login fails
Get token from https://wokwi.com/dashboard, then run `wokwi login --token YOUR_TOKEN`

## Next Steps

After installation, proceed to create PlatformIO project structure for SpeckIT.