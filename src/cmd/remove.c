#include "index.h"
#include "cmd/index.h"

extern Vec *students;

int remove_cmd(int argc, char *argv[])
{
  for (size_t i = 1; i < argc; i++)
  {
    long roll = strtol(argv[i], NULL, 10);
    if (roll <= 0)
    {
      printf("Invalid roll number: %s\n", argv[i]);
      return 1;
    }

    int removed = 0;
    for (size_t i = 0; i < students->size; i++)
    {
      Student *student = (Student *)vec_get(students, i);
      if (student->roll == roll)
      {
        vec_remove(students, i);
        removed = 1;
        printf("Removed student with roll no. %ld.\n", roll);
        break;
      }
    }
    
    if (!removed)
    printf("No student found with roll no. %ld.\n", roll);
  }
  
  write_student_data();
  return 0;
}