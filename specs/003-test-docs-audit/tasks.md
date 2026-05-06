# Tasks: Testing and Documentation Audit with Action Plan

**Input**: Design documents from `specs/003-test-docs-audit/`
**Prerequisites**: plan.md (required), spec.md (required), research.md, data-model.md

**Organization**: Tasks grouped by user story. This is a documentation/analysis feature — no code changes, no test tasks.

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this belongs to (US1, US2, US3)

---

## Phase 1: Setup (Repository Inventory)

**Purpose**: Catalog the entire repository to establish audit scope

- [x] T001 [P] List all source files: `find cw-trainer/ lib/ src/ libraries/ -type f \( -name "*.cpp" -o -name "*.ino" -o -name "*.h" \) | sort`
- [x] T002 [P] List all test files: `find test/ -type f | sort`
- [x] T003 [P] List all spec and doc files: `find specs/ docs/ -type f | sort`
- [x] T004 [P] Read `platformio.ini` and record build environments and test targets
- [x] T005 [P] Read `README.md` and record current project description

**Checkpoint**: Complete file inventory exists; every file in repo is accounted for in at least one task.

---

## Phase 2: Foundational (Read & Classify All Artifacts)

**Purpose**: Read every artifact that will be audited so subsequent phases have raw data

**⚠️ CRITICAL**: No analysis tasks can begin until all files are read and summarized

- [x] T006 [P] Read and summarize `cw-trainer/cw-trainer.ino` — record: line count, function count, Arduino dependencies, logic categories (UI, game, pedagogy, CW engine)
- [x] T007 [P] Read and summarize `lib/hal/hal.h` — record: functions declared, data types, completeness of contract
- [x] T008 [P] Read and summarize `lib/hal/hal_nano.cpp` and `lib/hal/hal_desktop.cpp` — record: which functions are implemented per target, gaps
- [x] T009 [P] Read and summarize `src/nano/main.cpp` and `src/desktop/main.cpp` — record: entry point complexity, what modules they call
- [x] T010 [P] Read and summarize `test/test_hal.cpp` — record: test count, coverage of hal.h functions, framework used
- [x] T011 [P] Read and summarize `test/desktop/` contents — record: files present, framework, coverage
- [x] T012 [P] Read and summarize `test/wokwi/smoke-test.yaml` — record: scenarios covered, missing scenarios
- [x] T013 [P] Read and summarize `libraries/morseIO/MorseEnDecoder.cpp` and `.h` — record: API surface, testability, external dependency status
- [x] T014 [P] Read and summarize all files in `specs/001-tool-install/` — record: completeness against 5-file pattern
- [x] T015 [P] Read and summarize all files in `specs/002-pio-project/` — record: completeness against 5-file pattern
- [x] T016 [P] Read `docs/tool-install.md` and `scripts/install-arch.sh` — record: accuracy, completeness

**Checkpoint**: Every file in the repo has a one-paragraph summary. Raw data ready for gap analysis.

---

## Phase 3: User Story 1 - Understand Current Testing State (Priority: P1) 🎯 MVP

**Goal**: Produce the testing-state section of the audit report

**Independent Test**: Verify that every `.cpp` and `.ino` file is classified by coverage status

- [x] T017 [US1] Classify each source module by coverage: `full`, `partial`, `none`, `not-testable`, `external`
- [x] T018 [US1] Identify test framework in use (Unity via PlatformIO native env)
- [x] T019 [US1] Determine whether `pio test -e native` passes (run it; record result)
- [x] T020 [US1] Determine whether `pio test -e nano` passes or is expected to fail (run it; record result)
- [x] T021 [US1] Assess test organization: are tests grouped by module or scattered?
- [x] T022 [US1] Identify biggest untested surface area by line count and logic criticality
- [x] T023 [US1] Identify quickest win for test coverage (smallest effort, highest value)

**Checkpoint**: Testing state report is complete and accurate. Every module has a coverage classification.

---

## Phase 4: User Story 2 - Assess Documentation Completeness (Priority: P2)

**Goal**: Produce the documentation-state section of the audit report

**Independent Test**: Verify every major directory has a documentation classification

- [x] T024 [US2] Check `specs/001-tool-install/` for completeness against 5-file pattern (`spec.md`, `plan.md`, `tasks.md`, `research.md`, `quickstart.md`)
- [x] T025 [US2] Check `specs/002-pio-project/` for completeness against 5-file pattern
- [x] T026 [US2] Check `CLAUDE.md` for constitution presence and version; verify it is followed in existing code
- [x] T027 [US2] Check `README.md` for accuracy against current repo state
- [x] T028 [US2] Check for architectural docs explaining `lib/hal/` vs `src/` vs `libraries/`
- [x] T029 [US2] Check for data model or state machine diagram for trainer logic
- [x] T030 [US2] Check for timing constraints documentation (Morse speed, Farnsworth, debounce)
- [x] T031 [US2] Identify most critical undocumented behavior

**Checkpoint**: Documentation state report is complete. Every spec directory has a pass/fail completeness result.

---

## Phase 5: User Story 3 - Receive Prioritized Action Plan (Priority: P3)

**Goal**: Produce the action plan, per-file recommendations, new spec list, test suite expansion plan, and risk register

**Independent Test**: Verify the action plan has at least one Immediate action and the risk register has ≥3 entries

- [x] T032 [US3] Draft Executive Summary with: current coverage %, documentation completeness %, biggest risk, recommended first sprint
- [x] T033 [US3] Draft Immediate Actions (this session) — concrete tasks with file paths
- [x] T034 [US3] Draft Short-Term Actions (next 1-2 sprints) — tasks with acceptance criteria
- [x] T035 [US3] Draft Medium-Term Actions (next month) — architectural changes with rationale
- [x] T036 [US3] Draft Per-File Recommendations for every relevant file
- [x] T037 [US3] Draft New Specs to Create list with `specs/###-name/` directories
- [x] T038 [US3] Draft Test Suite Expansion Plan: module name, test file path, first test case, dependencies to mock
- [x] T039 [US3] Draft Risk Register with ≥3 risks: likelihood, impact, mitigation
- [x] T040 [US3] Compile all sections into single audit document suitable for `CLAUDE.md` append or `specs/000-audit-and-plan/plan.md`

**Checkpoint**: Action plan is complete, prioritized, and actionable. Every item has a module reference and acceptance criterion.

---

## Phase 6: Polish & Cross-Cutting Concerns

**Purpose**: Validate audit quality and ensure cross-references are correct

- [x] T041 [P] Cross-check: every file path referenced in the audit exists in the repo
- [x] T042 [P] Cross-check: every module coverage classification is justified by a file summary from Phase 2
- [x] T043 [P] Cross-check: action plan items map to specific gaps identified in US1 and US2
- [x] T044 [P] Verify audit document follows constitutional principles: test-first, documentation-first, deterministic tests
- [x] T045 Run quickstart.md validation steps

**Checkpoint**: Audit is internally consistent and ready for consumption.

---

## Dependencies & Execution Order

### Phase Dependencies

- **Setup (Phase 1)**: No dependencies — can start immediately
- **Foundational (Phase 2)**: Depends on Setup completion — BLOCKS all user stories
- **User Stories (Phase 3-5)**: All depend on Foundational phase completion
  - US1 and US2 can proceed in parallel (different analysis domains)
  - US3 depends on US1 and US2 (needs their findings to build action plan)
- **Polish (Phase 6)**: Depends on all user story phases

### User Story Dependencies

- **User Story 1 (P1)**: Can start after Foundational (Phase 2). No dependencies on other stories.
- **User Story 2 (P2)**: Can start after Foundational (Phase 2). No dependencies on other stories. Can run in parallel with US1.
- **User Story 3 (P3)**: Depends on US1 and US2. Cannot start until both have findings.

### Within Each User Story

- US1: Inventory → Classification → Gap identification
- US2: Completeness check → Missing docs list → Critical gap flag
- US3: Summary → Actions → Recommendations → Risk register

### Parallel Opportunities

- All Phase 1 tasks marked [P] can run in parallel
- All Phase 2 tasks marked [P] can run in parallel (different files)
- US1 and US2 can be worked on in parallel once Phase 2 is done
- All Phase 6 tasks marked [P] can run in parallel

---

## Parallel Example: User Story 1

```bash
# Launch all US1 analysis tasks together:
Task: "Classify each source module by coverage"
Task: "Determine whether pio test -e native passes"
Task: "Determine whether pio test -e nano passes"
Task: "Assess test organization"
Task: "Identify biggest untested surface area"
Task: "Identify quickest win for test coverage"
```

---

## Implementation Strategy

### MVP First (User Story 1 Only)

1. Complete Phase 1: Setup
2. Complete Phase 2: Foundational
3. Complete Phase 3: User Story 1 (testing state)
4. **STOP and VALIDATE**: Verify every module has coverage classification
5. If time remains, proceed to US2 and US3

### Incremental Delivery

1. Setup + Foundational → Raw data ready
2. Add US1 → Testing audit complete → Deliverable chunk 1
3. Add US2 → Documentation audit complete → Deliverable chunk 2
4. Add US3 → Action plan complete → Final deliverable
5. Each chunk adds value without redoing previous work

### Parallel Team Strategy

With multiple developers:

1. Team completes Setup + Foundational together
2. Once Foundational is done:
   - Developer A: US1 (testing state)
   - Developer B: US2 (documentation state)
3. Both developers sync findings to Developer C for US3 (action plan)

---

## Notes

- [P] tasks = different files, no dependencies
- [Story] label maps task to specific user story for traceability
- Each user story produces an independently readable section of the audit
- No code changes in this feature — all tasks are read, classify, and write
- Stop at any checkpoint to validate story independently
- Avoid: vague tasks, same file conflicts, cross-story dependencies that break independence
