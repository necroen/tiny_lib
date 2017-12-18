# <p align="center">tiny_lib</p>
用 C 实现泛型的例子在这： https://github.com/necroen/generic_in_c  
linux内核中似乎很多这种generic的写法。

这个 tiny_lib 本意是模仿 pytorch 下的一些底层库，只是为了学习和演示用，剪切掉了不少功能。有时间的话会一直断断续续更新。  

TH:  
1，先实现一个THStorage，用数组初始化这个THStorage对象。  
2，再实现THTensor，再用上面的THStorage初始化这个THTensor，  
3，再实现一个THTensor的数学运算，主要是为了搞懂THTensor数学运算相关的TH_TENSOR_APPLY开头的宏，最后实现了调用TH_TENSOR\_APPLY2宏的 THTensor_(add) 函数以及 调用 TH_TENSOR\_APPLY 宏的 THTensor\_(nonzeroNum) 函数。

类型只实现了 int 和 double 类型，只是为了展示能够用C实现泛型

THStorage下面本来的内存管理功能被我简化成了调用系统函数。

有两个测试的例子：main.c 和 APPLY2_main.c(放在doc中)

几篇我写的关于 TH 的流水账博客：  
http://www.cnblogs.com/shepherd2015/p/7730277.html  
http://www.cnblogs.com/shepherd2015/p/7876120.html  
http://www.cnblogs.com/shepherd2015/p/8019404.html  
另一个重要的参考资料：  
https://github.com/torch/torch7/tree/master/doc  

THStorage 和 THTensor 实现都是在TH/generic中，然后在TH/下的同名文件中膨胀。

要看到所有的声明，可以开启 THGeneral.h 中的 DEBUG 宏，防止包含系统头文件。  
然后 gcc -E TH.h > declaration.h 就可以在 declaration.h 看到函数声明。  

TH_TENSOR\_APPLY开头的宏 不容易看懂，也可以预编译展开 TH 下的 THTensor.c 文件。  
doc中有个 THTensor_(add) 按 int 类型展开的例子。  

在 win7 下用的 mingw + cmake + vscode(用了几个vscode中的cmake插件)[编译](http://www.cnblogs.com/shepherd2015/p/7874386.html)。
或者直接切换到 main.c 所在文件夹运行  
**gcc main.c ./TH/*.c -o demo -w**  
