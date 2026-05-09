# Feature Specification: Testing and Documentation Audit with Action Plan

**Feature Branch**: `003-test-docs-audit`  
**Created**: 2026-05-05  
**Status**: Draft  
**Input**: User description: "Audit CW Trainer Testing & Documentation — Generate Action Plan"

## User Scenarios & Testing *(mandatory)*

### User Story 1 - Understand Current Testing State (Priority: P1)

As a developer working on the CW Trainer project, I want a complete inventory of existing tests and their coverage so that I know what is already verified and what risks exist in untested code.

**Why this priority**: Without knowing what is tested, every change risks regressions. This is the foundation for all other quality work.

**Independent Test**: Can be validated by reviewing the audit output against the actual file tree — every `.cpp` and `.ino` file should be accounted for as covered, partially covered, or uncovered.

**Acceptance Scenarios**:

1. **Given** the project contains source files across multiple directories, **When** the audit runs, **Then** every module is classified by test coverage status (full / partial / none / not-testable).
2. **Given** tests exist in the project test directories, **When** the audit runs, **Then** each test file is mapped to the module it exercises, and gaps are explicitly listed.

---

### User Story 2 - Assess Documentation Completeness (Priority: P2)

As a developer or future contributor, I want to know whether existing specs, READMEs, and architectural docs are complete and current so that I can onboard quickly and make informed design decisions.

**Why this priority**: Documentation-first specification is a constitutional principle. Incomplete docs block contributors and lead to inconsistent implementations.

**Independent Test**: Can be validated by checking that every major directory (`lib/hal/`, `src/`, `libraries/`, `specs/`) has a corresponding documentation artifact and that listed files exist.

**Acceptance Scenarios**:

1. **Given** the project maintains numbered feature specifications, **When** the audit runs, **Then** each spec is checked for completeness against the established project pattern.
2. **Given** the project uses a hardware abstraction layer, **When** the audit runs, **Then** there is documented evidence explaining the contract, the directory structure rationale, and the dual-target build rationale.

---

### User Story 3 - Receive Prioritized Action Plan (Priority: P3)

As the project maintainer, I want a concrete, prioritized action plan so that I can incrementally improve test coverage and documentation without boiling the ocean.

**Why this priority**: An audit without action is shelfware. The plan must be chunked into immediate, short-term, and medium-term work.

**Independent Test**: Can be validated by verifying each action item has a file path or module name, an acceptance criterion, and a priority bucket.

**Acceptance Scenarios**:

1. **Given** gaps are identified in testing and documentation, **When** the action plan is generated, **Then** each item is categorized as Immediate, Short-Term, or Medium-Term with clear rationale.
2. **Given** the project has limited RAM/Flash (Arduino Nano), **When** the action plan recommends new tests or modules, **Then** embedded constraints are explicitly considered.

---

### Edge Cases

- What happens when a file contains logic that cannot be unit-tested without hardware? (Must be classified as "requires mocking" or "integration/HIL only.")
- How does the audit handle third-party code in external libraries? (Must classify as external and note whether wrapper tests or interface tests are needed.)
- What if the test runner fails in the current environment? (Audit must record the failure state and recommend remediation.)

## Requirements *(mandatory)*

### Functional Requirements

- **FR-001**: System MUST inventory all existing test files and classify them by framework, target environment, and the module they exercise.
- **FR-002**: System MUST inventory all existing documentation and classify completeness against the established project pattern.
- **FR-003**: System MUST assess the legacy monolithic code for modularity and testability, reporting how much logic remains in the monolith versus extracted modules.
- **FR-004**: System MUST evaluate the hardware abstraction layer for contract completeness, leakage of platform-specific dependencies into non-HAL code, and dual-target build correctness.
- **FR-005**: System MUST evaluate the build system for correct dual-target configuration and test runner setup.
- **FR-006**: System MUST identify the biggest untested surface area, the most critical undocumented behavior, and the quickest win for test coverage.
- **FR-007**: System MUST produce a prioritized action plan with Immediate, Short-Term, and Medium-Term buckets, each containing concrete tasks with module references and acceptance criteria.
- **FR-008**: System MUST identify new specification directories needed to cover gaps, following the existing numbering pattern.
- **FR-009**: System MUST include a risk register listing risks related to embedded constraints, test determinism, and TDD adoption blockers.
- **FR-010**: System MUST respect project constitutional principles: test-first development, documentation-first specification, and deterministic, repeatable tests.

### Key Entities

- **Audit Report**: The artifact containing findings across testing, documentation, and code structure. Attributes: scope, findings per module, gap summary.
- **Action Plan**: The artifact containing prioritized tasks. Attributes: priority bucket, task description, acceptance criteria, file paths affected.
- **Risk Register**: The artifact listing risks. Attributes: risk description, likelihood, impact, mitigation.

## Success Criteria *(mandatory)*

### Measurable Outcomes

- **SC-001**: 100% of source and test files in the repository are accounted for in the audit report with a coverage classification.
- **SC-002**: The action plan contains at least one Immediate action that can be completed in a single session, with a clear module reference and acceptance criterion.
- **SC-003**: Every public interface in the hardware abstraction layer is either documented or explicitly flagged as missing documentation.
- **SC-004**: The risk register identifies at least the top three blockers to test-first adoption, each with a proposed mitigation.
- **SC-005**: All existing feature specifications are checked for completeness against the project pattern, with a pass/fail result per spec.

## Assumptions

- The audit covers the current state of the repository as of the execution date; it does not require historical version control analysis.
- Target test coverage for logic modules is assumed to be 80% or higher for host-native tests; hardware-specific code may have lower coverage if deterministic testing requires mocking not yet in place.
- The project continues to support resource-constrained embedded targets, so any recommended test or modularization strategy must be embeddable.
- Third-party code in external library directories is treated as an external dependency; the audit focuses on interface coverage rather than modifying library internals.
- The existing specification pattern is the authoritative standard for documentation completeness.
