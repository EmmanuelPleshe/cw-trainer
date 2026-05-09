# Implementation Plan: Testing and Documentation Audit with Action Plan

**Branch**: `003-test-docs-audit` | **Date**: 2026-05-05 | **Spec**: [spec.md](spec.md)
**Input**: Feature specification from `specs/003-test-docs-audit/spec.md`

## Summary

Audit existing testing and documentation state across the CW Trainer repository, then produce a prioritized action plan. Deliverables: audit report, gap analysis, per-file recommendations, new spec list, test suite expansion plan, and risk register. This is a documentation/analysis feature with no runtime code changes.

## Technical Context

**Language/Version**: N/A (audit/documentation task; outputs are Markdown)  
**Primary Dependencies**: None  
**Storage**: N/A  
**Testing**: Audit validates against existing `pio test` and `platformio.ini`  
**Target Platform**: N/A  
**Project Type**: documentation / analysis  
**Performance Goals**: N/A  
**Constraints**: Must respect existing repo structure; must follow constitutional principles; must account for Arduino Nano constraints (2KB SRAM, 32KB Flash)  
**Scale/Scope**: Single repository; all `.cpp`, `.ino`, `.h`, `.md`, `.yaml` files under `cw-trainer/`, `lib/`, `src/`, `libraries/`, `test/`, `specs/`, `docs/`

## Constitution Check

*GATE: Must pass before Phase 0 research. Re-check after Phase 1 design.*

| Gate | Check | Status |
|------|-------|--------|
| I. Hardware-First | Audit accounts for ATmega328P constraints in recommendations | Pass |
| II. Memory Discipline | No code changes; audit will flag any new test overhead against SRAM budget | Pass |
| III. Layered Architecture | Audit evaluates whether boundaries (UI → Game → Pedagogy → CW Engine → HAL) are documented and respected | Pass |
| IV. Test-First | Audit itself does not add code, but the action plan must mandate test-first for all subsequent features | Pass |
| V. Code Quality Standards | Audit evaluates naming, function length, and Arduino leakage in existing code | Pass |

No constitutional violations. All gates pass.

## Project Structure

### Documentation (this feature)

```text
specs/003-test-docs-audit/
├── plan.md              # This file
├── research.md          # Phase 0 output
├── data-model.md        # Phase 1 output (entity definitions for audit artifacts)
├── quickstart.md        # Phase 1 output (how to consume the audit)
├── contracts/           # N/A — no new interfaces
└── tasks.md             # Phase 2 output (/speckit-tasks)
```

### Source Code (repository root)

No source code changes for this feature. The audit reads from existing tree:

```text
cw-trainer/
├── cw-trainer/cw-trainer.ino          # Legacy monolith (assessed)
├── lib/hal/hal.h                      # HAL contract (assessed)
├── lib/hal/hal_nano.cpp               # Nano HAL impl (assessed)
├── lib/hal/hal_desktop.cpp            # Desktop HAL impl (assessed)
├── src/nano/main.cpp                  # Nano entry (assessed)
├── src/desktop/main.cpp               # Desktop entry (assessed)
├── test/test_hal.cpp                  # Existing HAL tests (assessed)
├── test/desktop/                      # Desktop tests (assessed)
├── test/wokwi/smoke-test.yaml         # Wokwi smoke test (assessed)
├── libraries/morseIO/                 # External Morse lib (assessed)
├── specs/001-tool-install/            # Existing spec (assessed)
├── specs/002-pio-project/             # Existing spec (assessed)
├── platformio.ini                     # Build config (assessed)
├── README.md                          # Project readme (assessed)
└── docs/tool-install.md               # Tool docs (assessed)
```

**Structure Decision**: Audit reads existing tree as-is. No structural changes required.

## Complexity Tracking

No violations. This feature is pure documentation/analysis.
