#ifndef UTILS_H
#define UTILS_H

#define DEFAULT_PAD_SIZE 2

#include "index.h"
#include "lib.h"

typedef struct Student Student;

typedef struct PadStudent {
  int name;
  int roll;
  int gender;
  int phone;
  int email;
  int f_name;
  int m_name;
  int address;
} PadStudent;

typedef struct PadMarks {
  int subject;
  int semester;
  int obtained_marks;
  int total_marks;
} PadMarks;


void copy_arr(int* source, int start, int end, int *res);
char *pad_end(char *str, char pad_char, int len);
char *lower_case(const char *str);
char *make_csv_friendly(const char *str);
PadStudent *get_pad_student(Vec *students);
PadStudent *merge_pad_student(PadStudent *pad1, PadStudent *pad2);
char *get_student_csv_string(Student *student, size_t len);
char **get_student_string(Vec *students, PadStudent *stpad);


#endif