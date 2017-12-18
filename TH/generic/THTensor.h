#ifndef GENERIC_FILE
	#define GENERIC_FILE "generic/THTensor.h"
#else

#define TH_TENSOR_REFCOUNTED 1

typedef struct THTensor
{
    int *size;
    int *stride;
    int nDimension;

    // Note: storage->size may be greater than the recorded size of a tensor
    THStorage *storage;
    ptrdiff_t storageOffset;
    int refcount;
    char flag;
} THTensor;

THTensor *THTensor_(newWithStorage)(THStorage *storage, 
                                    ptrdiff_t storageOffset, 
                                    THIntStorage *size, 
                                    THIntStorage *stride);

void THTensor_(setStorageNd)(THTensor *self, 
                              THStorage *storage, 
                              ptrdiff_t storageOffset, 
                              int nDimension, int *size, int *stride);

void THTensor_(resizeNd)(THTensor *self, 
                          int nDimension, 
                          int *size, 
                          int *stride);

int THTensor_(isContiguous)(const THTensor *self);

void THTensor_(resizeAs)(THTensor *self, THTensor *src);
int THTensor_(isSameSizeAs)(const THTensor *self, const THTensor* src);

#endif