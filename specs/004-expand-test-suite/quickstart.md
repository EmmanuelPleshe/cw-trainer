# Quickstart: Expand Test Suite for Missing Coverage

**Feature**: Expand Test Suite for Missing Coverage  
**Date**: 2026-05-05

## How to Run the Expanded Test Suite

### Desktop (Native) Tests

```bash
# Run all tests in test/desktop/
pio test -e desktop

# Expected output:
# Environment    Test      Status    Duration
# -------------  --------  --------  ------------
# desktop        test_hal  PASSED    00:00:00.xxx
# 17 test cases: 17 succeeded
```

### Nano (Compilation Gate)

```bash
# Build only (no upload expected without hardware)
pio test -e nano --without-upload

# Or just compile:
pio run -e nano
```

## How to Verify Acceptance Criteria

| Criterion | Verification Command | Expected Result |
|-----------|---------------------|------------------|
| SC-001: 100% HAL functions tested | `grep "RUN_TEST" test/desktop/test_hal.cpp | wc -l` | ≥17 |
| SC-002: Zero duplicated mocks | `grep -c "uint32_t hal_millis" test/desktop/test_hal.cpp` | 0 (no re-implementation) |
| SC-003: All tests pass | `pio test -e desktop` | `PASSED` for all |
| SC-004: Under 5 seconds | `time pio test -e desktop` | real <5s |
| SC-005: Deterministic | Run `pio test -e desktop` 3× | Identical pass/fail each time |

## How to Add a New HAL Test

1. Open `test/desktop/test_hal.cpp`
2. Add a `setUp` reset call if your test needs clean state
3. Write test function following pattern:
   ```cpp
   void test_hal_[function]_[scenario](void) {
       // Arrange
       test_eeprom_reset();
       // Act
       hal_eeprom_write(0, 42);
       // Assert
       TEST_ASSERT_EQUAL_UINT8(42, hal_eeprom_read(0));
   }
   ```
4. Add `RUN_TEST(test_hal_[function]_[scenario]);` in `main()`
5. Run `pio test -e desktop` to verify

## How to Add a Future Module Test

1. Create `test/desktop/test_[module].cpp`
2. Include `unity.h` and module headers
3. Follow Unity `setUp`/`tearDown`/`RUN_TEST` pattern
4. Run `pio test -e desktop` — PlatformIO auto-discovers new files

## Verification Checklist

- [ ] `pio test -e desktop` passes with 17+ tests
- [ ] No HAL function re-implemented in test files
- [ ] `test/desktop/` contains organized test files
- [ ] `test/test_hal.cpp` at root is removed or empty
- [ ] `pio run -e nano` compiles with zero errors
- [ ] All tests produce identical results on repeated runs
