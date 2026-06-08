#include "test_framework.h"
#include "../../SRC/data.h"
#include <string.h>

void test_find_student() {
    StudentSystem sys;
    reset_system(&sys);
    
    strcpy(sys.students[0].student_id, "SV001");
    sys.student_count = 1;
    
    ASSERT("find_student_index: Tim thay hoc sinh", find_student_index(&sys, "SV001") == 0);
    ASSERT("find_student_index: Khong tim thay", find_student_index(&sys, "SV002") == -1);
}

void test_data(void) {
    test_find_student();
}
