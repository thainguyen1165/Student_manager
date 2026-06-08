#include "test_framework.h"
#include "../../SRC/grade.h"
#include <string.h>

void test_convert_10_to_4() {
    ASSERT("convert_10_to_4: Diem A (8.5)", convert_10_to_4(8.5) == 4.0);
    ASSERT("convert_10_to_4: Diem B (7.0)", convert_10_to_4(7.0) == 3.0);
    ASSERT("convert_10_to_4: Diem F (3.0)", convert_10_to_4(3.0) == 0.0);
}

void test_get_letter_grade() {
    char letter[8];
    get_letter_grade(8.5, letter, sizeof(letter));
    ASSERT("get_letter_grade: 8.5 la A", strcmp(letter, "A") == 0);
    
    get_letter_grade(3.9, letter, sizeof(letter));
    ASSERT("get_letter_grade: 3.9 la F", strcmp(letter, "F") == 0);
}

void test_classify_by_gpa4() {
    ASSERT("classify_by_gpa4: Xuat sac (3.8)", strcmp(classify_by_gpa4(3.8), "Xuat sac") == 0);
}

void test_grade(void) {
    test_convert_10_to_4();
    test_get_letter_grade();
    test_classify_by_gpa4();
}
