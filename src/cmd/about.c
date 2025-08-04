#include <stdio.h>
#include "cmd/about.h"
#include "../config.h"

int about_cmd(int argc, char *argv[])
{
  printf("Student Management System CLI\n\
Description: %s\n\
Version: %s\n\
Author: %s\n\
GitHub: %s\n\
SSH: %s\n\
Usage: sms [command] [options]\n\
Available commands:\n\
  about - Show this information about the project\n\
  help - Show help message(general or specific)\n\
  add - Add a new student\n\
  list - List all students\n\
  delete - Delete a student\n\
  update - Update student information\n",
         PROJECT_DESCRIPTION, VERSION, AUTHOR, GITHUB, SSH);

  return 0;
}