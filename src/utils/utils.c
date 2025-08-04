#include "utils/utils.h"

void copy_arr(int* source, int start, int end, int *res) {
  for(int i = start; i<end; i++) {
    res[i-start] = source[i];
  }
}