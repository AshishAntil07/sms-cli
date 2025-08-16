#include <stdio.h>
#include "cmd/index.h"
#include "utils/vec.h"
#include "utils/utils.h"
#include "cmd/help.h"
#include <string.h>

#define PAD_LENGTH 12

extern Vec *commands;

int help_cmd(int argc, char *argv[])
{
  if (!(argc-1))
  {
    printf("Available commands:\n");
    for (int i = 0; i < commands->size; i++)
    {
      Command cmd = *(Command *)vec_get(commands, i);
      printf("  %s - %s\n", pad_end(cmd.name, ' ', PAD_LENGTH), cmd.description);
    }
  }
  else
  {
    for (int i = 0; i < commands->size; i++)
    {
      Command cmd = *(Command *)vec_get(commands, i);
      if (strcmp(cmd.name, argv[1]) == 0)
      {
        printf("Name: %s\nDescription: %s\nUsage: %s\nArguments:\n  min: %d\n  max: %d\n",
               cmd.name, cmd.description, cmd.usage, cmd.min_args, cmd.max_args);
        break;
      }
    }
    printf("\narguments - <required>, [optional]\n");
  }

  return 0;
}