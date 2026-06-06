#include "common.h"
#include "data.h"
#include "file_io.h"
#include "menu.h"
#include "utils.h"

#include <stdio.h>

int main(void) {
    StudentSystem sys;

    reset_system(&sys);

    if (!load_input_file(&sys, DATA_INPUT_FILE)) {
        printf("Khong tim thay %s. Chuong trinh se bat dau voi du lieu rong.\n", DATA_INPUT_FILE);
        printf("Hay dat file %s cung thu muc voi file .exe de chuong trinh tu doc khi mo len.\n", DATA_INPUT_FILE);
    }

    pause_screen();
    run_program(&sys);

    return 0;
}
