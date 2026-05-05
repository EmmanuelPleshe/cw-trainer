# Data Model: Testing and Documentation Audit

**Feature**: Testing and Documentation Audit with Action Plan  
**Date**: 2026-05-05

## Entity: Audit Report

Represents the complete findings of the audit across testing, documentation, and code structure.

| Field | Type | Description |
|-------|------|-------------|
| `scope` | string | What was audited (directories, file types) |
| `modules_tested` | list&lt;ModuleCoverage&gt; | Per-module coverage classification |
| `modules_documented` | list&lt;ModuleDoc&gt; | Per-module documentation status |
| `specs_checked` | list&lt;SpecCheck&gt; | Per-spec completeness result |
| `gap_summary` | string | Top-line gap analysis |
| `biggest_untested` | string | Module with largest untested surface |
| `most_critical_undocumented` | string | Most critical missing documentation |
| `quickest_win` | string | Lowest-effort, highest-value test to add |

## Entity: ModuleCoverage

Represents the test coverage state of a single source module.

| Field | Type | Description |
|-------|------|-------------|
| `module_name` | string | Human-readable module name |
| `source_files` | list&lt;string&gt; | Paths to source files in this module |
| `test_files` | list&lt;string&gt; | Paths to tests covering this module |
| `classification` | enum | `full` / `partial` / `none` / `not-testable` / `external` |
| `framework` | string | Test framework (Unity, Catch2, custom, N/A) |
| `target_env` | string | `native`, `nano`, `wokwi`, `N/A` |
| `gaps` | list&lt;string&gt; | What is missing |

## Entity: ModuleDoc

Represents the documentation state of a module or directory.

| Field | Type | Description |
|-------|------|-------------|
| `module_name` | string | Human-readable module name |
| `directory` | string | Directory path |
| `has_readme` | bool | README or overview doc exists |
| `has_architecture_doc` | bool | Architecture/contract doc exists |
| `has_api_doc` | bool | API reference exists |
| `missing` | list&lt;string&gt; | List of missing docs |

## Entity: SpecCheck

Represents the completeness check of an existing spec directory.

| Field | Type | Description |
|-------|------|-------------|
| `spec_dir` | string | Path to spec directory |
| `has_spec_md` | bool | |
| `has_plan_md` | bool | |
| `has_tasks_md` | bool | |
| `has_research_md` | bool | |
| `has_quickstart_md` | bool | |
| `completeness` | enum | `complete` / `incomplete` |
| `missing` | list&lt;string&gt; | Missing files |

## Entity: Action Plan

Represents the prioritized work items derived from the audit.

| Field | Type | Description |
|-------|------|-------------|
| `immediate_actions` | list&lt;ActionItem&gt; | Can complete this session |
| `short_term_actions` | list&lt;ActionItem&gt; | 1-2 sprints |
| `medium_term_actions` | list&lt;ActionItem&gt; | Next month |

## Entity: ActionItem

Represents a single actionable task.

| Field | Type | Description |
|-------|------|-------------|
| `priority` | enum | `immediate` / `short_term` / `medium_term` |
| `description` | string | What to do |
| `module_ref` | string | Module or file path affected |
| `acceptance_criteria` | string | How to verify completion |
| `rationale` | string | Why this matters |

## Entity: RiskRegister

Represents the list of risks to TDD adoption and project quality.

| Field | Type | Description |
|-------|------|-------------|
| `risks` | list&lt;Risk&gt; | All identified risks |

## Entity: Risk

Represents a single risk.

| Field | Type | Description |
|-------|------|-------------|
| `description` | string | What could go wrong |
| `likelihood` | enum | `high` / `medium` / `low` |
| `impact` | enum | `high` / `medium` / `low` |
| `mitigation` | string | How to reduce risk |
