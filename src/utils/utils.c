#include "utils/utils.h"
#include <string.h>
#include <stdlib.h>

void copy_arr(int* source, int start, int end, int *res) {
  for(int i = start; i<end; i++) {
    res[i-start] = source[i];
  }
}

char *pad_end(char *str, char pad_char, int len) {
  int str_len = strlen(str);
  if (str_len >= len) return str;

  char *padded_str = malloc(len + 1);
  if (!padded_str) return NULL;

  strcpy(padded_str, str);
  for (int i = str_len; i < len; i++) {
    padded_str[i] = pad_char;
  }
  padded_str[len] = '\0';

  return padded_str;
}