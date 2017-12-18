#ifndef TH_GENERAL_INC
#define TH_GENERAL_INC

//#define DEBUG  
// gcc -E TH.h > a.h 可以看到所有的函数声明，为了不包含下面这些系统头文件
// 设置了一个 DEBUG 宏来控制

#ifndef DEBUG

#include <stdint.h> // real int64_t 要用
#include <stddef.h> // ptrdiff_t 要用
#include <malloc.h> // THGeneral.c 的内存管理部分要用

#endif


#define TH_CONCAT_2(x,y) TH_CONCAT_2_EXPAND(x,y)
#define TH_CONCAT_2_EXPAND(x,y) x ## y

#define TH_CONCAT_3(x,y,z) TH_CONCAT_3_EXPAND(x,y,z)
#define TH_CONCAT_3_EXPAND(x,y,z) x ## y ## z

#define TH_CONCAT_4_EXPAND(x,y,z,w) x ## y ## z ## w
#define TH_CONCAT_4(x,y,z,w) TH_CONCAT_4_EXPAND(x,y,z,w)

#endif 