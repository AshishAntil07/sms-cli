#include "utils/vec.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

Vec *vec_create(size_t size_of_each)
{
  Vec *vec = (Vec *)malloc(sizeof(Vec));
  if (!vec)
    return NULL;
  vec->data = (char *)malloc(10 * size_of_each);
  if (!vec->data)
  {
    free(vec);
    return NULL;
  }
  vec->size_of_each = size_of_each;
  vec->size = 0;
  vec->capacity = 10;

  return vec;
}

Vec *vec_from_arr(void *arr, size_t size_of_each, size_t arr_s)
{
  Vec *vec = vec_create(size_of_each);

  if (!vec || !arr)
  {
    vec_free(vec);
    return NULL;
  }

  vec_cpy_arr(vec, arr, arr_s);

  return vec;
}

void vec_cpy_arr(Vec *vec, void *arr, size_t arr_s)
{
  if (!vec || !arr)
    return;

  if (arr_s > vec->capacity)
    vec->data = realloc(vec->data, arr_s + arr_s);

  vec->size = arr_s / vec->size_of_each;

  memcpy(vec->data, arr, arr_s);
}

void vec_clear(Vec *vec)
{
  vec->data = realloc(vec->data, 10 * vec->size_of_each);
  vec->size = 0;
  vec->capacity = 10;
}

int vec_push(Vec *vec, void *value)
{
  if (vec->size == vec->capacity)
  {
    vec->capacity *= 2;
    void *temp = realloc(vec->data, vec->capacity * vec->size_of_each);
    if (!temp)
      return -1;
    vec->data = temp;
  }
  memcpy((char *)vec->data + vec->size * vec->size_of_each, value, vec->size_of_each);
  vec->size++;

  return 0;
}

void *vec_pop(Vec *vec)
{
  if (vec->size == 0)
    return NULL;
  vec->size--;

  return (char *)vec->data + vec->size * vec->size_of_each;
}

void *vec_get(const Vec *vec, size_t index)
{
  if (index >= vec->size)
    return NULL;

  return (char *)vec->data + index * vec->size_of_each;
}

void vec_copy(const Vec *source, Vec *dest)
{
  if (!source || !dest)
    return;

  dest->size = source->size;
  dest->capacity = source->capacity;
  dest->size_of_each = source->size_of_each;

  if (dest->data)
    free(dest->data);

  dest->data = malloc(dest->capacity * dest->size_of_each);
  if (!dest->data)
    return;

  memcpy(dest->data, source->data, source->size * source->size_of_each);
}

void vec_free(Vec *vec)
{
  if (vec)
  {
    free(vec->data);
    free(vec);
  }
}