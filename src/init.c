#include "../config.h"
#include "utils/vec.h"
#include "cmd/index.h"
#include "lib.h"
#include <stdio.h>

Vec *commands = NULL;
Vec *students = NULL;

char *property_flags[8] = {"--name", "--roll", "--gender", "--phone", "--email", "--f_name", "--m_name", "--address"};

void init()
{
  static Command cmds[] = {
      {
          .name = "help",
          .description = "Show help message",
          .usage = "help <command>",
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
          .usage = "add <roll> <name> <gender> <phone> <email> <f_name> <m_name> <address> | add [--csv] <csv_file>",
          .execute = add_cmd,
          .min_args = 1,
          .max_args = 8,
      },
      {
          .name = "update",
          .description = "Update student information",
          .usage = "update <roll> ...(<property> <value>)",
          .execute = update_cmd,
          .min_args = 3,
          .max_args = 1 + 2 * 8, // roll + 8 properties with values
      },
      {
          .name = "remove",
          .description = "Remove a student by roll number",
          .usage = "remove <...roll>",
          .execute = remove_cmd,
          .min_args = 1,
          .max_args = 1000000,
      },
      {
          .name = "list",
          .description = "List all students from a category(if specified)",
          .usage = "list ...[(<property> <value>) | (--roll <start> <end>)]",
          .execute = list_cmd,
          .min_args = 0,
          .max_args = 1000000,
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