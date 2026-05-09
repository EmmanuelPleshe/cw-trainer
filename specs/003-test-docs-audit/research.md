# Research: Testing and Documentation Audit

**Feature**: Testing and Documentation Audit with Action Plan  
**Date**: 2026-05-05  
**Status**: Complete

## Decisions

### RD-001: Audit scope is read-only analysis of existing state

**Decision**: The audit does not modify any source files, tests, or specs. It reads and classifies only.

**Rationale**: This is a documentation/analysis feature. Code changes are out of scope for spec `003`. Actionable code changes belong in future specs derived from this audit's action plan.

**Alternatives considered**:
- Inline fixes during audit — rejected. Violates "audit before action" principle and makes the audit non-repeatable.

### RD-002: Test coverage classification uses five-state model

**Decision**: Every module classified as one of: `full`, `partial`, `none`, `not-testable`, `external`.

**Rationale**: Five states cover all cases in this repo:
- `full`: Tests exist and cover primary logic paths
- `partial`: Tests exist but miss edge cases or paths
- `none`: No tests
- `not-testable`: Hardware-dependent code that requires HIL/simulation
- `external`: Third-party code (libraries/morseIO/)

### RD-003: Deterministic test requirement is absolute

**Decision**: Any test relying on `millis()`, `random()`, or hardware timing without injection is classified as non-deterministic.

**Rationale**: Constitution Article I mandates deterministic tests. This audit must flag non-deterministic tests as gaps.

### RD-004: Existing spec pattern is the completeness standard

**Decision**: A spec directory is "complete" when it contains all five files: `spec.md`, `plan.md`, `tasks.md`, `research.md`, `quickstart.md`.

**Rationale**: Constitution Article II.2 defines the pattern. The audit checks against this standard.

## Unknowns Resolved

| Unknown | Resolution | Source |
|---------|-----------|--------|
| Test framework in use | Unity via PlatformIO `native` env | `platformio.ini` and `test/test_hal.cpp` |
| Dual-target build config | `nano` and `native` environments defined | `platformio.ini` |
| HAL contract completeness | Assessed by reading `lib/hal/hal.h` | Source analysis |
| Monolith testability | Assessed by reading `cw-trainer/cw-trainer.ino` | Source analysis |
| Existing spec completeness | Checked `specs/001-tool-install/` and `specs/002-pio-project/` | Directory inspection |

## Open Questions (for future specs, not this audit)

- Should `lib/core/` be created before or after HAL tests are complete? (Out of scope for audit; action plan will recommend order.)
- What is the target branch coverage threshold for legacy code extraction? (Constitution says ≥80% for new code; legacy migration may have different threshold.)
