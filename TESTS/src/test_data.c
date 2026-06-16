#include "test_framework.h"
#include "../../SRC/data.h"
#include <string.h>
#include <stdio.h>

void test_find_student() {
    StudentSystem sys;
    reset_system(&sys);
    
    add_student_direct(&sys, "SV001", "Nguyen Van A", "KTLT_01", "01/01/2000");
    add_student_direct(&sys, "SV002", "Tran Thi B", "KTLT_01", "02/02/2000");
    
    // Hop trang & Hop den: Kiem tra tim kiem chinh xac
    ASSERT("find_student_index: Tim thay sinh vien chinh xac", find_student_index(&sys, "SV001") == 0);
    ASSERT("find_student_index: Tim thay sinh vien khac", find_student_index(&sys, "SV002") == 1);
    ASSERT("find_student_index: Tim thay sinh vien khong phan biet hoa thuong", find_student_index(&sys, "sv001") == 0);
    
    // Tinh huong ngoai le: Ma khong ton tai hoac ma rong
    ASSERT("find_student_index: Khong tim thay voi ma sai", find_student_index(&sys, "SV003") == -1);
    ASSERT("find_student_index: Khong tim thay voi ma trong", find_student_index(&sys, "") == -1);
}

void test_add_course() {
    StudentSystem sys;
    reset_system(&sys);
    
    // Kiem tra them mon hoc
    add_course_direct(&sys, "MI3310", "Ky thuat lap trinh", 3);
    ASSERT("add_course: Them mon hoc thanh cong (so luong = 1)", sys.course_count == 1);
    ASSERT("add_course: Thong tin ma mon hoc chinh xac", strcmp(sys.courses[0].course_id, "MI3310") == 0);
    ASSERT("add_course: Thong tin ten mon hoc chinh xac", strcmp(sys.courses[0].course_name, "Ky thuat lap trinh") == 0);
    ASSERT("add_course: Thong tin tin chi chinh xac", sys.courses[0].credits == 3);
}

void test_find_course() {
    StudentSystem sys;
    reset_system(&sys);
    
    add_course_direct(&sys, "MI3310", "Ky thuat lap trinh", 3);
    
    ASSERT("find_course_index: Tim thay mon hoc chinh xac", find_course_index(&sys, "MI3310") == 0);
    ASSERT("find_course_index: Tim thay voi ma sai quy tac hoa thuong", find_course_index(&sys, "mi3310") == 0);
    ASSERT("find_course_index: Khong tim thay voi ma mon hoc sai", find_course_index(&sys, "MI1111") == -1);
    ASSERT("find_course_index: Khong tim thay voi ma rong", find_course_index(&sys, "") == -1);
}

void test_add_section_and_find() {
    StudentSystem sys;
    reset_system(&sys);
    
    add_section_direct(&sys, "150000", "MI3310", "20231", "Giang vien A");
    ASSERT("add_section: Them lop mo thanh cong", sys.section_count == 1);
    ASSERT("find_section_index: Tim thay lop mo", find_section_index(&sys, "150000") == 0);
    ASSERT("find_section_index: Khong tim thay lop mo sai", find_section_index(&sys, "150001") == -1);
}

void test_add_grade_and_find() {
    StudentSystem sys;
    reset_system(&sys);

    // Kiem tra viec ghi nhan diem
    add_grade_direct(&sys, "SV001", "MI3310", "150000", 8.0, 7.5, 9.0);
    ASSERT("add_grade: Them ban ghi diem thanh cong", sys.grade_count == 1);
    ASSERT("add_grade: Kiem tra ID sinh vien trong ban ghi diem", strcmp(sys.grades[0].student_id, "SV001") == 0);
    
    // Kiem tra tim kiem diem
    ASSERT("find_grade_index: Tim thay ban ghi ton tai", find_grade_index(&sys, "SV001", "MI3310", "150000") == 0);
    ASSERT("find_grade_index: Khong tim thay do sai SV", find_grade_index(&sys, "SV002", "MI3310", "150000") == -1);
    ASSERT("find_grade_index: Khong tim thay do sai mon hoc", find_grade_index(&sys, "SV001", "MI3311", "150000") == -1);
    ASSERT("find_grade_index: Khong tim thay do sai lop mo", find_grade_index(&sys, "SV001", "MI3310", "150001") == -1);
}

void test_limits() {
    StudentSystem sys;
    reset_system(&sys);
    int i;
    char id[ID_LEN];

    for (i = 0; i < MAX_STUDENTS; i++) {
        sprintf(id, "SV%04d", i);
        add_student_direct(&sys, id, "Test", "Test", "01/01/2000");
    }
    ASSERT("test_limits: So luong dat toi da (MAX_STUDENTS)", sys.student_count == MAX_STUDENTS);
    
    add_student_direct(&sys, "OVERFLOW", "Test", "Test", "01/01/2000");
    ASSERT("test_limits: Khong vuot qua MAX_STUDENTS", sys.student_count == MAX_STUDENTS);

    for (i = 0; i < MAX_COURSES + 5; i++) {
        sprintf(id, "MH%04d", i);
        add_course_direct(&sys, id, "Mon Test", 3);
    }
    ASSERT("test_limits: Khong vuot qua MAX_COURSES", sys.course_count == MAX_COURSES);
}

void test_data(void) {
    test_find_student();
    test_add_course();
    test_find_course();
    test_add_section_and_find();
    test_add_grade_and_find();
    test_limits();
}
