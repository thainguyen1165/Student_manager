#ifndef COMMON_H
#define COMMON_H

#define _CRT_SECURE_NO_WARNINGS

#define MAX_STUDENTS 1000
#define MAX_COURSES 300
#define MAX_SECTIONS 300
#define MAX_GRADES 5000

#define ID_LEN 24
#define NAME_LEN 80
#define DATE_LEN 20
#define INPUT_LEN 256

#define DATA_INPUT_FILE "input.txt"
#define DATA_OUTPUT_FILE "output.txt"

typedef struct {
    char student_id[ID_LEN];
    char full_name[NAME_LEN];
    char class_name[ID_LEN];
    char birth_date[DATE_LEN];
} Student;

typedef struct {
    char course_id[ID_LEN];
    char course_name[NAME_LEN];
    int credits;
} Course;

typedef struct {
    char section_id[ID_LEN];
    char course_id[ID_LEN];
    char semester[ID_LEN];
    char lecturer[NAME_LEN];
} ClassSection;

typedef struct {
    char student_id[ID_LEN];
    char course_id[ID_LEN];
    char section_id[ID_LEN];
    double process_score;
    double midterm_score;
    double final_score;
    double total10;
    double total4;
    char letter[8];
} Grade;

typedef struct {
    Student students[MAX_STUDENTS];
    Course courses[MAX_COURSES];
    ClassSection sections[MAX_SECTIONS];
    Grade grades[MAX_GRADES];
    int student_count;
    int course_count;
    int section_count;
    int grade_count;
} StudentSystem;

#endif
