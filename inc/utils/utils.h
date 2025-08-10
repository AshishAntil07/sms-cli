#ifndef UTILS_H
#define UTILS_H


void copy_arr(int* source, int start, int end, int *res);
char *pad_end(char *str, char pad_char, int len);
char *lower_case(const char *str);
char *make_csv_friendly(const char *str);

#endif