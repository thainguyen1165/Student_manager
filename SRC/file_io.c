#include "file_io.h"

#include "data.h"
#include "utils.h"

#include <stdio.h>

void write_data_file(StudentSystem* sys, const char* filename) {
    FILE* f;
    int i;

    f = fopen(filename, "w");
    if (f == NULL) {
        printf("Khong the ghi file %s.\n", filename);
        return;
    }

    fprintf(f, "# FILE DU LIEU CHUONG TRINH QUAN LY SINH VIEN\n");
    fprintf(f, "# Chuong trinh tu doc input.txt khi mo va tu ghi output.txt khi thoat.\n");
    fprintf(f, "# Co the doi ten output.txt thanh input.txt de dung lai lan sau.\n");
    fprintf(f, "# Khong dung dau | trong ten mon, ho ten, giang vien.\n\n");

    fprintf(f, "[COURSES]\n");
    fprintf(f, "# MaMon | TenMon | SoTinChi\n");
    for (i = 0; i < sys->course_count; i++) {
        fprintf(f, "%s | %s | %d\n",
                sys->courses[i].course_id,
                sys->courses[i].course_name,
                sys->courses[i].credits);
    }

    fprintf(f, "\n[SECTIONS]\n");
    fprintf(f, "# MaLopHocPhan | MaMon | HocKy | GiangVien\n");
    for (i = 0; i < sys->section_count; i++) {
        fprintf(f, "%s | %s | %s | %s\n",
                sys->sections[i].section_id,
                sys->sections[i].course_id,
                sys->sections[i].semester,
                sys->sections[i].lecturer);
    }

    fprintf(f, "\n[STUDENTS]\n");
    fprintf(f, "# MSSV | HoTen | LopHanhChinh | NgaySinh\n");
    for (i = 0; i < sys->student_count; i++) {
        fprintf(f, "%s | %s | %s | %s\n",
                sys->students[i].student_id,
                sys->students[i].full_name,
                sys->students[i].class_name,
                sys->students[i].birth_date);
    }

    fprintf(f, "\n[GRADES]\n");
    fprintf(f, "# MSSV | MaMon | MaLopHocPhan | DiemQuaTrinh | DiemGiuaKy | DiemCuoiKy\n");
    for (i = 0; i < sys->grade_count; i++) {
        fprintf(f, "%s | %s | %s | %.2f | %.2f | %.2f\n",
                sys->grades[i].student_id,
                sys->grades[i].course_id,
                sys->grades[i].section_id,
                sys->grades[i].process_score,
                sys->grades[i].midterm_score,
                sys->grades[i].final_score);
    }

    fclose(f);
}

int load_input_file(StudentSystem* sys, const char* filename) {
    FILE* f;
    char line[INPUT_LEN * 2];
    char work[INPUT_LEN * 2];
    char* fields[8];
    int section = 0; /* 1 course, 2 section, 3 student, 4 grade */
    int count;
    int line_no = 0;
    int error_count = 0;
    int credits;
    double process, midterm, final_exam;

    f = fopen(filename, "r");
    if (f == NULL) return 0;

    reset_system(sys);

    while (fgets(line, sizeof(line), f) != NULL) {
        line_no++;
        trim_newline(line);
        trim_spaces(line);

        if (line[0] == '\0') continue;
        if (line[0] == '#' || line[0] == ';') continue;

        if (string_equals_ignore_case(line, "[COURSES]")) {
            section = 1;
            continue;
        }
        if (string_equals_ignore_case(line, "[SECTIONS]")) {
            section = 2;
            continue;
        }
        if (string_equals_ignore_case(line, "[STUDENTS]")) {
            section = 3;
            continue;
        }
        if (string_equals_ignore_case(line, "[GRADES]")) {
            section = 4;
            continue;
        }

        safe_copy(work, sizeof(work), line);
        count = split_fields(work, fields, 8);

        if (section == 1) {
            if (count != 3 || sscanf(fields[2], "%d", &credits) != 1 || credits <= 0) {
                printf("Loi dong %d trong [COURSES]. Dinh dang: MaMon | TenMon | SoTinChi\n", line_no);
                error_count++;
                continue;
            }
            if (find_course_index(sys, fields[0]) >= 0) {
                printf("Bo qua dong %d: Ma mon %s bi trung.\n", line_no, fields[0]);
                error_count++;
                continue;
            }
            add_course_direct(sys, fields[0], fields[1], credits);
        } else if (section == 2) {
            if (count != 4) {
                printf("Loi dong %d trong [SECTIONS]. Dinh dang: MaLHP | MaMon | HocKy | GiangVien\n", line_no);
                error_count++;
                continue;
            }
            if (find_section_index(sys, fields[0]) >= 0) {
                printf("Bo qua dong %d: Ma lop hoc phan %s bi trung.\n", line_no, fields[0]);
                error_count++;
                continue;
            }
            if (find_course_index(sys, fields[1]) < 0) {
                printf("Bo qua dong %d: Ma mon %s chua ton tai. Hay dat [COURSES] truoc [SECTIONS].\n", line_no, fields[1]);
                error_count++;
                continue;
            }
            add_section_direct(sys, fields[0], fields[1], fields[2], fields[3]);
        } else if (section == 3) {
            if (count != 4) {
                printf("Loi dong %d trong [STUDENTS]. Dinh dang: MSSV | HoTen | Lop | NgaySinh\n", line_no);
                error_count++;
                continue;
            }
            if (find_student_index(sys, fields[0]) >= 0) {
                printf("Bo qua dong %d: MSSV %s bi trung.\n", line_no, fields[0]);
                error_count++;
                continue;
            }
            add_student_direct(sys, fields[0], fields[1], fields[2], fields[3]);
        } else if (section == 4) {
            if (count != 6 ||
                sscanf(fields[3], "%lf", &process) != 1 ||
                sscanf(fields[4], "%lf", &midterm) != 1 ||
                sscanf(fields[5], "%lf", &final_exam) != 1 ||
                process < 0.0 || process > 10.0 ||
                midterm < 0.0 || midterm > 10.0 ||
                final_exam < 0.0 || final_exam > 10.0) {
                printf("Loi dong %d trong [GRADES]. Dinh dang: MSSV | MaMon | MaLHP | QT | GK | CK\n", line_no);
                error_count++;
                continue;
            }
            if (find_student_index(sys, fields[0]) < 0) {
                printf("Bo qua dong %d: MSSV %s chua ton tai.\n", line_no, fields[0]);
                error_count++;
                continue;
            }
            if (find_course_index(sys, fields[1]) < 0) {
                printf("Bo qua dong %d: Ma mon %s chua ton tai.\n", line_no, fields[1]);
                error_count++;
                continue;
            }
            if (find_section_index(sys, fields[2]) < 0) {
                printf("Bo qua dong %d: Ma LHP %s chua ton tai.\n", line_no, fields[2]);
                error_count++;
                continue;
            }
            if (find_grade_index(sys, fields[0], fields[1], fields[2]) >= 0) {
                printf("Bo qua dong %d: Diem cua %s - %s - %s bi trung.\n", line_no, fields[0], fields[1], fields[2]);
                error_count++;
                continue;
            }
            add_grade_direct(sys, fields[0], fields[1], fields[2], process, midterm, final_exam);
        } else {
            printf("Loi dong %d: Dong du lieu nam ngoai cac muc [COURSES], [SECTIONS], [STUDENTS], [GRADES].\n", line_no);
            error_count++;
        }
    }

    fclose(f);

    if (error_count > 0) {
        printf("Da doc file %s nhung co %d dong bi loi/bo qua.\n", filename, error_count);
    } else {
        printf("Da doc file %s thanh cong.\n", filename);
    }

    printf("Du lieu hien co: %d sinh vien, %d mon hoc, %d lop hoc phan, %d bang diem.\n",
           sys->student_count, sys->course_count, sys->section_count, sys->grade_count);
    return 1;
}
