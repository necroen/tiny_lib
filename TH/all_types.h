// all_types.h需要注意一下宏结构，不然 THStorage.h 
// 和 THStorage.c 中的声明和定义会干涉。 不能同时膨胀
// 展开TH.h时会出现：有声明但是找不到定义(不能编译出exe来)，或者无声明但是有定义(会警告)。

// ver1=============================
// #ifndef all_types_h
// #define all_types_h

// 	#include "double_type.h"
// 	#include "int_type.h"

// 	#undef GENERIC_FILE

// #endif
// ver1  end =======================

// ver2=============================
#ifndef THGenerateManyTypes
	#define THAllLocalGenerateManyTypes // 1
	#define THGenerateManyTypes         // 1
#endif

#include "double_type.h"
#include "int_type.h"

#ifdef THAllLocalGenerateManyTypes
	#undef THAllLocalGenerateManyTypes  // 0
	#undef THGenerateManyTypes          // 0
	#undef GENERIC_FILE     // all_types的最后一行出现在这，这一句一定要，不能删
#endif