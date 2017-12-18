// 专门测试 TH_TENSOR_APPLY2_D 宏，搞清其中一些变量的含义

#include "TH/TH.h"

#include <stdio.h>

int main(){
    // 新建一个 array[2][3][4][5][6] 的数组
    // stride = {360,120, 30, 6, 1}
    // size   = {  2,  3,  4, 5, 6}  共计 720 个元素
    int array[720];
	for(int i=0; i<720; i++)
		array[i] = i+1;
    array[0] = 0;
    
    printf("&array[-1] = %d\n",&array[-1]);
    
    THIntStorage* x = THIntStorage_newWithData(&array, 720);

	int stride[5] 	= {360,120, 30, 6, 1}; 
    int size[5] 	= {  2,  3,  4, 4, 6}; // 任意改变这里某些数字，让其比原来的值小点。看运行结果
    //                {  2,  3,  4,|5, 6}
    // 改变size中的1个数字算切1刀， 分成 2 段，则 TENSOR##_dim = 2
    // 改变2个算切2刀， TENSOR##_dim = 3， 以此类推
    // TENSOR##_size 是变完以后的数右边相乘  循环 sizeof(A) 次
    // 比如上面5改成了4，4以及4右边的数字连乘得到 TENSOR##_size

	THIntStorage* tensor_size =  THIntStorage_newWithData(&size, 5);
	THIntStorage* tensor_stride =  THIntStorage_newWithData(&stride, 5);

	THIntTensor * tensor_x = THIntTensor_newWithStorage(x, 0, 
														tensor_size, 
														tensor_stride);
    
	printf("tensor_x isContiguous: %d\n", THIntTensor_isContiguous(tensor_x) );

    printf("tensor_x nonzeroNum: %d\n", THIntTensor_nonzeroNum(tensor_x) );
    
    printf("press Enter to exit...\n");
	getchar();
	return 0;
}