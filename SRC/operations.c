#include "operations.h"

#include "data.h"
#include "grade.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

void menu_add_course(StudentSystem* sys) {
    char id[ID_LEN], name[NAME_LEN];
    int credits;

    if (sys->course_count >= MAX_COURSES) {
        printf("Danh sach mon hoc da day.\n");
        return;
    }

    read_line("Ma mon: ", id, sizeof(id));
    if (strlen(id) == 0) {
        printf("Ma mon khong duoc rong.\n");
        return;
    }
    if (find_course_index(sys, id) >= 0) {
        printf("Ma mon da ton tai.\n");
        return;
    }

    read_line("Ten mon: ", name, sizeof(name));
    credits = read_int("So tin chi: ");
    if (credits <= 0) {
        printf("So tin chi phai > 0.\n");
        return;
    }

    add_course_direct(sys, id, name, credits);
    printf("Da them mon hoc thanh cong.\n");
}

void menu_add_student(StudentSystem* sys) {
    char id[ID_LEN], name[NAME_LEN], class_name[ID_LEN], birth[DATE_LEN];

    if (sys->student_count >= MAX_STUDENTS) {
        printf("Danh sach sinh vien da day.\n");
        return;
    }

    read_line("MSSV: ", id, sizeof(id));
    if (strlen(id) == 0) {
        printf("MSSV khong duoc rong.\n");
        return;
    }
    if (find_student_index(sys, id) >= 0) {
        printf("MSSV da ton tai.\n");
        return;
    }

    read_line("Ho ten: ", name, sizeof(name));
    read_line("Lop hanh chinh: ", class_name, sizeof(class_name));
    read_line("Ngay sinh (yyyy-mm-dd): ", birth, sizeof(birth));

    add_student_direct(sys, id, name, class_name, birth);
    printf("Da them sinh vien thanh cong.\n");
}

void menu_add_section(StudentSystem* sys) {
    char section_id[ID_LEN], course_id[ID_LEN], semester[ID_LEN], lecturer[NAME_LEN];

    if (sys->section_count >= MAX_SECTIONS) {
        printf("Danh sach lop hoc phan da day.\n");
        return;
    }

    read_line("Ma lop hoc phan: ", section_id, sizeof(section_id));
    if (strlen(section_id) == 0) {
        printf("Ma lop hoc phan khong duoc rong.\n");
        return;
    }
    if (find_section_index(sys, section_id) >= 0) {
        printf("Ma lop hoc phan da ton tai.\n");
        return;
    }

    read_line("Ma mon: ", course_id, sizeof(course_id));
    if (find_course_index(sys, course_id) < 0) {
        printf("Khong tim thay ma mon. Hay them mon hoc truoc.\n");
        return;
    }

    read_line("Hoc ky: ", semester, sizeof(semester));
    read_line("Giang vien: ", lecturer, sizeof(lecturer));

    add_section_direct(sys, section_id, course_id, semester, lecturer);
    printf("Da them lop hoc phan thanh cong.\n");
}

void menu_add_or_update_grade(StudentSystem* sys) {
    char student_id[ID_LEN], course_id[ID_LEN], section_id[ID_LEN];
    int grade_index, section_index;
    Grade* g;

    read_line("Nhap MSSV: ", student_id, sizeof(student_id));
    if (find_student_index(sys, student_id) < 0) {
        printf("Khong tim thay sinh vien.\n");
        return;
    }

    read_line("Nhap ma mon: ", course_id, sizeof(course_id));
    if (find_course_index(sys, course_id) < 0) {
        printf("Khong tim thay mon hoc.\n");
        return;
    }

    read_line("Nhap ma lop hoc phan: ", section_id, sizeof(section_id));
    section_index = find_section_index(sys, section_id);
    if (section_index < 0) {
        printf("Khong tim thay lop hoc phan.\n");
        return;
    }
    if (!string_equals_ignore_case(sys->sections[section_index].course_id, course_id)) {
        printf("Lop hoc phan nay khong thuoc ma mon vua nhap.\n");
        return;
    }

    grade_index = find_grade_index(sys, student_id, course_id, section_id);
    if (grade_index >= 0) {
        printf("Da co diem. He thong se cap nhat diem cu.\n");
        g = &sys->grades[grade_index];
    } else {
        if (sys->grade_count >= MAX_GRADES) {
            printf("Danh sach diem da day.\n");
            return;
        }
        g = &sys->grades[sys->grade_count];
        safe_copy(g->student_id, sizeof(g->student_id), student_id);
        safe_copy(g->course_id, sizeof(g->course_id), course_id);
        safe_copy(g->section_id, sizeof(g->section_id), section_id);
        sys->grade_count++;
    }

    g->process_score = read_double_range("Diem qua trinh (0-10): ", 0.0, 10.0);
    g->midterm_score = read_double_range("Diem giua ky (0-10): ", 0.0, 10.0);
    g->final_score = read_double_range("Diem cuoi ky (0-10): ", 0.0, 10.0);
    calculate_grade(g);

    printf("Da luu diem. Tong ket he 10 = %.2f | He 4 = %.2f | Chu = %s\n",
           g->total10, g->total4, g->letter);
}
