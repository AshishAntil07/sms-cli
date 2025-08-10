#include "tests/index.h"

int test_parse_csv_record(pcr_args **args)
{
  if (!args || !*args)
  {
    printf("  null args received\n");
    return 1;
  }

  const char *record = (*args)->record;
  Vec *expected_result = (*args)->expected_result;

  if (!expected_result || !expected_result->size)
  {
    printf("  expected_result null reference: %p\n", expected_result);
    return 1;
  }

  Vec *result = parse_csv_record(record);
  if (!result)
  {
    printf("  Failed to parse CSV record: %s\n", record);
    return 1;
  }

  if (result->size != expected_result->size)
  {
    printf("  Unexpected number of fields in CSV record: %s\n  Expected - %zu   Got - %zu\n", record, expected_result->size, result->size);
    for (size_t i = 0; i < result->size; i++)
    {
      printf("  %s\n", *(char **)vec_get(result, i));
    }
    vec_free(result);
    return 1;
  }
  
  for (size_t i = 0; i < result->size; i++)
  {
    const char *expected = *(char **)vec_get(expected_result, i);
    const char *actual = *(char **)vec_get(result, i);
    if (strcmp(expected, actual) != 0)
    {
      printf("  Field %zu does not match: expected \"%s\", got \"%s\"\n", i, expected, actual);
      vec_free(result);
      return 1;
    }
  }

  // Free the result vector
  vec_free(result);
  return 0;
}