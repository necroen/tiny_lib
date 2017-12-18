#ifndef GENERIC_FILE
    #define GENERIC_FILE "generic/THStorage.c"
#else


THStorage* THStorage_(new)(void)
{
  return THStorage_(newWithSize)(0);
}

THStorage* THStorage_(newWithSize)(ptrdiff_t size)
{
  return THStorage_(newWithAllocator)(size, &THDefaultAllocator, NULL);
}

THStorage* THStorage_(newWithAllocator)(ptrdiff_t size,
                                        THAllocator *allocator,
                                        void *allocatorContext)
{
  THStorage *storage = THAlloc(sizeof(THStorage));
  storage->data = allocator->malloc(allocatorContext, sizeof(real)*size);
  storage->size = size;
  storage->refcount = 1;
  storage->flag = TH_STORAGE_REFCOUNTED | TH_STORAGE_RESIZABLE | TH_STORAGE_FREEMEM;
  storage->allocator = allocator;
  storage->allocatorContext = allocatorContext;
  return storage;
}




// THAllocator.c中有相关定义
THStorage* THStorage_(newWithData)(real *data, ptrdiff_t size)
{
  return THStorage_(newWithDataAndAllocator)(data, size,
                                             &THDefaultAllocator, NULL);
}

THStorage* THStorage_(newWithDataAndAllocator)(real* data, ptrdiff_t size,
                                               THAllocator* allocator,
                                               void* allocatorContext) {
  THStorage *storage = THAlloc(sizeof(THStorage));
  storage->data = data;
  storage->size = size;
  storage->refcount = 1;
  storage->flag = TH_STORAGE_REFCOUNTED | TH_STORAGE_RESIZABLE | TH_STORAGE_FREEMEM;
  storage->allocator = allocator;
  storage->allocatorContext = allocatorContext;
  return storage;
}


void THStorage_(resize)(THStorage *storage, ptrdiff_t size)
{
  if(storage->flag & TH_STORAGE_RESIZABLE)
  {
    if(storage->allocator->realloc == NULL) {
      /* case when the allocator does not have a realloc defined */
      real *old_data = storage->data;
      ptrdiff_t old_size = storage->size;
      if (size == 0) {
	      storage->data = NULL;
      } 
      else {
	      storage->data = storage->allocator->malloc(
						   storage->allocatorContext,
						   sizeof(real)*size);
      }
      storage->size = size;
      if (old_data != NULL) {
	ptrdiff_t copy_size = old_size;
	if (storage->size < copy_size) {
	  copy_size = storage->size;
	}
	if (copy_size > 0) {
	  memcpy(storage->data, old_data, sizeof(real)*copy_size);
	}
	storage->allocator->free(storage->allocatorContext, old_data);
      }
    } else {
      storage->data = storage->allocator->realloc(
						  storage->allocatorContext,
						  storage->data,
						  sizeof(real)*size);
      storage->size = size;
    }
  } else {
    //THError("Trying to resize storage that is not resizable");
    printf("Trying to resize storage that is not resizable");
  }
}




#endif