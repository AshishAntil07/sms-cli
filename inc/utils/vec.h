#ifndef VEC_H
#define VEC_H

#include <stddef.h>

typedef struct Vec
{
  void *data;
  size_t size;
  size_t capacity;
  size_t size_of_each;
} Vec;

Vec *vec_create(size_t size_of_each);
void vec_clear(Vec *vec);
int vec_push(Vec *vec, void *value);
Vec *vec_from_arr(void *arr, size_t size_of_each, size_t arr_s);
void vec_cpy_arr(Vec *vec, void *arr, size_t arr_s);
void *vec_pop(Vec *vec);
void *vec_get(const Vec *vec, size_t index);
void vec_copy(const Vec *source, Vec *dest);
void vec_free(Vec *vec);

#endif