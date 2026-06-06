#include "data.h"

#include "utils.h"
#include "grade.h"

void reset_system(StudentSystem* sys) {
    sys->student_count = 0;
    sys->course_count = 0;
    sys->section_count = 0;
    sys->grade_count = 0;
}

int find_student_index(StudentSystem* sys, const char* student_id) {
    int i;
    for (i = 0; i < sys->student_count; i++) {
        if (string_equals_ignore_case(sys->students[i].student_id, student_id)) return i;
    }
    return -1;
}

int find_course_index(StudentSystem* sys, const char* course_id) {
    int i;
    for (i = 0; i < sys->course_count; i++) {
        if (string_equals_ignore_case(sys->courses[i].course_id, course_id)) return i;
    }
    return -1;
}

int find_section_index(StudentSystem* sys, const char* section_id) {
    int i;
    for (i = 0; i < sys->section_count; i++) {
        if (string_equals_ignore_case(sys->sections[i].section_id, section_id)) return i;
    }
    return -1;
}

int find_grade_index(StudentSystem* sys, const char* student_id, const char* course_id, const char* section_id) {
    int i;
    for (i = 0; i < sys->grade_count; i++) {
        if (string_equals_ignore_case(sys->grades[i].student_id, student_id) &&
            string_equals_ignore_case(sys->grades[i].course_id, course_id) &&
            string_equals_ignore_case(sys->grades[i].section_id, section_id)) return i;
    }
    return -1;
}

void add_course_direct(StudentSystem* sys, const char* id, const char* name, int credits) {
    if (sys->course_count >= MAX_COURSES) return;
    safe_copy(sys->courses[sys->course_count].course_id, sizeof(sys->courses[sys->course_count].course_id), id);
    safe_copy(sys->courses[sys->course_count].course_name, sizeof(sys->courses[sys->course_count].course_name), name);
    sys->courses[sys->course_count].credits = credits;
    sys->course_count++;
}

void add_student_direct(StudentSystem* sys, const char* id, const char* name, const char* class_name, const char* birth) {
    if (sys->student_count >= MAX_STUDENTS) return;
    safe_copy(sys->students[sys->student_count].student_id, sizeof(sys->students[sys->student_count].student_id), id);
    safe_copy(sys->students[sys->student_count].full_name, sizeof(sys->students[sys->student_count].full_name), name);
    safe_copy(sys->students[sys->student_count].class_name, sizeof(sys->students[sys->student_count].class_name), class_name);
    safe_copy(sys->students[sys->student_count].birth_date, sizeof(sys->students[sys->student_count].birth_date), birth);
    sys->student_count++;
}

void add_section_direct(StudentSystem* sys, const char* section_id, const char* course_id, const char* semester, const char* lecturer) {
    if (sys->section_count >= MAX_SECTIONS) return;
    safe_copy(sys->sections[sys->section_count].section_id, sizeof(sys->sections[sys->section_count].section_id), section_id);
    safe_copy(sys->sections[sys->section_count].course_id, sizeof(sys->sections[sys->section_count].course_id), course_id);
    safe_copy(sys->sections[sys->section_count].semester, sizeof(sys->sections[sys->section_count].semester), semester);
    safe_copy(sys->sections[sys->section_count].lecturer, sizeof(sys->sections[sys->section_count].lecturer), lecturer);
    sys->section_count++;
}

void add_grade_direct(StudentSystem* sys, const char* student_id, const char* course_id, const char* section_id,
                      double process, double midterm, double final_exam) {
    Grade* g;
    if (sys->grade_count >= MAX_GRADES) return;
    g = &sys->grades[sys->grade_count];
    safe_copy(g->student_id, sizeof(g->student_id), student_id);
    safe_copy(g->course_id, sizeof(g->course_id), course_id);
    safe_copy(g->section_id, sizeof(g->section_id), section_id);
    g->process_score = process;
    g->midterm_score = midterm;
    g->final_score = final_exam;
    calculate_grade(g);
    sys->grade_count++;
}
