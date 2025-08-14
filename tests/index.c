#include "tests/index.h"

char *expected_tcsvp1[7], *expected_tcsvp2[7];

int run_tests()
{
  printf("Initializing tests...\n");
  pcr_args *csvp_cases[] = {
      &(pcr_args){
          .record = "John Doe,12345,M,123-456-7890,\"Father\"\" Name\",Mother Name,\"123 Street,City,Country\"",
          .expected_result = vec_from_arr(expected_tcsvp1, sizeof(char *), sizeof(expected_tcsvp1)),
      },
      &(pcr_args){
          .record = "John Doe,12345,M,123-456-7890,\"Father\"\" Name\",Mother Name,\"123 Street,City,\"\"Country\"\"",
          .expected_result = vec_from_arr(expected_tcsvp2, sizeof(char *), sizeof(expected_tcsvp2)),
      },
  };

  vr_args *vr_cases[] = {
      &(vr_args){
          .input = (vr_input){vec_from_arr((int[]){1, 2, 3}, sizeof(int), sizeof(int) * 3), 2},
          .expected = vec_from_arr((int[]){1, 2}, sizeof(int), sizeof(int) * 2),
      },
      &(vr_args){
          .input = (vr_input){vec_from_arr((int[]){1, 2, 3, 5, 9}, sizeof(int), sizeof(int) * 5), 1},
          .expected = vec_from_arr((int[]){1, 3, 5, 9}, sizeof(int), sizeof(int) * 4),
      },
      &(vr_args){
          .input = (vr_input){vec_from_arr((char[]){1, 2, 3}, sizeof(char), sizeof(char) * 3), 0},
          .expected = vec_from_arr((char[]){2, 3}, sizeof(char), sizeof(char) * 2),
      },
      &(vr_args){
          .input = (vr_input){vec_from_arr((char *[]){"abc", "def", "ghi"}, sizeof(char *), sizeof(char *) * 3), 2},
          .expected = vec_from_arr((char *[]){"abc", "def"}, sizeof(char *), sizeof(char *) * 2),
      },
  };

  Test t[] = {
      {
          .name = "CSV Parsing",
          .description = "Validates the length and values of parsed CSV Record",
          .function = test_parse_csv_record,
          .cases = vec_from_arr(csvp_cases, sizeof(csvp_cases[0]), sizeof(csvp_cases)),
      },
      {
          .name = "Vector Remove",
          .description = "Tests if elements of a vector are correctly removed and trailing elements are moved to leading bits.",
          .function = test_vector_remove,
          .cases = vec_from_arr(vr_cases, sizeof(vr_cases[0]), sizeof(vr_cases)),
      },
  };

  Vec *tests = vec_from_arr(t, sizeof(t[0]), sizeof(t));
  
  int failed_tests = 0;

  for (size_t i = 0; i < tests->size; i++) {
    Test test = *(Test *)vec_get(tests, i);
    int did_fail = 0;
    printf("\nRunning test: %s\n  %s\n", test.name, test.description);
    for(int j = 0; j<test.cases->size; j++) {
      int res = test.function(vec_get(test.cases, j));
      failed_tests += res;
      if(res) did_fail = res;
    }
    if(!did_fail) printf("  Success (%s)\n", test.name);
  }

  printf("\n\n");

  printf("%zu/%zu tests passed.\n", tests->size-failed_tests, tests->size);
  
  return failed_tests ? 1 : 0;
}

char *expected_tcsvp1[] = {
    "John Doe",
    "12345",
    "M",
    "123-456-7890",
    "Father\" Name",
    "Mother Name",
    "123 Street,City,Country",
};

char *expected_tcsvp2[] = {
    "John Doe",
    "12345",
    "M",
    "123-456-7890",
    "Father\" Name",
    "Mother Name",
    "123 Street,City,\"Country\"",
};