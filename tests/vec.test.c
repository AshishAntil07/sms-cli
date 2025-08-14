#include "tests/index.h"

int test_vector_remove(vr_args **args) {
  if (!args || !*args) {
    printf("  Invalid arguments.\n");
    return 1;
  }

  vr_args *arg = *args;
  Vec *input = arg->input.vector;
  size_t index = arg->input.index;
  Vec *expected = arg->expected;

  if (!input || !expected) {
    printf("  Input or expected vector is NULL.\n");
    return 1;
  }

  vec_remove(input, index);

  if (!input) {
    printf("  Failed to remove element at index %zu.\n", index);
    return 1;
  }

  if (input->size != expected->size || memcmp(input->data, expected->data, input->size * input->size_of_each) != 0) {
    printf("  Result does not match expected vector.\n");
    vec_free(input);
    return 1;
  }

  return 0;
}