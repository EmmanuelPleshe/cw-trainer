#!/bin/bash
#
# SpeckIT Tool Installation Script for EndeavourOS/Arch Linux
# Installs the complete SpeckIT development toolchain
# Idempotent: safe to re-run, skips already-installed tools
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

# Track if anything was installed
installed=0

# Step 1: Official packages (check each)
echo ""
echo "==> Checking official packages..."

check_and_install() {
    local pkg="$1"
    if ! pacman -Qi "$pkg" &> /dev/null; then
        echo "  Installing $pkg..."
        sudo pacman -S --needed "$pkg"
        installed=1
    else
        echo "  $pkg already installed, skipping"
    fi
}

check_and_install base-devel
check_and_install python-pipx
check_and_install nodejs
check_and_install npm
check_and_install avr-gcc
check_and_install avr-binutils
check_and_install avr-libc
check_and_install avrdude
check_and_install gtkwave

# Step 2: AUR packages (check each)
echo ""
echo "==> Checking AUR packages..."

check_aur() {
    local pkg="$1"
    if ! pacman -Qi "$pkg" &> /dev/null; then
        echo "  Installing $pkg..."
        $AUR_HELPER -S --needed "$pkg"
        installed=1
    else
        echo "  $pkg already installed, skipping"
    fi
}

check_aur simavr
check_aur avr-gdb

# Step 3: PlatformIO
echo ""
echo "==> Checking PlatformIO..."
if ! command -v pio &> /dev/null; then
    echo "  Installing PlatformIO..."
    pipx install platformio
    installed=1
else
    echo "  PlatformIO already installed, skipping"
fi

# Step 4: Wokwi CLI
echo ""
echo "==> Checking Wokwi CLI..."
if ! command -v wokwi &> /dev/null; then
    echo "  Installing Wokwi CLI..."
    curl -L https://wokwi.com/ci/install.sh | sh
    installed=1
else
    echo "  Wokwi CLI already installed, skipping"
fi

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
if command -v simavr &> /dev/null; then
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
    echo "=== All tools verified successfully! ==="
    if [ $installed -eq 1 ]; then
        echo ""
        echo "Next steps:"
        echo "  1. Run 'wokwi login' to authenticate with Wokwi"
        echo "  2. Create your SpeckIT project structure"
    fi
    exit 0
else
    echo "=== $errors tool(s) failed verification ==="
    exit 1
fi