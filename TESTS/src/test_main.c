#include <stdio.h>
#include "test_framework.h"

int tests_run = 0;
int tests_passed = 0;

extern void test_utils(void);
extern void test_grade(void);
extern void test_data(void);

int main(void) {
    printf("--- BAT DAU CHAY UNIT TESTS ---\n\n");

    printf("1. Kiem thu module Utils:\n");
    test_utils();
    
    printf("\n2. Kiem thu module Grade:\n");
    test_grade();

    printf("\n3. Kiem thu module Data:\n");
    test_data();

    printf("\n--- KET QUA KIEM THU ---\n");
    printf("Tong so Test: %d\n", tests_run);
    printf("Pass: %d\n", tests_passed);
    printf("Fail: %d\n", tests_run - tests_passed);

    if (tests_run == tests_passed) {
        printf("\n=> TRANG THAI: Tat ca bai kiem thu deu vuot qua!\n");
        return 0;
    } else {
        printf("\n=> TRANG THAI: Co %d bai kiem thu that bai!\n", tests_run - tests_passed);
        return 1;
    }
}
