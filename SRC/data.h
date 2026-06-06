#ifndef DATA_H
#define DATA_H

#include "common.h"

void reset_system(StudentSystem* sys);
int find_student_index(StudentSystem* sys, const char* student_id);
int find_course_index(StudentSystem* sys, const char* course_id);
int find_section_index(StudentSystem* sys, const char* section_id);
int find_grade_index(StudentSystem* sys, const char* student_id, const char* course_id, const char* section_id);

void add_course_direct(StudentSystem* sys, const char* id, const char* name, int credits);
void add_student_direct(StudentSystem* sys, const char* id, const char* name, const char* class_name, const char* birth);
void add_section_direct(StudentSystem* sys, const char* section_id, const char* course_id, const char* semester, const char* lecturer);
void add_grade_direct(StudentSystem* sys, const char* student_id, const char* course_id, const char* section_id,
                      double process, double midterm, double final_exam);

#endif
