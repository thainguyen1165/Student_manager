#include "test_framework.h"
#include "../../SRC/grade.h"
#include <string.h>

void test_convert_10_to_4() {
    ASSERT("convert_10_to_4: Diem A (>=8.5)", convert_10_to_4(8.5) == 4.0 && convert_10_to_4(10.0) == 4.0);
    ASSERT("convert_10_to_4: Diem B+ (8.0 -> 8.4)", convert_10_to_4(8.0) == 3.5 && convert_10_to_4(8.4) == 3.5);
    ASSERT("convert_10_to_4: Diem B (7.0 -> 7.9)", convert_10_to_4(7.0) == 3.0 && convert_10_to_4(7.9) == 3.0);
    ASSERT("convert_10_to_4: Diem C+ (6.5 -> 6.9)", convert_10_to_4(6.5) == 2.5 && convert_10_to_4(6.9) == 2.5);
    ASSERT("convert_10_to_4: Diem C (5.5 -> 6.4)", convert_10_to_4(5.5) == 2.0 && convert_10_to_4(6.4) == 2.0);
    ASSERT("convert_10_to_4: Diem D+ (5.0 -> 5.4)", convert_10_to_4(5.0) == 1.5 && convert_10_to_4(5.4) == 1.5);
    ASSERT("convert_10_to_4: Diem D (4.0 -> 4.9)", convert_10_to_4(4.0) == 1.0 && convert_10_to_4(4.9) == 1.0);
    ASSERT("convert_10_to_4: Diem F (< 4.0)", convert_10_to_4(3.9) == 0.0 && convert_10_to_4(0.0) == 0.0);
}

void test_get_letter_grade() {
    char letter[8];
    get_letter_grade(8.5, letter, sizeof(letter));
    ASSERT("get_letter_grade: 8.5 la A", strcmp(letter, "A") == 0);
    
    get_letter_grade(8.0, letter, sizeof(letter));
    ASSERT("get_letter_grade: 8.0 la B+", strcmp(letter, "B+") == 0);

    get_letter_grade(3.9, letter, sizeof(letter));
    ASSERT("get_letter_grade: 3.9 la F", strcmp(letter, "F") == 0);
}

void test_classify_by_gpa4() {
    ASSERT("classify_by_gpa4: Xuat sac (>= 3.6)", strcmp(classify_by_gpa4(3.6), "Xuat sac") == 0 && strcmp(classify_by_gpa4(4.0), "Xuat sac") == 0);
    ASSERT("classify_by_gpa4: Gioi (3.2 -> 3.59)", strcmp(classify_by_gpa4(3.2), "Gioi") == 0 && strcmp(classify_by_gpa4(3.59), "Gioi") == 0);
    ASSERT("classify_by_gpa4: Kha (2.5 -> 3.19)", strcmp(classify_by_gpa4(2.5), "Kha") == 0 && strcmp(classify_by_gpa4(3.1), "Kha") == 0);
    ASSERT("classify_by_gpa4: Trung binh (2.0 -> 2.49)", strcmp(classify_by_gpa4(2.0), "Trung binh") == 0 && strcmp(classify_by_gpa4(2.4), "Trung binh") == 0);
    ASSERT("classify_by_gpa4: Yeu (1.0 -> 1.99)", strcmp(classify_by_gpa4(1.0), "Yeu") == 0 && strcmp(classify_by_gpa4(1.9), "Yeu") == 0);
    ASSERT("classify_by_gpa4: Kem (< 1.0)", strcmp(classify_by_gpa4(0.9), "Kem") == 0 && strcmp(classify_by_gpa4(0.0), "Kem") == 0);
}

void test_calculate_grade() {
    Grade g;
    g.process_score = 8.0;
    g.midterm_score = 7.0;
    g.final_score = 9.0;
    calculate_grade(&g);
    
    ASSERT("calculate_grade: Tinh diem total10", g.total10 >= 8.29 && g.total10 <= 8.31);
    ASSERT("calculate_grade: Tinh diem total4", g.total4 == 3.5);
    ASSERT("calculate_grade: Tinh diem letter", strcmp(g.letter, "B+") == 0);
}

void test_grade(void) {
    test_convert_10_to_4();
    test_get_letter_grade();
    test_classify_by_gpa4();
    test_calculate_grade();
}
