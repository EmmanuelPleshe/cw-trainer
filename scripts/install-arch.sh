#!/bin/bash
#
# SpeckIT Tool Installation Script for EndeavourOS/Arch Linux
# Installs the complete SpeckIT development toolchain
#
set -e

echo "=== SpeckIT Tool Installation for EndeavourOS ==="
echo ""

# Check for AUR helper
if ! command -v yay &> /dev/null && ! command -v paru &> /dev/null; then
    echo "ERROR: No AUR helper found (yay or paru)"
    echo "Install yay first:"
    echo "  sudo pacman -S --needed git base-devel"
    echo "  git clone https://aur.archlinux.org/yay.git"
    echo "  cd yay && makepkg -si"
    exit 1
fi

AUR_HELPER=$(command -v yay || command -v paru)
echo "Using AUR helper: $AUR_HELPER"

# Step 1: Official packages
echo ""
echo "==> Installing official packages..."
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

# Step 2: AUR packages
echo ""
echo "==> Installing AUR packages..."
$AUR_HELPER -S --needed simavr avr-gdb

# Step 3: PlatformIO
echo ""
echo "==> Installing PlatformIO..."
pipx install platformio

# Step 4: Wokwi CLI
echo ""
echo "==> Installing Wokwi CLI..."
curl -L https://wokwi.com/ci/install.sh | sh

# Verify installations
echo ""
echo "=== Verifying Installation ==="

errors=0

echo -n "PlatformIO: "
if pio --version &> /dev/null; then
    echo "OK ($(pio --version | grep -oP 'version \K[0-9.]+'))"
else
    echo "FAILED"
    ((errors++))
fi

echo -n "AVR-GCC: "
if avr-gcc --version &> /dev/null; then
    echo "OK ($(avr-gcc --version | grep -oP '\d+\.\d+\.\d+' | head -1))"
else
    echo "FAILED"
    ((errors++))
fi

echo -n "simavr: "
if simavr --help &> /dev/null; then
    echo "OK"
else
    echo "FAILED"
    ((errors++))
fi

echo -n "Wokwi: "
if wokwi --version &> /dev/null; then
    echo "OK ($(wokwi --version))"
else
    echo "FAILED"
    ((errors++))
fi

echo -n "GTKWave: "
if gtkwave --version &> /dev/null; then
    echo "OK"
else
    echo "FAILED"
    ((errors++))
fi

echo ""
if [ $errors -eq 0 ]; then
    echo "=== All tools installed successfully! ==="
    echo ""
    echo "Next steps:"
    echo "  1. Run 'wokwi login' to authenticate with Wokwi"
    echo "  2. Create your SpeckIT project structure"
    exit 0
else
    echo "=== $errors tool(s) failed to install ==="
    exit 1
fi