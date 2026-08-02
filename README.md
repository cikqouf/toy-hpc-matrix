用到的第三方库: google benchmark: [https://github.com/google/benchmark]

一个非常简单的高性能 gemm cpp 实现

用法: 

```cpp
#define MAT_THREAD_NUMS 1
#include "mat.hpp"
```

然后直接写 `mat<float> c = a * b;` 就行.

还有就是本项目不支持跨平台, 且 Windows x64 带 avx2 的处理器才能用.

理论上也需要 Windows 7 之后的系统.
