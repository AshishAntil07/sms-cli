#ifndef LIB_H
#define LIB_H

#include "utils/vec.h"
#include "utils/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined(_WIN32)
#include <direct.h>
#define make_dir(path) _mkdir(path)
#else
#include <sys/stat.h>
#define make_dir(path) mkdir(path, 0755)
#endif

typedef struct Student Student;

typedef enum Gender
{
  MALE = 'M',
  FEMALE = 'F'
} Gender;

typedef struct Marks
{
  Student *student;
  char *subject;
  int semester;
  int obtained_marks;
  int total_marks;
} Marks;

typedef struct Student
{
  char *name;
  long roll;
  char *phone;
  char *email;
  char *f_name;
  char *m_name;
  char *address;
  Gender gender;
  Vec *marks;
} Student;

typedef struct CSVFile
{
  FILE *file;
  Vec *headers;
} CSVFile;

Vec *parse_csv_record(const char *record);
CSVFile *read_student_data(char *fileurl);
void *get_matching_property(Student *, const char *);
Student *get_next_student(CSVFile *file);
int write_student_data();
int append_student_data(Student *student);
void free_student(Student *student);
void free_marks(Marks *marks);
void free_student_data(CSVFile *file);
void init_student(Student *student);
void cpy_partial_student(Student *source, Student *dest);

#endif