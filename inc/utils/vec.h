#ifndef VEC_H
#define VEC_H

#include <stddef.h>

typedef struct
{
  void *data;
  size_t size;
  size_t capacity;
  size_t size_of_each;
} Vec;

Vec *vec_create(size_t size_of_each);
void vec_clear(Vec *vec);
int vec_push(Vec *vec, void *value);
void vec_cpy_arr(Vec *vec, void *arr, int arr_s);
void *vec_pop(Vec *vec);
void *vec_get(const Vec *vec, size_t index);

#endif