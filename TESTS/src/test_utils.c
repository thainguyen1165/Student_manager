#include "test_framework.h"
#include "../../SRC/utils.h"
#include <string.h>

void test_trim_spaces() {
    char str1[] = "  Hello   World  ";
    trim_spaces(str1);
    ASSERT("trim_spaces: loai bo khoang trang thua", strcmp(str1, "Hello   World") == 0);

    char str2[] = "Normal";
    trim_spaces(str2);
    ASSERT("trim_spaces: chuoi khong co khoang trang thua", strcmp(str2, "Normal") == 0);
}

void test_string_equals_ignore_case() {
    ASSERT("string_equals_ignore_case: bang nhau hoa thuong", string_equals_ignore_case("aBcD", "AbCd") == 1);
    ASSERT("string_equals_ignore_case: khong bang nhau", string_equals_ignore_case("abc", "abd") == 0);
}

void test_string_contains_ignore_case() {
    ASSERT("string_contains_ignore_case: chua tu khoa", string_contains_ignore_case("Nguyen Van An", "van") != 0);
    ASSERT("string_contains_ignore_case: khong chua tu khoa", string_contains_ignore_case("Nguyen Van An", "tran") == 0);
}

void test_utils(void) {
    test_trim_spaces();
    test_string_equals_ignore_case();
    test_string_contains_ignore_case();
}

