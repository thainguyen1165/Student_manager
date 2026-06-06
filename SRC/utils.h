#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include "common.h"

void clear_screen_simple(void);
void pause_screen(void);
void trim_newline(char* s);
void trim_spaces(char* s);
void safe_copy(char* dest, size_t dest_size, const char* src);
void read_line(const char* prompt, char* buffer, int size);
int read_int(const char* prompt);
double read_double_range(const char* prompt, double min, double max);
int string_equals_ignore_case(const char* a, const char* b);
int string_contains_ignore_case(const char* text, const char* keyword);
int split_fields(char* line, char* fields[], int max_fields);
void print_box_line(const char* text, int width);

#endif
