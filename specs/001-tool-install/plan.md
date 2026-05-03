# Implementation Plan: 001-tool-install

**Branch**: `001-tool-install` | **Date**: 2026-05-02 | **Spec**: [spec.md](./spec.md)
**Input**: Feature specification from `/specs/001-tool-install/spec.md`

## Summary

Install and verify SpeckIT development toolchain on EndeavourOS/Arch Linux. Create one-shot install script and verification procedure for Tier 1-3 simulation stack (PlatformIO, AVR toolchain, simavr, Wokwi CLI).

## Technical Context

**Language/Version**: Shell scripts (Bash) | **Primary Dependencies**: pacman, yay/paru, pipx, npm
**Storage**: N/A | **Testing**: Verification scripts (pio, simavr, wokwi --version checks)
**Target Platform**: EndeavourOS/Arch Linux (x86_64) | **Project Type**: Dev environment setup
**Performance Goals**: N/A | **Constraints**: Must work on clean Arch install
**Scale/Scope**: Single developer machine setup

## Constitution Check

| Gate | Status | Notes |
|------|--------|-------|
| I. Hardware-First | N/A | No embedded code - documentation only |
| II. Memory Discipline | N/A | No embedded code |
| III. Layered Architecture | N/A | No code modules |
| IV. Test-First | PASS | Verification via `--version` checks |
| V. Code Quality | N/A | Shell scripts - no C++ |

**Result**: GATE PASS (no embedded code, verification applies)

## Project Structure

### Documentation (this feature)

```text
specs/001-tool-install/
├── plan.md              # This file
├── research.md          # Phase 0 (tool versions, AUR status)
├── quickstart.md        # Phase 1 (quick start guide)
├── install.sh           # Phase 1 (one-shot install script)
└── tasks.md             # Phase 2 (/speckit-tasks output)
```

### Source Code (repository root)

This feature adds install scripts to repository root:

```text
scripts/
└── install-arch.sh      # One-shot Arch install script

docs/
└── tool-install.md      # Detailed Arch installation guide
```

**Structure Decision**: Add `scripts/install-arch.sh` and `docs/tool-install.md`. No PlatformIO project structure yet - this is just tool installation.

## Complexity Tracking

> Not applicable - no constitution violations.

---

## Phase 0: Research

**Research Tasks**:

1. **Tool Version Compatibility**: Verify latest tool versions work together
   - PlatformIO 6.x vs 5.x
   - simavr AUR package version
   - Wokwi CLI Node.js requirements

2. **AUR Package Status**: Check if simavr and avr-gdb packages are still maintained
   - Last updated date
   - Dependencies
   - Known issues

3. **Verification Strategy**: How to confirm each tool works
   - PlatformIO: `pio --version`
   - AVR-GCC: `avr-gcc --version`
   - simavr: `simavr --help`
   - Wokwi: `wokwi --version`

**Output**: `research.md`