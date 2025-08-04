#include "../config.h"
#include "utils/vec.h"
#include "cmd/index.h"
#include "cmd/help.h"
#include "cmd/about.h"
#include <stdio.h>

extern Vec *commands = NULL;

void init_cmd()
{
  commands = vec_create(sizeof(Command));

  Command cmds[] = {
      {
          "help",
          "Show help message",
          "help [command]",
          help_cmd,
          0,
          1,
      },
      {
          "about",
          "Show information about the application",
          "about",
          about_cmd,
          0,
          0,
      },
  };

  vec_cpy_arr(commands, &cmds, sizeof(cmds));
}