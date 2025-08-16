#ifndef MAIN_INDEX_H
#define MAIN_INDEX_H

#include "../config.h"
#include "utils/vec.h"
#include "lib.h"

extern Vec *commands;
extern Vec *students;

extern char *property_flags[8];

void init();

#endif