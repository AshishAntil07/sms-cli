#include "cmd/add.h"
#include "lib.h"
#include "index.h"

extern Vec *students;

typedef enum Headers
{
  ROLL = 1,
  NAME,
  GENDER,
  PHONE,
  F_NAME,
  M_NAME,
  ADDRESS
} Headers;

int add_cmd(int argc, char *argv[])
{
  Student *new_student = malloc(sizeof(Student));
  if (!new_student)
  {
    printf("add_cmd: Memory allocation failed for new student.\n");
    return -1;
  }

  init_student(new_student);

  if (argc == 8)
  {
    new_student->roll = strtol(argv[ROLL], NULL, 10);
    new_student->name = argv[NAME];
    new_student->gender = (Gender)argv[GENDER][0];
    new_student->phone = argv[PHONE];
    new_student->f_name = argv[F_NAME];
    new_student->m_name = argv[M_NAME];
    new_student->address = argv[ADDRESS];

    Student *existing_student = NULL;

    for (size_t i = 0; i < students->size; i++)
    {
      Student *s = (Student *)vec_get(students, i);
      if (s->roll == new_student->roll)
      {
        existing_student = s;
        break;
      }
    }

    if (existing_student)
    {
      printf("add_cmd: Student with roll no. %ld already exists. Merging data...\n", new_student->roll);
      cpy_partial_student(new_student, existing_student);
      write_student_data();
    }
    else if (append_student_data(new_student) != 0)
    {
      printf("add_cmd: Failed to write student data(roll no. %ld).\n", new_student->roll);
    }

    printf("Successfully added student!\n");
  }
  else if (argc == 2 || (argc == 3 && strcmp(argv[2], "--csv") == 0))
  {
    CSVFile *csv = read_student_data(argv[1]);
    if (csv)
    {
      new_student = get_next_student(csv);
      int student_count = 0;
      while (new_student)
      {
        Student *existing_student = NULL;
        for (size_t i = 0; i < students->size; i++)
        {
          Student *s = vec_get(students, i);
          if (s->roll == new_student->roll)
          {
            existing_student = s;
            break;
          }
        }

        if (existing_student)
        {
          printf("add_cmd: Student with roll no. %ld already exists. Merging data...\n", new_student->roll);
          cpy_partial_student(new_student, existing_student);
        }
        else
        {
          vec_push(students, new_student);
        }

        student_count++;
        new_student = get_next_student(csv);
      }

      if (write_student_data() != 0)
      {
        printf("add_cmd: Failed to write %s file.\n", OUT_DIR OUT_NAME);
        if (new_student)
          free_student(new_student);
        free_student_data(csv);

        return 1;
      }

      if (new_student)
        free_student(new_student);
      free_student_data(csv);
      printf("Added %d students from CSV file successfully!\n", student_count);
    }
  }

  if (new_student)
    free(new_student);

  return 0;
}