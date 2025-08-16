#include "cmd/update.h"
#include "index.h"

int update_cmd(int argc, char *argv[]) {
  Student *s = NULL;
  for (size_t i = 0; i < students->size; i++) {
    Student *student = vec_get(students, i);

    if (student->roll == strtol(argv[1], NULL, 10)) {
      s = student;
      break;
    }
  }

  if (!s) {
    printf("Student with roll %s not found.\n", argv[1]);
    return 1;
  }

  for (int i = 2; i < argc; i += 2) {
    if (i + 1 >= argc) {
      printf("Missing value for property '%s'.\n", argv[i] + 2);
      return 1;
    }

    char *flag = argv[i];
    char *value = argv[i + 1];

    if (!is_str_in_array(property_flags, sizeof(property_flags) / sizeof(property_flags[0]), flag)) {
      printf("Unknown property '%s'.\n", flag + 2);
      return 1;
    }

    if (update_student_property(s, flag + 2, value)) {
      printf("Failed to update property '%s' for student with roll %s.\n", flag + 2, argv[1]);
      return 1;
    }
  }

  if (write_student_data()) {
    printf("Failed to write updated student data.\n");
    return 1;
  }

  printf("Successfully updated student with roll %s.\n", argv[1]);

  return 0;
}