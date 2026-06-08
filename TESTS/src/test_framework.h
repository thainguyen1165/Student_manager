#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>

extern int tests_run;
extern int tests_passed;

#define ASSERT(message, test) do { \
    tests_run++; \
    if (!(test)) { \
        printf("  [FAIL] %s:%d %s\n", __FILE__, __LINE__, message); \
    } else { \
        tests_passed++; \
        printf("  [PASS] %s\n", message); \
    } \
} while (0)

#endif
