# SpeckIT Constitution
<!-- CW Trainer for Arduino Uno R3 -->

## Core Principles

### I. Hardware-First (The Iron Law)
The Arduino Uno R3 is not a suggestion — it is the law. All design decisions must respect ATmega328P constraints: 31.5 KB flash, 2 KB SRAM, 1 KB EEPROM, 16 MHz clock. No `String`, no `malloc`, no float in hot paths, no recursion. PROGMEM for all constant data.

### II. Memory Discipline
SRAM budget: ≤512 B globals, ≤512 B stack, 0 B heap. Use `uint8_t` not `int`, bitfields for flags. Flash: all strings via `F()` or PROGMEM. EEPROM: persistent config + SRS buckets only. Every byte guilty until proven innocent.

### III. Layered Architecture
Clean module boundaries: UI → Game → Pedagogy → CW Engine → HAL. No circular dependencies. Each module exposes C-style API in header. State machines use `enum` + `switch`, not nested `if` spaghetti.

### IV. Test-First (NON-NEGOTIABLE)
TDD mandatory: Tests written → User approved → Tests fail → Then implement. Three tiers: Tier 1 Native (PlatformIO + Unity), Tier 2 simavr (timing), Tier 3 Wokwi (integration). No code merges to main without passing all three tiers.

### V. Code Quality Standards
C++ with Arduino core, write C-style where possible. No STL containers, no exceptions, no RTTI. Naming: UPPER_SNAKE_CASE constants, lower_snake_case functions, g_prefix globals, k_prefix PROGMEM tables. Max 50 lines per function.

## Game Design & Pedagogy

**Modes**: Koch Trainer (90% threshold to advance), Survival (adaptive WPM, 3 lives), Callsign (real-world patterns), Head Copy (forces mental buffer), QSO Fragments (ragchew), Decoder (dynamic decode).

**Koch Progression**: Standard 40-step order: `KMRSUAPTLOWI.NJEF0Y,VG5/Q9ZH38B?427C1D6X`. Start with 2 chars at target speed. Add next only when current set ≥90% accuracy.

**Farnsworth Timing**: Character speed fixed at target WPM. Spacing speed slower via increased inter-character gaps. Formula: `extra_gap = (1200/farnsworthWPM) - (1200/targetWPM)`.

**Spaced Repetition (SRS)**: Each char has bucket 0-4. Correct → bucket up (max 4). Incorrect → bucket 0. Session generator weights by inverse bucket: weak chars appear more often.

## Development Workflow

**Branches**: `main` (always compiles, always flashes), `feature/<name>` (rebase before PR).

**Commits**: Imperative mood, ≤50 chars summary.

**CI Gates**: Compiles for Uno, SRAM usage <80%, no `String` usage. Pre-release: compile check, smoke test, audio test, EEPROM test, stress test, decoder test.

**Version Control & Collaboration**: PRs require review. Retain original attribution (Tom Lewis N4TL, Mike Hughes KC1DMR) in source headers. MIT license for SpeckIT modifications.

## Governance

Constitution supersedes all other practices. Amendments require documentation, approval, and migration plan. All PRs/reviews must verify compliance with hardware constraints and memory budgets. Use Addendum A (Simulation-First) for development guidance.

**Version**: 1.1.0 | **Ratified**: 2026-05-02 | **Last Amended**: 2026-05-02

---

# Addendum A: Simulation-First Development & TDD Scaffolding

## A.1 Philosophy
Hardware is optional. Correctness is mandatory. Every feature must be provably correct through automated tests before it touches silicon. The simulation stack is the primary development environment. Golden rule: If you can't write a test for it, you haven't designed it yet.

## A.2 Three Simulation Tiers

| Tier | Tool | Purpose | Speed |
|------|------|---------|-------|
| Tier 1: Native TDD | PlatformIO `native` + Unity | Algorithmic logic, state machines, math | <1s |
| Tier 2: AVR Simulation | simavr + GDB + VCD | Cycle-accurate timing, ISR behavior | ~10s |
| Tier 3: Full HIL | Wokwi | Complete sketch, LCD, buttons, buzzer | ~30s |

## A.3 Project Structure
```
speckit/
├── lib/               # Shared logic — tested at Tier 1
│   ├── koch/
│   ├── srs/
│   ├── cw_engine/
│   ├── decoder/
│   ├── game/
│   └── hal/           # Hardware Abstraction Layer
├── src/
│   ├── nano/         # Arduino entry point
│   └── desktop/      # Native test runner
├── test/
│   ├── desktop/      # Tier 1 unit tests
│   └── wokwi/        # Tier 3 scenarios
├── simavr/           # Tier 2 scripts
├── wokwi/            # Wokwi project files
└── platformio.ini
```

## A.4 HAL Interface
Every Arduino-specific call must go through HAL. No `digitalWrite`, `tone`, `millis`, or `analogRead` in game logic. HAL provides: time, tone/audio, input (buttons/key), output (LCD), EEPROM, random, LED/debug interfaces.

## A.5 Tier 1: Native Tests
Run with `pio test --environment desktop`. Tests use Unity framework. Mock HAL in `hal_desktop.cpp` provides controllable time, LCD buffer inspection, tone tracking.

## A.6 Tier 2: simavr
Cycle-accurate verification for timing-critical code. Scripts in `simavr/run.sh` with GDB breakpoints and VCD trace output.

## A.7 Tier 3: Wokwi
Integration tests in `test/wokwi/smoke-test.yaml`. Tests boot, menu navigation, Koch session, scoring.

## A.8 TDD Workflow
1. Write failing test → 2. Watch fail → 3. Implement minimal code → 4. Watch pass → 5. Refactor. Promote to Tier 2/3 once logic is solid.

## A.9 Simulation-First Checklist
- [ ] All Tier 1 native tests pass
- [ ] New code has ≥80% branch coverage
- [ ] No `String`, `malloc`, `new`, or `float` in production code
- [ ] All hardware access goes through `hal.h`
- [ ] simavr timing verification passes for audio/timing changes
- [ ] Wokwi smoke test passes in CI
- [ ] SRAM usage reported (target: <1.6 KB)
- [ ] Flash usage reported (target: <28 KB)

## A.10 Tool Installation
```bash
# macOS
brew install platformio simavr avr-gdb

# Ubuntu/Debian
pip install platformio
sudo apt-get install simavr avr-libc gcc-avr gdb-avr
```

---

# Addendum B: EndeavourOS/Arch Tool Installation

EndeavourOS is Arch-based — cleanest path via official repos or AUR. No PPAs, no tarballs.

## B.1 PlatformIO (Tier 1)

```bash
# Option A: pipx (isolated)
sudo pacman -S python-pipx
pipx install platformio

# Option B: venv
python -m venv ~/.venv/speckit
source ~/.venv/speckit/bin/activate
pip install platformio
```

## B.2 AVR Toolchain (Tiers 2-3)

```bash
sudo pacman -S avr-gcc avr-binutils avr-libc avrdude

# avr-gdb: AUR only
yay -S avr-gdb
```

## B.3 simavr (Tier 2)

```bash
yay -S simavr
```

## B.4 GTKWave (Tier 2 VCD viewing)

```bash
sudo pacman -S gtkwave
```

## B.5 Wokwi CLI (Tier 3)

```bash
curl -L https://wokwi.com/ci/install.sh | sh

# Set token from https://wokwi.com/dashboard/ci
export WOKWI_CLI_TOKEN=your-token
```

## B.6 One-Shot Install Script

```bash
#!/bin/bash
set -e

sudo pacman -S --needed \
    base-devel python-pipx nodejs npm \
    avr-gcc avr-binutils avr-libc avrdude gtkwave

pipx install platformio

yay -S --needed simavr avr-gdb
npm install -g @wokwi/cli
```

## B.7 Quick Reference

| Tool | Package | Source |
|------|---------|--------|
| PlatformIO | `platformio` | pipx |
| AVR-GCC | `avr-gcc` | Official |
| AVR-GDB | `avr-gdb` | AUR |
| simavr | `simavr` | AUR |
| GTKWave | `gtkwave` | Official |
| Wokwi CLI | `@wokwi/cli` | npm |
| avrdude | `avrdude` | Official |