#include "index.h"
#include "cmd/index.h"

extern Vec *students;

int remove_cmd(int argc, char *argv[]) {
  if(argc != 2) {
    printf("Invalid arguments. See `help remove` for usage.\n");
    return 1;
  }

  long roll = strtol(argv[1], NULL, 10);
  if(roll <= 0) {
    printf("Invalid roll number: %s\n", argv[1]);
    return 1;
  }

  for(size_t i = 0; i < students->size; i++) {
    Student *student = (Student *)vec_get(students, i);
    if(student->roll == roll) {
      vec_remove(students, i);
      write_student_data();
      printf("Removed student with roll no. %ld.\n", roll);
      return 0;
    }
  }

  printf("No student found with roll no. %ld.\n", roll);
  return 0;
}