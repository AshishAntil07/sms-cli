#include "cmd/add.h"
#include "lib.h"

int add_cmd(int argc, char *argv[]) {
  Student *new_student = malloc(sizeof(Student));
  if (!new_student) {
    fprintf(stderr, "Memory allocation failed for new student.\n");
    return -1;
  }

  init_student(new_student);

  if(argc > 2) {
    new_student->name = argv[1] ? argv[1] : NULL;
    new_student->roll = argc > 2 ? strtol(argv[2], NULL, 10) : 0;
    new_student->gender = argc > 3 ? (Gender)argv[3][0] : MALE;
    new_student->phone = argc > 4 ? argv[4] : NULL;
    new_student->f_name = argc > 5 ? argv[5] : NULL;
    new_student->m_name = argc > 6 ? argv[6] : NULL;
    new_student->address = argc > 7 ? argv[7] : NULL;
  } else {
    CSVFile *csv = read_student_data(argv[1]);
    if (csv) {
      Student *existing_student = get_next_student(csv);
      if (existing_student) {
        // Copy data from the existing student
        new_student->name = existing_student->name;
        new_student->roll = existing_student->roll;
        new_student->gender = existing_student->gender;
        new_student->phone = existing_student->phone;
        new_student->f_name = existing_student->f_name;
        new_student->m_name = existing_student->m_name;
        new_student->address = existing_student->address;
        free_student(existing_student);
      }
      free_student_data(csv);
    }
  }

  return 0;
}