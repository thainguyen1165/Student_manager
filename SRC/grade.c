#include "grade.h"

#include "data.h"
#include "utils.h"

#include <string.h>

double convert_10_to_4(double score10) {
    if (score10 >= 8.5) return 4.0;
    if (score10 >= 8.0) return 3.5;
    if (score10 >= 7.0) return 3.0;
    if (score10 >= 6.5) return 2.5;
    if (score10 >= 5.5) return 2.0;
    if (score10 >= 5.0) return 1.5;
    if (score10 >= 4.0) return 1.0;
    return 0.0;
}

void get_letter_grade(double score10, char* out, size_t out_size) {
    if (score10 >= 8.5) safe_copy(out, out_size, "A");
    else if (score10 >= 8.0) safe_copy(out, out_size, "B+");
    else if (score10 >= 7.0) safe_copy(out, out_size, "B");
    else if (score10 >= 6.5) safe_copy(out, out_size, "C+");
    else if (score10 >= 5.5) safe_copy(out, out_size, "C");
    else if (score10 >= 5.0) safe_copy(out, out_size, "D+");
    else if (score10 >= 4.0) safe_copy(out, out_size, "D");
    else safe_copy(out, out_size, "F");
}

const char* classify_by_gpa4(double gpa4) {
    if (gpa4 >= 3.60) return "Xuat sac";
    if (gpa4 >= 3.20) return "Gioi";
    if (gpa4 >= 2.50) return "Kha";
    if (gpa4 >= 2.00) return "Trung binh";
    if (gpa4 >= 1.00) return "Yeu";
    return "Kem";
}

int calculate_gpa(StudentSystem* sys, const char* student_id, double* gpa10, double* gpa4, int* total_credits) {
    int i, course_index, credits;
    double sum10 = 0.0, sum4 = 0.0;
    int credits_sum = 0;

    for (i = 0; i < sys->grade_count; i++) {
        if (string_equals_ignore_case(sys->grades[i].student_id, student_id)) {
            course_index = find_course_index(sys, sys->grades[i].course_id);
            if (course_index >= 0) {
                credits = sys->courses[course_index].credits;
                sum10 += sys->grades[i].total10 * credits;
                sum4 += sys->grades[i].total4 * credits;
                credits_sum += credits;
            }
        }
    }

    if (credits_sum == 0) {
        *gpa10 = 0.0;
        *gpa4 = 0.0;
        *total_credits = 0;
        return 0;
    }

    *gpa10 = sum10 / credits_sum;
    *gpa4 = sum4 / credits_sum;
    *total_credits = credits_sum;
    return 1;
}

void calculate_grade(Grade* g) {
    /* Cong thuc: qua trinh 10%, giua ky 30%, cuoi ky 60%. */
    g->total10 = g->process_score * 0.10 + g->midterm_score * 0.30 + g->final_score * 0.60;
    g->total4 = convert_10_to_4(g->total10);
    get_letter_grade(g->total10, g->letter, sizeof(g->letter));
}

double get_student_gpa4(StudentSystem* sys, const char* student_id) {
    double gpa10, gpa4;
    int credits;
    if (calculate_gpa(sys, student_id, &gpa10, &gpa4, &credits)) return gpa4;
    return -1.0;
}
