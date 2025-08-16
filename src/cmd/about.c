#include <stdio.h>
#include "cmd/about.h"
#include "../config.h"

int about_cmd(int argc, char *argv[])
{
  printf("Student Management System CLI (v%s)\n\
%s\n\
GitHub: %s\n\
SSH: %s\n\n\
This project is licensed under the MIT License.\n\
Copyright (c) 2025 %s\n\n\
Usage: sms [command] [options]\n\
",
     VERSION, PROJECT_DESCRIPTION, GITHUB, SSH, AUTHOR);

  printf("\
Available commands:\n\
  about - Show this information about the project\n\
  help - Show help message(general or specific)\n\
  add - Add a new student or merge student information\n\
  list - List all students\n\
  remove - Remove a student\n\
  update - Update student information\n");

  return 0;
}