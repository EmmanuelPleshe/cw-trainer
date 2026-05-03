# Research: 001-tool-install

## Decision: Tool Stack Selection

**Chosen**: PlatformIO + simavr + Wokwi CLI on EndeavourOS/Arch

### Rationale

1. **PlatformIO**: Industry standard for embedded Arduino development. Native test support (Unity) enables Tier 1 TDD. Version 6.x current.

2. **simavr**: Best open-source AVR simulator. AUR package available. Supports cycle-accurate timing for Tier 2 verification.

3. **Wokwi**: Web-based Arduino simulator. Excellent for Tier 3 integration tests. CLI available for CI.

4. **Arch/EndeavourOS**: Cleanest package availability. Most tools in official repos, rest in AUR. No PPAs needed.

### Alternatives Considered

- **PlatformIO Core only** (no IDE): Rejected - need native test runner
- **QEMU**: Rejected - no AVR support
- **Proteus/Multisim**: Rejected - proprietary, expensive
- **Ubuntu/Debian**: Rejected - older packages, more setup work

## Verification Strategy

Each tool verified via `--version` or `--help`:

| Tool | Command | Expected |
|------|---------|----------|
| PlatformIO | `pio --version` | 6.x |
| AVR-GCC | `avr-gcc --version` | 12.x+ |
| simavr | `simavr --help` | Help output |
| Wokwi CLI | `wokwi --version` | 2.x |
| GTKWave | `gtkwave --version` | 3.x |

## Install Script Requirements

1. Check for AUR helper (yay/paru) - warn if missing
2. Install official packages first (pacman)
3. Then AUR packages (yay/paru)
4. Then pipx/npm packages
5. Each step with verification
6. Error on any failure, don't continue

## Risk Assessment

- **AUR package stale**: Check AUR page comments before running
- **Node.js version**: Wokwi CLI requires Node 18+. Arch ships 20.x, should be fine.
- **pipx PATH**: Ensure ~/.local/bin in PATH after install

## References

- PlatformIO: https://platformio.org/
- simavr AUR: https://aur.archlinux.org/packages/simavr
- Wokwi: https://wokwi.com/