#include "../config.h"
#include "utils/vec.h"
#include "cmd/index.h"
#include "index.h"
#include "tests/index.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  init();

#ifndef TEST

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
        printf("Invalid arguments!\nUsage: %s\n\nRun `sms help %s` for more information.\n", cmd->usage, cmd->name);
        return 1;
      }

      int res = cmd->execute(argc - 1, argv + 1);
      if (res != 0)
      {
        fprintf(stderr, "\n\nCommand '%s' failed with error code %d.\n", cmd->name, res);
        return res;
      }

      break;
    }
  }

#else

  run_tests();

#endif

  return 0;
}
