#ifndef GRADE_H
#define GRADE_H

#include <stddef.h>
#include "common.h"

double convert_10_to_4(double score10);
void get_letter_grade(double score10, char* out, size_t out_size);
const char* classify_by_gpa4(double gpa4);
int calculate_gpa(StudentSystem* sys, const char* student_id, double* gpa10, double* gpa4, int* total_credits);
void calculate_grade(Grade* g);
double get_student_gpa4(StudentSystem* sys, const char* student_id);

#endif
