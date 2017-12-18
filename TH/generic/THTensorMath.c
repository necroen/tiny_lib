#ifndef GENERIC_FILE
    #define GENERIC_FILE "generic/THTensorMath.c"
#else

// 为了测试 TH_TENSOR_APPLY2 宏，默认 r_ 和 t 内存上不连续
void THTensor_(add)(THTensor *r_, THTensor *t, real value)
{
  THTensor_(resizeAs)(r_, t); // 将 r_ 的尺寸调整成和 t 一样
//   if (THTensor_(isContiguous)(r_) && THTensor_(isContiguous)(t) && THTensor_(nElement)(r_) == THTensor_(nElement)(t)) {
//     TH_TENSOR_APPLY2_CONTIG(real, r_, real, t, THVector_(adds)(r__data, t_data, value, r__len););
//   } 
//   else {
    TH_TENSOR_APPLY2(real, r_, real, t, *r__data = *t_data + value;);
//   }
}

// 改造了一下 THTensor_(nonzero) 函数， 只统计非零元素数目
int THTensor_(nonzeroNum)(THTensor *tensor)
{
    ptrdiff_t numel = 0;
  
    #define IS_NONZERO(val) ((val)!=0)

    /* First Pass to determine size of subscripts */
    TH_TENSOR_APPLY(real, tensor,
                    if IS_NONZERO(*tensor_data) {
                        ++numel;
                    }
                    );

    return numel;
}


#endif