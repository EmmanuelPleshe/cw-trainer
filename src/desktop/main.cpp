// SpeckIT Desktop Test Runner
// Entry point for native tests

#ifdef PIO_ENV_DESKTOP

#include <stdio.h>
#include "hal.h"

int main(void) {
    printf("SpeckIT Desktop Test Runner\n");
    printf("============================\n");

    // Initialize HAL
    hal_lcd_init();
    hal_random_seed(42);

    // Print LCD buffer
    printf("LCD Row 0: %.16s\n", test_lcd_get_row(0));
    printf("LCD Row 1: %.16s\n", test_lcd_get_row(1));

    // Test time functions
    printf("Time: %u ms\n", hal_millis());
    test_advance_time(1000);
    printf("Time after 1s: %u ms\n", hal_millis());

    printf("\nTests complete.\n");
    return 0;
}

#endif