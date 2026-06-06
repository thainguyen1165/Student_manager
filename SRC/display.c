#include "display.h"

#include "data.h"
#include "grade.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

static const char* get_last_name_part(const char* full_name) {
    const char* p = full_name;
    const char* last = full_name;

    while (*p != '\0') {
        if (isspace((unsigned char)*p) && *(p + 1) != '\0') {
            last = p + 1;
        }
        p++;
    }
    return last;
}

static int compare_ignore_case_ascii(const char* a, const char* b) {
    unsigned char ca, cb;
    while (*a && *b) {
        ca = (unsigned char)tolower((unsigned char)*a);
        cb = (unsigned char)tolower((unsigned char)*b);
        if (ca < cb) return -1;
        if (ca > cb) return 1;
        a++;
        b++;
    }
    if (*a == '\0' && *b == '\0') return 0;
    return *a == '\0' ? -1 : 1;
}

static int compare_students(StudentSystem* sys, Student* a, Student* b, int sort_type) {
    double gpa_a, gpa_b;
    int cmp;

    if (sort_type == 1) {
        return compare_ignore_case_ascii(a->student_id, b->student_id);
    }

    if (sort_type == 2) {
        /* Sap xep theo ten rieng truoc, neu trung ten thi so sanh ca ho ten. */
        cmp = compare_ignore_case_ascii(get_last_name_part(a->full_name), get_last_name_part(b->full_name));
        if (cmp != 0) return cmp;
        return compare_ignore_case_ascii(a->full_name, b->full_name);
    }

    if (sort_type == 3) {
        gpa_a = get_student_gpa4(sys, a->student_id);
        gpa_b = get_student_gpa4(sys, b->student_id);
        if (gpa_a > gpa_b) return -1;
        if (gpa_a < gpa_b) return 1;
        return compare_ignore_case_ascii(a->student_id, b->student_id);
    }

    return 0;
}

static void sort_student_indexes_for_display(StudentSystem* sys, int indexes[], int sort_type) {
    int i, j, tmp;
    for (i = 0; i < sys->student_count; i++) indexes[i] = i;

    for (i = 0; i < sys->student_count - 1; i++) {
        for (j = i + 1; j < sys->student_count; j++) {
            if (compare_students(sys, &sys->students[indexes[i]], &sys->students[indexes[j]], sort_type) > 0) {
                tmp = indexes[i];
                indexes[i] = indexes[j];
                indexes[j] = tmp;
            }
        }
    }
}

static const char* get_sort_type_name(int sort_type) {
    if (sort_type == 1) return "MSSV tang dan";
    if (sort_type == 2) return "ten A-Z";
    if (sort_type == 3) return "GPA he 4 giam dan";
    return "MSSV tang dan";
}

void display_student_short(StudentSystem* sys, Student* s) {
    double gpa10, gpa4;
    int credits;
    if (calculate_gpa(sys, s->student_id, &gpa10, &gpa4, &credits)) {
        printf("%-12s | %-25s | %-12s | %-12s | GPA10: %5.2f | GPA4: %4.2f | %s\n",
               s->student_id, s->full_name, s->class_name, s->birth_date,
               gpa10, gpa4, classify_by_gpa4(gpa4));
    } else {
        printf("%-12s | %-25s | %-12s | %-12s | Chua co diem\n",
               s->student_id, s->full_name, s->class_name, s->birth_date);
    }
}

void menu_list_students(StudentSystem* sys) {
    int indexes[MAX_STUDENTS];
    int i;
    int sort_type;

    if (sys->student_count == 0) {
        printf("\nChua co sinh vien nao.\n");
        return;
    }

    printf("\nHIEN THI DANH SACH SINH VIEN\n");
    printf("1. Sap xep theo MSSV tang dan\n");
    printf("2. Sap xep theo ten A-Z\n");
    printf("3. Sap xep theo GPA he 4 giam dan\n");
    sort_type = read_int("Chon kieu hien thi: ");
    if (sort_type < 1 || sort_type > 3) {
        printf("Lua chon khong hop le. Tu dong sap xep theo MSSV.\n");
        sort_type = 1;
    }

    sort_student_indexes_for_display(sys, indexes, sort_type);

    printf("\nDANH SACH SINH VIEN (%d) - SAP XEP THEO %s\n", sys->student_count, get_sort_type_name(sort_type));
    printf("--------------------------------------------------------------------------------------------\n");
    for (i = 0; i < sys->student_count; i++) {
        display_student_short(sys, &sys->students[indexes[i]]);
    }
}

void menu_list_courses(StudentSystem* sys) {
    int i;
    printf("\nDANH SACH MON HOC (%d)\n", sys->course_count);
    printf("---------------------------------------------------------------\n");
    printf("%-12s | %-40s | %s\n", "Ma mon", "Ten mon", "TC");
    printf("---------------------------------------------------------------\n");
    for (i = 0; i < sys->course_count; i++) {
        printf("%-12s | %-40s | %d\n", sys->courses[i].course_id, sys->courses[i].course_name, sys->courses[i].credits);
    }
}

void menu_list_sections(StudentSystem* sys) {
    int i, course_index;
    printf("\nDANH SACH LOP HOC PHAN (%d)\n", sys->section_count);
    printf("----------------------------------------------------------------------------------\n");
    printf("%-12s | %-10s | %-28s | %-10s | %-20s\n", "Ma LHP", "Ma mon", "Ten mon", "Hoc ky", "Giang vien");
    printf("----------------------------------------------------------------------------------\n");
    for (i = 0; i < sys->section_count; i++) {
        course_index = find_course_index(sys, sys->sections[i].course_id);
        printf("%-12s | %-10s | %-28s | %-10s | %-20s\n",
               sys->sections[i].section_id,
               sys->sections[i].course_id,
               course_index >= 0 ? sys->courses[course_index].course_name : "Unknown",
               sys->sections[i].semester,
               sys->sections[i].lecturer);
    }
}

void menu_search_student(StudentSystem* sys) {
    char keyword[NAME_LEN];
    int i, found = 0;
    read_line("Nhap MSSV hoac ho ten can tim: ", keyword, sizeof(keyword));
    printf("\nKET QUA TIM KIEM\n");
    printf("--------------------------------------------------------------------------------------------\n");
    for (i = 0; i < sys->student_count; i++) {
        if (string_contains_ignore_case(sys->students[i].student_id, keyword) ||
            string_contains_ignore_case(sys->students[i].full_name, keyword)) {
            display_student_short(sys, &sys->students[i]);
            found = 1;
        }
    }
    if (!found) printf("Khong tim thay sinh vien phu hop.\n");
}

static void print_grade_row(StudentSystem* sys, Grade* g) {
    int course_index = find_course_index(sys, g->course_id);
    int credits = course_index >= 0 ? sys->courses[course_index].credits : 0;
    printf("%-10s | %-30s | %-8s | %2d | %5.2f | %5.2f | %5.2f | %6.2f | %4.2f | %-3s\n",
           g->course_id,
           course_index >= 0 ? sys->courses[course_index].course_name : "Unknown",
           g->section_id,
           credits,
           g->process_score,
           g->midterm_score,
           g->final_score,
           g->total10,
           g->total4,
           g->letter);
}

void menu_student_transcript(StudentSystem* sys) {
    char student_id[ID_LEN];
    int student_index;
    int i, found = 0;
    double gpa10, gpa4;
    int credits;

    read_line("Nhap MSSV: ", student_id, sizeof(student_id));
    student_index = find_student_index(sys, student_id);
    if (student_index < 0) {
        printf("Khong tim thay sinh vien.\n");
        return;
    }

    printf("\nBANG DIEM SINH VIEN\n");
    printf("MSSV: %s\n", sys->students[student_index].student_id);
    printf("Ho ten: %s\n", sys->students[student_index].full_name);
    printf("Lop: %s\n", sys->students[student_index].class_name);
    printf("Ngay sinh: %s\n", sys->students[student_index].birth_date);
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("%-10s | %-30s | %-8s | %2s | %5s | %5s | %5s | %6s | %4s | %-3s\n",
           "Ma mon", "Ten mon", "Ma LHP", "TC", "QT", "GK", "CK", "Tong", "H4", "Chu");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < sys->grade_count; i++) {
        if (string_equals_ignore_case(sys->grades[i].student_id, student_id)) {
            print_grade_row(sys, &sys->grades[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("Sinh vien nay chua co diem.\n");
        return;
    }

    if (calculate_gpa(sys, student_id, &gpa10, &gpa4, &credits)) {
        printf("-------------------------------------------------------------------------------------------------------------\n");
        printf("Tong tin chi: %d | GPA he 10: %.2f | GPA he 4: %.2f | Xep loai: %s\n",
               credits, gpa10, gpa4, classify_by_gpa4(gpa4));
    }
}

void menu_section_transcript(StudentSystem* sys) {
    char section_id[ID_LEN];
    int section_index;
    int i, student_index, found = 0;

    read_line("Nhap ma lop hoc phan: ", section_id, sizeof(section_id));
    section_index = find_section_index(sys, section_id);
    if (section_index < 0) {
        printf("Khong tim thay lop hoc phan.\n");
        return;
    }

    printf("\nBANG DIEM LOP HOC PHAN\n");
    printf("Ma LHP: %s | Ma mon: %s | Hoc ky: %s | Giang vien: %s\n",
           sys->sections[section_index].section_id,
           sys->sections[section_index].course_id,
           sys->sections[section_index].semester,
           sys->sections[section_index].lecturer);
    printf("---------------------------------------------------------------------------------------------\n");
    printf("%-12s | %-25s | %5s | %5s | %5s | %6s | %4s | %-3s\n",
           "MSSV", "Ho ten", "QT", "GK", "CK", "Tong", "H4", "Chu");
    printf("---------------------------------------------------------------------------------------------\n");

    for (i = 0; i < sys->grade_count; i++) {
        if (string_equals_ignore_case(sys->grades[i].section_id, section_id)) {
            student_index = find_student_index(sys, sys->grades[i].student_id);
            printf("%-12s | %-25s | %5.2f | %5.2f | %5.2f | %6.2f | %4.2f | %-3s\n",
                   sys->grades[i].student_id,
                   student_index >= 0 ? sys->students[student_index].full_name : "Unknown",
                   sys->grades[i].process_score,
                   sys->grades[i].midterm_score,
                   sys->grades[i].final_score,
                   sys->grades[i].total10,
                   sys->grades[i].total4,
                   sys->grades[i].letter);
            found = 1;
        }
    }

    if (!found) printf("Lop hoc phan nay chua co diem.\n");
}

void menu_statistics(StudentSystem* sys) {
    int i;
    double gpa10, gpa4;
    int credits;
    int count_xs = 0, count_gioi = 0, count_kha = 0, count_tb = 0, count_yeu = 0, count_kem = 0;
    const char* type;

    printf("\nTHONG KE GPA VA XEP LOAI\n");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("%-12s | %-25s | %8s | %8s | %5s | %-12s\n", "MSSV", "Ho ten", "GPA10", "GPA4", "TC", "Xep loai");
    printf("--------------------------------------------------------------------------------------------\n");

    for (i = 0; i < sys->student_count; i++) {
        if (calculate_gpa(sys, sys->students[i].student_id, &gpa10, &gpa4, &credits)) {
            type = classify_by_gpa4(gpa4);
            printf("%-12s | %-25s | %8.2f | %8.2f | %5d | %-12s\n",
                   sys->students[i].student_id, sys->students[i].full_name, gpa10, gpa4, credits, type);
            if (strcmp(type, "Xuat sac") == 0) count_xs++;
            else if (strcmp(type, "Gioi") == 0) count_gioi++;
            else if (strcmp(type, "Kha") == 0) count_kha++;
            else if (strcmp(type, "Trung binh") == 0) count_tb++;
            else if (strcmp(type, "Yeu") == 0) count_yeu++;
            else count_kem++;
        } else {
            printf("%-12s | %-25s | %8s | %8s | %5s | %-12s\n",
                   sys->students[i].student_id, sys->students[i].full_name, "-", "-", "-", "Chua co diem");
        }
    }

    printf("--------------------------------------------------------------------------------------------\n");
    printf("Tong sinh vien: %d\n", sys->student_count);
    printf("Xuat sac: %d | Gioi: %d | Kha: %d | Trung binh: %d | Yeu: %d | Kem: %d\n",
           count_xs, count_gioi, count_kha, count_tb, count_yeu, count_kem);
}
