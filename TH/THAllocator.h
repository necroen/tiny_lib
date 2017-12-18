#ifndef TH_ALLOCATOR_INC
#define TH_ALLOCATOR_INC

#include "THGeneral.h"  // 注意这个要包含，间接包含了 THGeneral.c 中的内存管理机制

typedef struct THAllocator {
  void* (*malloc)(void*, ptrdiff_t);
  void* (*realloc)(void*, void*, ptrdiff_t);
  void (*free)(void*, void*);
} THAllocator;
// 定义 TH 的 allocator

THAllocator THDefaultAllocator; 
// 定义一个默认的Allocator，在相应的 .c 文件中实现

#endif