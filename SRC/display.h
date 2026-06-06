#ifndef DISPLAY_H
#define DISPLAY_H

#include "common.h"

void display_student_short(StudentSystem* sys, Student* s);
void menu_list_students(StudentSystem* sys);
void menu_list_courses(StudentSystem* sys);
void menu_list_sections(StudentSystem* sys);
void menu_search_student(StudentSystem* sys);
void menu_student_transcript(StudentSystem* sys);
void menu_section_transcript(StudentSystem* sys);
void menu_statistics(StudentSystem* sys);

#endif
