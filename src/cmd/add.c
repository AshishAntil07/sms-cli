#include "cmd/add.h"
#include "lib.h"

int add_cmd(int argc, char *argv[])
{
  Student *new_student = malloc(sizeof(Student));
  if (!new_student)
  {
    printf("add_cmd: Memory allocation failed for new student.\n");
    return -1;
  }

  init_student(new_student);

  if (argc > 2)
  {
    new_student->name = argv[1] ? argv[1] : NULL;
    new_student->roll = argc > 2 ? strtol(argv[2], NULL, 10) : 0;
    new_student->gender = argc > 3 ? (Gender)argv[3][0] : MALE;
    new_student->phone = argc > 4 ? argv[4] : NULL;
    new_student->f_name = argc > 5 ? argv[5] : NULL;
    new_student->m_name = argc > 6 ? argv[6] : NULL;
    new_student->address = argc > 7 ? argv[7] : NULL;

    if (write_student_data(new_student) != 0)
    {
      printf("add_cmd: Failed to write student data(roll no. %ld).\n", new_student->roll);
      return 1;
    }

    printf("Successfully added student!\n");
  }
  else if (argc == 2 || (argc == 3 && strcmp(argv[2], "--csv") == 0))
  {
    CSVFile *csv = read_student_data(argv[1]);
    if (csv)
    {
      new_student = get_next_student(csv);
      int suc_student_count = 0, student_count = 0;
      while (new_student)
      {
        cpy_partial_student(new_student, new_student);

        if (write_student_data(new_student) != 0)
        {
          printf("add_cmd: Failed to write student data(roll no. %ld).\n", new_student->roll);
        }
        else
          suc_student_count++;

        student_count++;

        new_student = get_next_student(csv);
      }

      if (new_student)
        free_student(new_student);
      free_student_data(csv);
      printf("Added %d/%d students from CSV file successfully!\n", suc_student_count, student_count);
    }
  }

  if (new_student)
    free(new_student);

  return 0;
}