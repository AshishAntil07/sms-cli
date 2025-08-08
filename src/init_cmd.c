#include "../config.h"
#include "utils/vec.h"
#include "cmd/index.h"
#include "cmd/help.h"
#include "cmd/about.h"
#include <stdio.h>

extern Vec *commands = NULL;

void init_cmd()
{
  Command cmds[] = {
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
  };

  commands = vec_from_arr(cmds, sizeof(Command), sizeof(cmds));
}