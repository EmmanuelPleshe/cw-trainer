# Tasks: 001-tool-install

**Input**: Design documents from `/specs/001-tool-install/`
**Prerequisites**: plan.md (required)

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this task belongs to (not applicable for this setup task)

---

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Create install scripts and documentation

- [X] T001 Create scripts directory at repository root
- [X] T002 Create docs directory at repository root
- [X] T003 [P] Create install-arch.sh script in scripts/
- [X] T004 [P] Create tool-install.md documentation in docs/
- [X] T005 Make install-arch.sh executable (chmod +x)
- [X] T006 Verify script syntax with bash -n

---

## Phase 2: Verification

**Purpose**: Verify created artifacts

- [X] T007 Test install script syntax: `bash -n scripts/install-arch.sh`
- [X] T008 Verify docs/tool-install.md has all required sections
- [X] T009 Verify quickstart.md in specs matches install script

---

## Phase 3: Polish

**Purpose**: Final review and cleanup

- [X] T010 Review install-arch.sh for completeness
- [X] T011 Review tool-install.md for accuracy
- [X] T012 Update CLAUDE.md with new docs reference

---

## Dependency Graph

```
T001 ─┬─► T003 ─► T005 ─► T007 ─► T010
T002 ─┘    └──────────► T004 ─► T006 ─► T008 ─► T011
                                          └─► T009 ─► T012
```

**Parallel Opportunities**:
- T003 and T004 can run in parallel (different output files)
- T005 and T006 can run in parallel

## Implementation Strategy

This is a documentation/setup task. MVP scope = Phase 1 complete (install script + docs). Phase 2 verifies correctness. Phase 3 polishes.

## Independent Test Criteria

- `bash -n scripts/install-arch.sh` exits 0 (valid syntax)
- `ls scripts/install-arch.sh` exists and is executable
- `ls docs/tool-install.md` exists and is readable
- install-arch.sh contains all required tool installations

---

## Summary

- **Total tasks**: 12
- **Parallelizable tasks**: 2
- **MVP scope**: Phase 1 (T001-T006)