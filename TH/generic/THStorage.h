#ifndef GENERIC_FILE
    #define GENERIC_FILE "generic/THStorage.h"
#else

#define TH_STORAGE_REFCOUNTED 1  
#define TH_STORAGE_RESIZABLE  2
#define TH_STORAGE_FREEMEM    4
#define TH_STORAGE_VIEW       8

typedef struct THStorage
{
    real *data;
    ptrdiff_t size;
    int refcount;
    char flag;
    THAllocator *allocator;
    void *allocatorContext;
    struct THStorage *view;
} THStorage;

THStorage* THStorage_(new)(void);
THStorage* THStorage_(newWithSize)(ptrdiff_t size);
THStorage* THStorage_(newWithAllocator)(ptrdiff_t size,
                                        THAllocator *allocator,
                                        void *allocatorContext);

THStorage* THStorage_(newWithData)(real *data, ptrdiff_t size);
THStorage* THStorage_(newWithDataAndAllocator)(real* data, ptrdiff_t size,
                                               THAllocator* allocator,
                                               void* allocatorContext);

void THStorage_(resize)(THStorage *storage, ptrdiff_t size);

#endif