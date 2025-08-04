#include "../config.h"
#include "utils/vec.h"
#include "cmd/index.h"
#include "index.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  init_cmd();

  if (argc < 2)
  {
    printf("No command provided. Use 'help' to see available commands.\n");
    return 1;
  }

  for (int i = 0; i < commands->size; i++)
  {
    Command *cmd = vec_get(commands, i);
    if (strcmp(cmd->name, argv[1]) == 0)
    {
      if (argc < cmd->min_args + 2 || argc > cmd->max_args + 2)
      {
        printf("Usage: %s\n", cmd->usage);
        return 1;
      }

      cmd->execute(argc - 1, argv + 1);
      break;
    }
  }

  return 0;
}