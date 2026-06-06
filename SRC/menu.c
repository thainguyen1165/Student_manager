#include "menu.h"

#include "display.h"
#include "file_io.h"
#include "operations.h"
#include "utils.h"

#include <stdio.h>

void print_menu(void) {
    const int width = 70;
    clear_screen_simple();
    printf("+------------------------------------------------------------------------+\n");
    print_box_line("                     QUAN LY SINH VIEN VA DIEM SO", width);
    print_box_line("", width);
    print_box_line(">  1. Them lop hoc phan", width);
    print_box_line("   2. Them mon hoc", width);
    print_box_line("   3. Them sinh vien", width);
    print_box_line("   4. Nhap / cap nhat diem", width);
    print_box_line("   5. Hien thi danh sach sinh vien", width);
    print_box_line("      - Trong muc nay chon sap xep theo MSSV / ten / GPA", width);
    print_box_line("   6. Hien thi danh sach mon hoc", width);
    print_box_line("   7. Hien thi danh sach lop hoc phan", width);
    print_box_line("   8. Tim kiem sinh vien", width);
    print_box_line("   9. Bang diem cua mot sinh vien", width);
    print_box_line("  10. Bang diem cua lop hoc phan", width);
    print_box_line("  11. Thong ke GPA va xep loai toan bo sinh vien", width);
    print_box_line("   0. Thoat", width);
    printf("+------------------------------------------------------------------------+\n");
}

void run_program(StudentSystem* sys) {
    int choice;

    while (1) {
        print_menu();
        choice = read_int("Chon chuc nang: ");

        if (choice == 0) {
            write_data_file(sys, DATA_OUTPUT_FILE);
            printf("Da ghi du lieu cuoi cung vao %s va thoat chuong trinh.\n", DATA_OUTPUT_FILE);
            break;
        } else if (choice == 1) {
            menu_add_section(sys);
        } else if (choice == 2) {
            menu_add_course(sys);
        } else if (choice == 3) {
            menu_add_student(sys);
        } else if (choice == 4) {
            menu_add_or_update_grade(sys);
        } else if (choice == 5) {
            menu_list_students(sys);
        } else if (choice == 6) {
            menu_list_courses(sys);
        } else if (choice == 7) {
            menu_list_sections(sys);
        } else if (choice == 8) {
            menu_search_student(sys);
        } else if (choice == 9) {
            menu_student_transcript(sys);
        } else if (choice == 10) {
            menu_section_transcript(sys);
        } else if (choice == 11) {
            menu_statistics(sys);
        } else {
            printf("Lua chon khong hop le.\n");
        }

        if (choice >= 1 && choice <= 11) {
            pause_screen();
        }
    }
}
