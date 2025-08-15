#include "cmd/index.h"
#include "index.h"

extern Vec* students;

int list_cmd(int argc, char *argv[])
{
  if (students == NULL || students->size == 0) {
    printf("No students found.\n");
    return 0;
  }

  if (argc > 3) {
    printf("Usage: list [category] [value]\n");
    return 1;
  }

  if(argc == 1) {

    PadStudent *pad = get_pad_student(students);
    PadStudent *merged = merge_pad_student(pad, &(PadStudent){6, 6, 8, 7, 7, 8, 8, 9});
    free(pad);


    printf("%s%s%s%s%s%s%s%s\n",
      pad_end("roll", ' ', merged->roll),
      pad_end("name", ' ', merged->name),
      pad_end("gender", ' ', merged->gender),
      pad_end("phone", ' ', merged->phone),
      pad_end("email", ' ', merged->email),
      pad_end("f_name", ' ', merged->f_name),
      pad_end("m_name", ' ', merged->m_name),
      pad_end("address", ' ', merged->address)
    );

    char **studentStr = get_student_string(students, merged);
    for(size_t i = 0; i<students->size; i++) {
      printf("%s\n", *(studentStr + i));
    }
  }

  printf("Total students: %zu\n", students->size);
  return 0;
}