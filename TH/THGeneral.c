#include "THGeneral.h"

static void* THAllocInternal(ptrdiff_t size) // 被下面的调用
{
    void *ptr;
    ptr = malloc(size);
    return ptr;
}

void* THAlloc(ptrdiff_t size) // = malloc(size)
{
  void *ptr;

  //if(size < 0)
    //THError("$ Torch: invalid memory size -- maybe an overflow?");
  if(size == 0)
    return NULL;

  ptr = THAllocInternal(size); // = malloc(size)
  return ptr;
}

void THFree(void *ptr)
{
  free(ptr);
}

void* THRealloc(void *ptr, ptrdiff_t size)
{
  if(!ptr)
    return(THAlloc(size));

  if(size == 0)
  {
    THFree(ptr);  // 注意
    return NULL;
  }

  void *newptr = realloc(ptr, size); // 系统函数

  return newptr;
}