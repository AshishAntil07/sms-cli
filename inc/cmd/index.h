#ifndef INDEX_H
#define INDEX_H


#include "cmd/help.h"
#include "cmd/about.h"
#include "cmd/add.h"
#include "cmd/update.h"
#include "cmd/remove.h"
#include "cmd/list.h"

typedef struct {
  char *name;          // Name of the command
  char *description;   // Description of the command
  char *usage;         // Usage instructions for the command
  int (*execute)(int argc, char *argv[]); // Function pointer to execute the command
  int min_args;        // Minimum number of arguments required
  int max_args;        // Maximum number of arguments allowed
} Command;

#endif