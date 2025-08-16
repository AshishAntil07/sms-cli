#include "cmd/index.h"

extern Vec *students;

char *str_flags[] = {"--name", "--roll", "--gender", "--phone", "--email", "--f_name", "--m_name", "--address"};

int list_cmd(int argc, char *argv[])
{
  if (students == NULL || students->size == 0)
  {
    printf("No students found.\n");
    return 0;
  }

  if (argc > 3)
  {
    printf("Usage: list [category] [value]\n");
    return 1;
  }

  if (argc == 1)
  {
    PadStudent *pad = get_pad_student(students);
    PadStudent *merged = merge_pad_student(pad, &(PadStudent){6, 6, 8, 7, 7, 8, 8, 9});
    free(pad);

    print_headers(merged);

    char **studentStr = get_student_string(students, merged);
    for (size_t i = 0; i < students->size; i++)
    {
      printf("%s\n", *(studentStr + i));
    }
    printf("Total students: %zu\n", students->size);
  }
  else if (argc == 3 && is_str_in_array(str_flags, sizeof(str_flags) / sizeof(str_flags[0]), argv[1]))
  {
    char *property = argv[1] + 2; // Skip the "--" prefix
    char *value = argv[2];
    
    Vec *filtered_students = get_students_by_property(property, value);
    if (filtered_students == NULL || filtered_students->size == 0)
    {
      printf("No students found with %s: %s\n", property, value);
      return 0;
    }
    
    PadStudent *pad = get_pad_student(filtered_students);
    PadStudent *merged = merge_pad_student(pad, &(PadStudent){6, 6, 8, 7, 7, 8, 8, 9});
    free(pad);
    
    print_headers(merged);
    
    char **studentStr = get_student_string(filtered_students, merged);
    for (size_t i = 0; i < filtered_students->size; i++)
    {
      printf("%s\n", *(studentStr + i));
    }
    printf("Total students: %zu\n", filtered_students->size);
  }

  return 0;
}

void print_headers(PadStudent *pad)
{
  printf("%s%s%s%s%s%s%s%s\n",
         pad_end("roll", ' ', pad->roll),
         pad_end("name", ' ', pad->name),
         pad_end("gender", ' ', pad->gender),
         pad_end("phone", ' ', pad->phone),
         pad_end("email", ' ', pad->email),
         pad_end("f_name", ' ', pad->f_name),
         pad_end("m_name", ' ', pad->m_name),
         pad_end("address", ' ', pad->address));
}

Vec *get_students_by_property(const char *property, const char *value)
{
  Vec *result = vec_create(sizeof(Student));
  for (size_t i = 0; i < students->size; i++)
  {
    Student *student = (Student *)vec_get(students, i);
    void *property_value = get_matching_property(student, property);
    if(strcmp(property, "roll") == 0) {
      if (property_value && *(long *)property_value == strtol(value, NULL, 10))
      {
        vec_push(result, student);
      }
      continue;
    }
    if (property_value && strcmp(*(char **)property_value, value) == 0)
    {
      vec_push(result, student);
    }
  }
  return result;
}