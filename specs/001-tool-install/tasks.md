# Tasks: 001-tool-install

**Input**: Design documents from `/specs/001-tool-install/`
**Prerequisites**: plan.md (required)

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this task belongs to (not applicable for this setup task)

---

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Create install scripts and documentation

- [ ] T001 Create scripts directory at repository root
- [ ] T002 Create docs directory at repository root
- [ ] T003 [P] Create install-arch.sh script in scripts/
- [ ] T004 [P] Create tool-install.md documentation in docs/
- [ ] T005 Make install-arch.sh executable (chmod +x)
- [ ] T006 Verify script syntax with bash -n

---

## Phase 2: Verification

**Purpose**: Verify created artifacts

- [ ] T007 Test install script syntax: `bash -n scripts/install-arch.sh`
- [ ] T008 Verify docs/tool-install.md has all required sections
- [ ] T009 Verify quickstart.md in specs matches install script

---

## Phase 3: Polish

**Purpose**: Final review and cleanup

- [ ] T010 Review install-arch.sh for completeness
- [ ] T011 Review tool-install.md for accuracy
- [ ] T012 Update CLAUDE.md with new docs reference

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