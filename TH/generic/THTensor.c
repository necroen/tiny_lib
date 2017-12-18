#ifndef GENERIC_FILE
    #define GENERIC_FILE "generic/THTensor.c"
#else

static void THTensor_(rawInit)(THTensor *self)
{
  self->refcount = 1;
  self->storage = NULL;
  self->storageOffset = 0;  // 默认是 0
  self->size = NULL;
  self->stride = NULL;
  self->nDimension = 0;
  self->flag = TH_TENSOR_REFCOUNTED;
}

/* Storage init */
THTensor *THTensor_(newWithStorage)(THStorage *storage, 
                                    ptrdiff_t storageOffset, 
                                    THIntStorage *size, 
                                    THIntStorage *stride)
{
  THTensor *self = THAlloc(sizeof(THTensor));
//   if(size && stride)
//     THArgCheck(size->size == stride->size, 4, "inconsistent size");
  THTensor_(rawInit)(self); // 
  THTensor_(setStorageNd)(self,
                          storage,
                          storageOffset,
                          (size ? size->size : (stride ? stride->size : 0)), // nDimension
                          (size ? size->data : NULL),      // *size
                          (stride ? stride->data : NULL)); // *stride

  return self;
}


//===========================
void THTensor_(setStorageNd)(THTensor *self, 
                              THStorage *storage, 
                              ptrdiff_t storageOffset, 
                              int nDimension, int *size, int *stride)
{
  /* storage */
  if(self->storage != storage) 
  {
    // if(self->storage)  // 如果 Tensor 的storage 不为空，则释放
    //   THStorage_(free)(self->storage);    

    if(storage)
    {
      self->storage = storage;
      //THStorage_(retain)(self->storage);  //
    }
    else
      self->storage = NULL;
  }

  /* storageOffset */
  if(storageOffset < 0)
    //THError("Tensor: invalid storage offset");
    printf("Tensor: invalid storage offset");
  self->storageOffset = storageOffset;

  /* size and stride */
  THTensor_(resizeNd)(self, nDimension, size, stride); // 
}

// =====================================
void THTensor_(resizeNd)(THTensor *self, 
                          int nDimension, 
                          int *size, 
                          int *stride)
{
  int d;
  int nDimension_;
  ptrdiff_t totalSize;
  int hascorrectsize = 1;

  nDimension_ = 0;
  for(d = 0; d < nDimension; d++)
  {
    if(size[d] > 0)
    {
      nDimension_++;
      if((self->nDimension > d) && (size[d] != self->size[d]))
        hascorrectsize = 0;

      if((self->nDimension > d) && stride && (stride[d] >= 0) && (stride[d] != self->stride[d]))
        hascorrectsize = 0;
    }
    else
      break;
  }
  nDimension = nDimension_;

  if(nDimension != self->nDimension)
    hascorrectsize = 0;

  if(hascorrectsize)
    return;

  if(nDimension > 0)
  {
    if(nDimension != self->nDimension)
    {
      self->size = THRealloc(self->size, sizeof(int)*nDimension);
      self->stride = THRealloc(self->stride, sizeof(int)*nDimension);
      self->nDimension = nDimension;
    }

    totalSize = 1;
    for(d = self->nDimension-1; d >= 0; d--)
    {
      self->size[d] = size[d];
      if(stride && (stride[d] >= 0) )
        self->stride[d] = stride[d];
      else
      {
        if(d == self->nDimension-1)
          self->stride[d] = 1;
        else
          self->stride[d] = self->size[d+1]*self->stride[d+1];
      }
      totalSize += (self->size[d]-1)*self->stride[d];
    }

    if(totalSize+self->storageOffset > 0)
    {
      if(!self->storage)
        self->storage = THStorage_(new)();  // 
      if(totalSize+self->storageOffset > self->storage->size)
        THStorage_(resize)(self->storage, totalSize+self->storageOffset);  // 
    }
  }
  else
    self->nDimension = 0;
}

int THTensor_(isContiguous)(const THTensor *self)
{
  int64_t z = 1;
  int d;
  for(d = self->nDimension-1; d >= 0; d--)
  {
    if(self->size[d] != 1)
    {
      if(self->stride[d] == z)
        z *= self->size[d];
      else
        return 0;
    }
  }
  return 1;
}

void THTensor_(resizeAs)(THTensor *self, THTensor *src)
{
  if(!THTensor_(isSameSizeAs)(self, src))
    THTensor_(resizeNd)(self, src->nDimension, src->size, NULL);
}

int THTensor_(isSameSizeAs)(const THTensor *self, const THTensor* src)
{
  int d;
  if (self->nDimension != src->nDimension)
    return 0;
  for(d = 0; d < self->nDimension; ++d)
  {
    if(self->size[d] != src->size[d])
      return 0;
  }
  return 1;
}




#endif