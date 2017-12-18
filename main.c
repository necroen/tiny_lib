// 2017年12月16日18:22:59
#include "TH/TH.h"

#include <stdio.h>

int main(){
	// 测试Storage相关函数
	int a[12];
	for(int i=0; i<12; i++)
		a[i] = i+1;

	THIntStorage* x = THIntStorage_newWithData(&a, 12);

	// 测试Tensor相关函数  
	// doc: 对pytorch中Tensor的剖析
	// http://www.cnblogs.com/shepherd2015/p/8019404.html
	int sz[2] 		= {3,4};
	int stride[2] 	= {4,1}; 

	THIntStorage* tensor_size =  THIntStorage_newWithData(&sz, 2);
	THIntStorage* tensor_stride =  THIntStorage_newWithData(&stride, 2);

	THIntTensor * tensor_x = THIntTensor_newWithStorage(x, // THIntStorage *storage
														0, // ptrdiff_t storageOffset,
														tensor_size, // THIntStorage *size,
														tensor_stride); // THIntStorage *stride

	int isContiguous = THIntTensor_isContiguous(tensor_x);
	printf("tensor_x isContiguous: %d\n", isContiguous);

	// 测试 THTensor_(add) 函数中的 TH_TENSOR_APPLY2 宏
	// void THTensor_(add)(THTensor *r_, THTensor *t, real value)

	// 先生成一个内存上不连续的 Tensor ，从 3x4 中截取一个 3x3 出来
	int aa[12];
	for(int i=0; i<12; i++)
		aa[i] = i+1;
	THIntStorage* xx = THIntStorage_newWithData(&aa, 12);

	int bb[12];
	for(int i=0; i<12; i++)
		bb[i] = 0;
	THIntStorage* yy = THIntStorage_newWithData(&bb, 12);

	int sz1[2] 		= {3,3};
	int stride1[2] 	= {4,1};

	THIntStorage* tensor_size1 =  THIntStorage_newWithData(&sz1, 2);
	THIntStorage* tensor_stride1 =  THIntStorage_newWithData(&stride1, 2);

	THIntTensor* tensor_xx = THIntTensor_newWithStorage(xx,0,tensor_size1,tensor_stride1);
	THIntTensor* tensor_yy = THIntTensor_newWithStorage(yy,0,tensor_size1,tensor_stride1);
	THIntTensor_add(tensor_yy, tensor_xx, 6);

	int* data = tensor_yy->storage->data+tensor_yy->storageOffset;
	for(int i=0; i<12; i++)
		printf("%d\t", *(data+i));
	printf("\n");

    printf("press Enter to exit...\n");
	getchar();
	return 0;
}
// 从3x4的矩阵
// [1	2	3	4
//  5	6	7	8
//  9	10	11	12] 
// 截取出 3x3 大小，得到 tensor_xx = 
// [1	2	3
//  5	6	7
//  9	10	11]
// 其在内存上是不连续的。

// tensor_yy为 从 3x4 的0矩阵中截取的 3x3 的0矩阵, tensor_xx各元素加 6 后得到 tensor_yy
// 因此最后打印的结果为 :
// 7       8       9       0       11      12      13      0       15      16      17      0