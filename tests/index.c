#include "tests/index.h"

char *expected_tcsvp[7];

int run_tests()
{
  printf("Initializing tests...\n");


  // Step 4: assign
  Test tests[] = {
    {
      .name = "CSV Parsing",
      .description = "Validates the length and values of parsed CSV Record",
      .function = test_parse_csv_record,
      .cases = vec_from_arr((pcr_args *[]){ &(pcr_args){
        .record = "John Doe,12345,M,123-456-7890,\"Father\"\" Name\",Mother Name,\"123 Street,City,Country\"",
        .expected_result = vec_from_arr(expected_tcsvp, sizeof(char *), sizeof(expected_tcsvp))
      }}, sizeof(pcr_args *), sizeof(pcr_args *) * 1)
    }
  };
  
  int failed_tests = 0;
  
  size_t n = sizeof(tests) / sizeof(Test);
  for (size_t i = 0; i < n; i++) {
    for(int j = 0; j<tests[i].cases->size; j++) {
      printf("\nRunning test: %s\n  %s\n", tests[i].name, tests[i].description);
      int res = tests[i].function(vec_get(tests[i].cases, j));
      failed_tests += res;
      if(!res) printf("  Success (%s)\n", tests[i].name);
    }
  }

  printf("\n\n");

  if (failed_tests > 0)
  {
    printf("%d tests failed.\n", failed_tests);
  }
  else
  {
    printf("All tests passed successfully!\n");
  }
  
  return failed_tests ? 1 : 0;
  
}


char *expected_tcsvp[] = {
  "John Doe",
  "12345",
  "M",
  "123-456-7890",
  "Father\" Name",
  "Mother Name",
  "123 Street,City,Country"
};