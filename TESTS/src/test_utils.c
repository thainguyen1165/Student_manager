#include "test_framework.h"
#include "../../SRC/utils.h"
#include <string.h>

void test_trim_spaces() {
    char str1[] = "  Hello   World  ";
    trim_spaces(str1);
    ASSERT("trim_spaces: Loai bo khoang trang hai dau", strcmp(str1, "Hello   World") == 0);

    char str2[] = "Normal";
    trim_spaces(str2);
    ASSERT("trim_spaces: Chuoi khong co khoang trang", strcmp(str2, "Normal") == 0);

    char str3[] = "   ";
    trim_spaces(str3);
    ASSERT("trim_spaces: Chuoi chi co khoang trang", strcmp(str3, "") == 0);

    char str4[] = "";
    trim_spaces(str4);
    ASSERT("trim_spaces: Chuoi rong", strcmp(str4, "") == 0);

    trim_spaces(NULL);
    ASSERT("trim_spaces: Xu ly an toan voi NULL", 1);
}

void test_trim_newline() {
    char str1[] = "abc\n";
    trim_newline(str1);
    ASSERT("trim_newline: Loai bo ky tu xuong dong", strcmp(str1, "abc") == 0);

    char str2[] = "abc";
    trim_newline(str2);
    ASSERT("trim_newline: Khong co ky tu xuong dong", strcmp(str2, "abc") == 0);

    trim_newline(NULL); // An toan voi NULL
    ASSERT("trim_newline: Xu ly an toan voi NULL", 1);
}

void test_string_equals_ignore_case() {
    ASSERT("string_equals_ignore_case: Bang nhau khong phan biet hoa thuong", string_equals_ignore_case("aBcD", "AbCd") == 1);
    ASSERT("string_equals_ignore_case: Bang nhau chuoi rong", string_equals_ignore_case("", "") == 1);
    ASSERT("string_equals_ignore_case: Khong bang nhau (khac do dai)", string_equals_ignore_case("abc", "abcd") == 0);
    ASSERT("string_equals_ignore_case: Khong bang nhau (khac ky tu)", string_equals_ignore_case("abc", "abd") == 0);
}

void test_string_contains_ignore_case() {
    ASSERT("string_contains_ignore_case: Chua tu khoa giua chuoi", string_contains_ignore_case("Nguyen Van An", "van") == 1);
    ASSERT("string_contains_ignore_case: Tu khoa la chuoi rong (tra ve 1)", string_contains_ignore_case("Nguyen Van An", "") == 1);
    ASSERT("string_contains_ignore_case: Chuoi text rong", string_contains_ignore_case("", "van") == 0);
    ASSERT("string_contains_ignore_case: Tu khoa dai hon chuoi text", string_contains_ignore_case("van", "Nguyen Van An") == 0);
    ASSERT("string_contains_ignore_case: Khong chua tu khoa", string_contains_ignore_case("Nguyen Van An", "tran") == 0);
}

void test_split_fields() {
    char line1[] = " SV01 | Nguyen Van A | KTLT ";
    char* fields[3];
    int count = split_fields(line1, fields, 3);
    ASSERT("split_fields: Cat duoc 3 phan tu", count == 3);
    ASSERT("split_fields: Phan tu 1 tu dong trim_spaces", strcmp(fields[0], "SV01") == 0);
    ASSERT("split_fields: Phan tu 2 tu dong trim_spaces", strcmp(fields[1], "Nguyen Van A") == 0);
    ASSERT("split_fields: Phan tu 3 tu dong trim_spaces", strcmp(fields[2], "KTLT") == 0);

    char line2[] = "Data1|Data2";
    count = split_fields(line2, fields, 5);
    ASSERT("split_fields: Gioi han cat phan tu it hon max", count == 2);
}

void test_utils(void) {
    test_trim_spaces();
    test_trim_newline();
    test_string_equals_ignore_case();
    test_string_contains_ignore_case();
    test_split_fields();
}
