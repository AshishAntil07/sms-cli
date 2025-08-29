#include "cmd/index.h"
#include "lib.h"
#include "index.h"

int init_cmd(int argc, char **argv) {
  if (argc > 1) {
    fprintf(stderr, "Usage: %s\n", argv[0]);
    return -1;
  }

  students = vec_create(sizeof(Student));

  write_student_data();

  printf("Application initialized successfully.\n");
  return 0;
}
