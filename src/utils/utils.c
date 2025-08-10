#include "utils/utils.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

char *lower_case(const char *str) {
  if (!str) return NULL;

  char *lower_str = malloc(strlen(str) + 1);
  if (!lower_str) return NULL;

  for (size_t i = 0; i < strlen(str); i++) {
    lower_str[i] = tolower((unsigned char)str[i]);
  }
  lower_str[strlen(str)] = '\0';

  return lower_str;
}

char *make_csv_friendly(const char *str) {
  char *csv_friendly = malloc(2*strlen(str));
  if(!csv_friendly) return NULL;

  size_t j = 0;
  for(size_t i = 0; i < strlen(str); i++) {
    csv_friendly[j++] = str[i];
    if(str[i]=='"') csv_friendly[j++] = '"';
  }

  return csv_friendly;
}