#include <stdio.h>
#include "cmd/index.h"
#include "../config.h"
#include "index.h"
#include "utils/utils.h"

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

  printf("Available commands:\n");
  for(size_t i = 0; i < commands->size; i++) {
    Command *cmd = vec_get(commands, i);
    printf("  %s - %s\n", pad_end(cmd->name, ' ', 10), cmd->description);
  }

  return 0;
}