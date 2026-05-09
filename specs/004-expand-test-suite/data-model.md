# Data Model: Expand Test Suite for Missing Coverage

**Feature**: Expand Test Suite for Missing Coverage  
**Date**: 2026-05-05

## Entity: HALFunction

Represents a single function in the HAL contract.

| Field | Type | Description |
|-------|------|-------------|
| `name` | string | Function name (e.g., `hal_millis`) |
| `return_type` | string | Return type (e.g., `uint32_t`, `void`, `bool`) |
| `parameters` | list&lt;Param&gt; | Input parameters with types |
| `category` | enum | `time`, `tone`, `input`, `lcd`, `eeprom`, `random`, `debug` |
| `has_test` | bool | Whether a test exists |
| `test_file` | string | Path to test file containing this function's tests |

## Entity: Param

Represents a function parameter.

| Field | Type | Description |
|-------|------|-------------|
| `type` | string | C type (e.g., `uint16_t`, `const char*`) |
| `name` | string | Parameter name |

## Entity: TestCase

Represents a single Unity test function.

| Field | Type | Description |
|-------|------|-------------|
| `name` | string | Test function name (e.g., `test_hal_millis_starts_at_zero`) |
| `target_function` | string | HAL function under test |
| `description` | string | What the test verifies |
| `assertions` | list&lt;string&gt; | Unity assertions used (e.g., `TEST_ASSERT_EQUAL_UINT32`) |
| `deterministic` | bool | Whether test uses only seeded/controlled inputs |

## Entity: MockState

Represents inspectable state in the desktop HAL.

| Field | Type | Description |
|-------|------|-------------|
| `buffer` | string | Name of mock buffer (e.g., `g_lcd_buffer`, `g_eeprom`) |
| `size` | int | Buffer size in bytes |
| `accessor` | string | Test helper to read state (e.g., `test_lcd_get_row`) |

## Entity: TestDirectory

Represents the test file organization.

| Field | Type | Description |
|-------|------|-------------|
| `env` | string | PlatformIO environment (e.g., `desktop`) |
| `path` | string | Directory path (e.g., `test/desktop/`) |
| `test_files` | list&lt;string&gt; | Test files in this directory |
| `modules_covered` | list&lt;string&gt; | Module names covered by tests here |
