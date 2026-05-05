# Quickstart: Testing and Documentation Audit

**Feature**: Testing and Documentation Audit with Action Plan  
**Date**: 2026-05-05

## How to Read the Audit

The audit output lives in `specs/003-test-docs-audit/` and is designed to be consumed in this order:

1. **`spec.md`** — The specification that drove this audit. Read first for scope and success criteria.
2. **`plan.md`** — Implementation plan showing how the audit was structured.
3. **`research.md`** — Decisions made during the audit (no technology choices; mostly scope and classification rules).
4. **`data-model.md`** — Entity definitions for audit artifacts (ModuleCoverage, ActionItem, Risk, etc.).

## How to Use the Action Plan

The action plan will be generated in `/speckit-tasks` as `tasks.md`. Consume it as follows:

### Immediate Actions (This Session)
- Pick one. Complete it. Commit.
- Do not start a second until the first is verified.

### Short-Term Actions (Next 1-2 Sprints)
- Convert each into a new `specs/###-feature-name/` directory.
- Follow the established pattern: `spec.md` → `plan.md` → `tasks.md`.

### Medium-Term Actions (Next Month)
- Treat as architectural initiatives. Write a spec per initiative.
- Example: "Extract all logic from `cw-trainer.ino` into `lib/core/`" becomes its own spec.

## How to Re-Run the Audit

This audit is a snapshot. To update it:

1. Create a new spec directory (e.g., `specs/004-test-docs-audit-v2/`).
2. Re-run the same specification against the updated repo.
3. Compare against `003` to measure progress.

## Verification

- [ ] Every source module in the repo has a coverage classification.
- [ ] Every spec directory is checked for completeness.
- [ ] The action plan has at least one Immediate action.
- [ ] The risk register has at least three entries.
- [ ] All findings reference specific file paths or module names.
