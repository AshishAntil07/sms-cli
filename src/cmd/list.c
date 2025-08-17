#include "cmd/index.h"
#include "index.h"

int list_cmd(int argc, char *argv[])
{
  if (students == NULL || students->size == 0)
  {
    printf("No students found.\n");
    return 0;
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
  else if (argc >= 2)
  {
    Vec *filtered_students = students;
    for (size_t i = 1; i < argc; i += 2)
    {
      if (strcmp(argv[i], "--export") == 0)
      {
        if (i + 1 >= argc)
        {
          printf("No export file specified.\n");
          return 0;
        }
        char *export_file = argv[i + 1];
        export_student_data(filtered_students, export_file);
        printf("Exported student list to %s\n", export_file);

        continue;
      }

      if (!is_str_in_array(property_flags, sizeof(property_flags) / sizeof(property_flags[0]), argv[i]))
      {
        printf("Invalid property: %s\n", argv[i]);
        continue;
      }

      char *property = argv[i] + 2;
      char *value = argv[i + 1];

      if (strcmp(property, "roll") == 0 && i + 2 < argc && strncmp(argv[i + 2], "--", 2) != 0)
      {
        long endroll = strtol(argv[++i + 1], NULL, 10);
        long roll = strtol(value, NULL, 10);

        filtered_students = get_students_in_range(filtered_students, property, roll, endroll);

        if(filtered_students == NULL || filtered_students->size == 0) {
          printf("No students found in roll range %ld to %ld\n", roll, endroll);
          return 0;
        }
        continue;
      }
      
      filtered_students = get_students_by_property(filtered_students, property, value);

      if (filtered_students == NULL || filtered_students->size == 0)
      {
        printf("No students found with %s: %s\n", property, value);
        return 0;
      }
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

Vec *get_students_by_property(Vec *sv, const char *property, const char *value)
{
  Vec *result = vec_create(sizeof(Student));
  for (size_t i = 0; i < sv->size; i++)
  {
    Student *student = (Student *)vec_get(sv, i);
    void *property_value = get_matching_property(student, property);
    if (strcmp(property, "roll") == 0)
    {
      if (property_value && *(long *)property_value == strtol(value, NULL, 10))
      {
        vec_push(result, student);
      }
      continue;
    }
    else if (strcmp(property, "gender") == 0)
    {
      if (property_value && (*(char *)property_value == value[0] || *(char *)property_value == (value[0] == 'M' ? 'M' : 'F')))
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

Vec *get_students_in_range(Vec *sv, const char *property, long start, long end)
{
  Vec *result = vec_create(sizeof(Student));
  for (size_t i = 0; i < sv->size; i++)
  {
    Student *student = (Student *)vec_get(sv, i);
    void *property_value = get_matching_property(student, property);
    if (property_value && *(long *)property_value >= start && *(long *)property_value <= end)
    {
      vec_push(result, student);
    }
  }
  return result;
}