#ifndef LIST_CMD_H
#define LIST_CMD_H

#include "index.h"
#include "utils/utils.h"

int list_cmd(int argc, char *argv[]);
void print_headers(PadStudent *pad);
Vec *get_students_by_property(Vec* sv, const char *property, const char *value);
Vec *get_students_in_range(Vec* sv, const char *property, long start, long end);

#endif