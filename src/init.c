#include "../config.h"
#include "utils/vec.h"
#include "cmd/index.h"
#include "lib.h"
#include <stdio.h>

extern Vec *commands = NULL;
extern Vec *students = NULL;

void init()
{
  static Command cmds[] = {
      {
          .name = "help",
          .description = "Show help message",
          .usage = "help [command]",
          .execute = help_cmd,
          .min_args = 0,
          .max_args = 1,
      },
      {
          .name = "about",
          .description = "Show information about the application",
          .usage = "about",
          .execute = about_cmd,
          .min_args = 0,
          .max_args = 0,
      },
      {
          .name = "add",
          .description = "Add a new student",
          .usage = "add <name>",
          .execute = add_cmd,
          .min_args = 1,
          .max_args = 7,
      },
      {
          .name = "remove",
          .description = "Remove a student by roll number",
          .usage = "remove <roll>",
          .execute = remove_cmd,
          .min_args = 1,
          .max_args = 1,
      },
  };

  commands = vec_from_arr(cmds, sizeof(Command), sizeof(cmds));
  if (!commands)
  {
    fprintf(stderr, "Failed to initialize commands vector.\n");
    exit(EXIT_FAILURE);
  }

  students = vec_create(sizeof(Student));

  if (!students)
  {
    fprintf(stderr, "Failed to initialize students vector.\n");
    exit(EXIT_FAILURE);
  }

  CSVFile *csv = read_student_data(NULL);
  if (!csv)
  {
    fprintf(stderr, "Failed to read student data from CSV file.\n");
    exit(EXIT_FAILURE);
  }

  for (Student *student = get_next_student(csv); student; student = get_next_student(csv))
    vec_push(students, student);

  free_student_data(csv);
}