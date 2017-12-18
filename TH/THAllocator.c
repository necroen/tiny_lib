// 这里有很多指针类型转换会报warning,但是不影响正常使用

#include "THAllocator.h"

static void *THDefaultAllocator_alloc(void* ctx, ptrdiff_t size) {
  return THAlloc(size);  // THGeneral.c
}

static void *THDefaultAllocator_realloc(void* ctx, void* ptr, ptrdiff_t size) {
  return THRealloc(ptr, size); // THGeneral.c
}
// 注意哪个是 src 和 dst

static void THDefaultAllocator_free(void* ctx, void* ptr) {
  THFree(ptr);  // THGeneral.c
}

THAllocator THDefaultAllocator = {
  &THDefaultAllocator_alloc,
  &THDefaultAllocator_realloc,
  &THDefaultAllocator_free
};