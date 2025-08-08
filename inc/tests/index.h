#ifndef TESTS_INDEX_H
#define TESTS_INDEX_H

#include "lib.h"
#include "utils/vec.h"
#include "utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Test {
  const char *name;
  const char *description;
  Vec *cases;
  int (*function)(void *args);
} Test;

int run_tests();

typedef struct parse_csv_record_args {
  const char *record;
  Vec *expected_result;
} pcr_args;
int test_parse_csv_record(pcr_args **args);

#endif