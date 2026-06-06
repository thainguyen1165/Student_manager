#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void clear_screen_simple(void) {
#ifdef _WIN32
    system("cls");
#else
    int i;
    for (i = 0; i < 25; i++) {
        printf("\n");
    }
#endif
}

void pause_screen(void) {
    char tmp[INPUT_LEN];
    printf("\nNhan Enter de tiep tuc...");
    fgets(tmp, sizeof(tmp), stdin);
}

void trim_newline(char* s) {
    size_t len;
    if (s == NULL) return;
    len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') s[len - 1] = '\0';
}

void trim_spaces(char* s) {
    char* start;
    int len;

    if (s == NULL) return;
    start = s;
    while (*start && isspace((unsigned char)*start)) start++;
    if (start != s) memmove(s, start, strlen(start) + 1);

    len = (int)strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[len - 1] = '\0';
        len--;
    }
}

void safe_copy(char* dest, size_t dest_size, const char* src) {
    if (dest_size == 0) return;
    if (src == NULL) src = "";
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
}

void read_line(const char* prompt, char* buffer, int size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    trim_newline(buffer);
}

int read_int(const char* prompt) {
    char buffer[INPUT_LEN];
    int value;
    while (1) {
        read_line(prompt, buffer, sizeof(buffer));
        if (sscanf(buffer, "%d", &value) == 1) return value;
        printf("Nhap sai. Vui long nhap so nguyen.\n");
    }
}

double read_double_range(const char* prompt, double min, double max) {
    char buffer[INPUT_LEN];
    double value;
    while (1) {
        read_line(prompt, buffer, sizeof(buffer));
        if (sscanf(buffer, "%lf", &value) == 1 && value >= min && value <= max) return value;
        printf("Nhap sai. Vui long nhap diem trong khoang %.1f - %.1f.\n", min, max);
    }
}

int string_equals_ignore_case(const char* a, const char* b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

int string_contains_ignore_case(const char* text, const char* keyword) {
    int i, j;
    int n = (int)strlen(text);
    int m = (int)strlen(keyword);
    if (m == 0) return 1;
    if (m > n) return 0;
    for (i = 0; i <= n - m; i++) {
        for (j = 0; j < m; j++) {
            if (tolower((unsigned char)text[i + j]) != tolower((unsigned char)keyword[j])) break;
        }
        if (j == m) return 1;
    }
    return 0;
}

int split_fields(char* line, char* fields[], int max_fields) {
    int count = 0;
    char* token;

    token = strtok(line, "|");
    while (token != NULL && count < max_fields) {
        trim_spaces(token);
        fields[count] = token;
        count++;
        token = strtok(NULL, "|");
    }
    return count;
}

void print_box_line(const char* text, int width) {
    int len = (int)strlen(text);
    int i;
    printf("| ");
    if (len > width) {
        for (i = 0; i < width; i++) putchar(text[i]);
    } else {
        printf("%s", text);
        for (i = 0; i < width - len; i++) putchar(' ');
    }
    printf(" |\n");
}
