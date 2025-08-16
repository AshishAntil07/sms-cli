#include "utils/utils.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int max(int a, int b)
{
  return a > b ? a : b;
}

void copy_arr(int *source, int start, int end, int *res)
{
  for (int i = start; i < end; i++)
  {
    res[i - start] = source[i];
  }
}

char *pad_end(char *str, char pad_char, int len)
{
  int str_len = strlen(str);
  if (str_len >= len)
    return str;

  char *padded_str = malloc(len + 1);
  if (!padded_str)
    return NULL;

  strcpy(padded_str, str);
  for (int i = str_len; i < len; i++)
  {
    padded_str[i] = pad_char;
  }
  padded_str[len] = '\0';

  return padded_str;
}

char *lower_case(const char *str)
{
  if (!str)
    return NULL;

  char *lower_str = malloc(strlen(str) + 1);
  if (!lower_str)
    return NULL;

  for (size_t i = 0; i < strlen(str); i++)
  {
    lower_str[i] = tolower((unsigned char)str[i]);
  }
  lower_str[strlen(str)] = '\0';

  return lower_str;
}

char *make_csv_friendly(const char *str)
{
  char *csv_friendly = calloc(2 * strlen(str), sizeof(char));
  if (!csv_friendly)
    return NULL;

  size_t j = 0;
  for (size_t i = 0; i < strlen(str); i++)
  {
    csv_friendly[j++] = str[i];
    if (str[i] == '"')
      csv_friendly[j++] = '"';
  }
  csv_friendly[j] = '\0';

  return csv_friendly;
}

char *get_student_csv_string(Student *student, size_t len)
{
  if (!student)
    return NULL;

  char *csv_string = malloc(len);
  if (!csv_string)
    return NULL;

  snprintf(csv_string, len, "\"%ld\",\"%s\",\"%c\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"",
           student->roll, make_csv_friendly(student->name), student->gender, make_csv_friendly(student->phone), make_csv_friendly(student->email), make_csv_friendly(student->f_name), make_csv_friendly(student->m_name), make_csv_friendly(student->address));

  return csv_string;
}

PadStudent *get_pad_student(Vec *students)
{
  PadStudent *pad = calloc(1, sizeof(PadStudent));

  if (!pad)
  {
    return NULL;
  }

  for (size_t i = 0; i < students->size; i++)
  {
    Student *student = vec_get(students, i);
    char *roll = calloc(13, sizeof(char));
    sprintf(roll, "%ld", student->roll);

    if (!pad->name || strlen(student->name) > pad->name - DEFAULT_PAD_SIZE)
      pad->name = strlen(student->name) + DEFAULT_PAD_SIZE;
    if (!pad->roll || strlen(roll) > pad->roll - DEFAULT_PAD_SIZE)
      pad->roll = strlen(roll) + DEFAULT_PAD_SIZE;
    if (!pad->phone || strlen(student->phone) > pad->phone - DEFAULT_PAD_SIZE)
      pad->phone = strlen(student->phone) + DEFAULT_PAD_SIZE;
    if (!pad->email || (student->email && strlen(student->email) > pad->email - DEFAULT_PAD_SIZE))
      pad->email = strlen(student->email) + DEFAULT_PAD_SIZE;
    if (!pad->f_name || strlen(student->f_name) > pad->f_name - DEFAULT_PAD_SIZE)
      pad->f_name = strlen(student->f_name) + DEFAULT_PAD_SIZE;
    if (!pad->m_name || strlen(student->m_name) > pad->m_name - DEFAULT_PAD_SIZE)
      pad->m_name = strlen(student->m_name) + DEFAULT_PAD_SIZE;
    if (!pad->address || strlen(student->address) > pad->address - DEFAULT_PAD_SIZE)
      pad->address = strlen(student->address) + DEFAULT_PAD_SIZE;

    free(roll);
  }

  pad->gender = 1 + DEFAULT_PAD_SIZE;

  return pad;
}

PadStudent *merge_pad_student(PadStudent *pad1, PadStudent *pad2)
{
  PadStudent *new_pad = calloc(1, sizeof(PadStudent));

  new_pad->name = max(pad1->name, pad2->name);
  new_pad->roll = max(pad1->roll, pad2->roll);
  new_pad->phone = max(pad1->phone, pad2->phone);
  new_pad->gender = max(pad1->gender, pad2->gender);
  new_pad->email = max(pad1->email, pad2->email);
  new_pad->f_name = max(pad1->f_name, pad2->f_name);
  new_pad->m_name = max(pad1->m_name, pad2->m_name);
  new_pad->address = max(pad1->address, pad2->address);

  return new_pad;
}

char **get_student_string(Vec *students, PadStudent *stpad)
{
  if (!students || students->size == 0)
    return NULL;

  char **student_strings = malloc(students->size * sizeof(char *));
  if (!student_strings)
    return NULL;

  PadStudent *pad = stpad ? stpad : get_pad_student(students);

  for (size_t i = 0; i < students->size; i++)
  {
    student_strings[i] = malloc(256);
    if (!student_strings[i])
    {
      for (size_t j = 0; j < i; j++)
      {
        free(student_strings[j]);
      }
      free(student_strings);
      return NULL;
    }

    Student *student = vec_get(students, i);
    char *roll = calloc(13, sizeof(char));
    sprintf(roll, "%ld", student->roll);

    snprintf(student_strings[i], 256, "%s%s%s%s%s%s%s%s",
             pad_end(roll, ' ', pad->roll),
             pad_end(student->name, ' ', pad->name),
             pad_end(student->gender == MALE ? "M" : "F", ' ', pad->gender),
             pad_end(student->phone, ' ', pad->phone),
             pad_end(student->email, ' ', pad->email),
             pad_end(student->f_name, ' ', pad->f_name),
             pad_end(student->m_name, ' ', pad->m_name),
             pad_end(student->address, ' ', pad->address));
    free(roll);
  }

  return student_strings;
}

int is_int_in_array(int *arr, int size, int value)
{
  for (int i = 0; i < size; i++)
  {
    if (arr[i] == value)
      return 1;
  }
  return 0;
}

int is_str_in_array(char **arr, int size, const char *value)
{
  for (int i = 0; i < size; i++)
  {
    if (strcmp(arr[i], value) == 0)
      return 1;
  }
  return 0;
}