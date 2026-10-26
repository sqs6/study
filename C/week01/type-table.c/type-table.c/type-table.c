/* =====================================================================
 *  type-table.c  ——  C 语言基本类型信息表（Week 01 练习）
 *
 *  【知识点】
 *   1. <limits.h> 提供各整型的取值范围宏（CHAR_MIN / INT_MAX / ULLONG_MAX ...）
 *   2. sizeof 是运算符不是函数，参数不会被求值
 *   3. %zu 打印 size_t；%llu 打印 unsigned long long；%p 打印指针地址
 *   4. Windows 是 LLP64：long 只有 4 字节；Linux 是 LP64：long 有 8 字节
 *      -> 这就是「同一份代码两个平台行为不同」的经典坑，pwn 里非常常见
 *   5. 无符号整数溢出 = 回绕（有明确定义）；有符号整数溢出 = 未定义行为
 *
 *  【本版修复的 Bug】
 *      原代码：printf("... min=%llu ...", sizeof(...), 0, ULLONG_MAX);
 *              这里的 0 是 int，与 %llu 不匹配 -> MSVC warning C4477
 *      修复：  0  ->  0ULL   让实参类型与格式符严格对应
 *
 *  【本版新增】
 *      long / unsigned long / bool / wchar_t / size_t / int32_t / int64_t
 *      uint32_t / long double / 指针地址(%p) / 溢出回绕演示
 *
 *  【输出说明】
 *      输出全部使用 ASCII，避免 VS 调试窗口 / 不同代码页导致中文乱码；
 *      中文讲解放在本注释里，在 VS 里看得到即可。
 *
 *  编译：cl /nologo type-table.c
 * ===================================================================== */
#include <stdio.h>
#include <limits.h>
#include <stddef.h>   /* size_t, wchar_t */
#include <stdint.h>   /* int32_t / int64_t / uint32_t */
#include <stdbool.h>  /* bool, true, false */
#include <wchar.h>    /* wchar_t */

int main(void)
{
    printf("============ 1. Integer types: size / range ============\n");

    printf("char           : size=%zu, min=%d, max=%d\n",
           sizeof(char), CHAR_MIN, CHAR_MAX);

    printf("signed char    : size=%zu, min=%d, max=%d\n",
           sizeof(signed char), SCHAR_MIN, SCHAR_MAX);

    /* 0U 是 unsigned int，与 %u 严格匹配 */
    printf("unsigned char  : size=%zu, min=%u, max=%u\n",
           sizeof(unsigned char), 0U, (unsigned)UCHAR_MAX);

    printf("short          : size=%zu, min=%d, max=%d\n",
           sizeof(short), SHRT_MIN, SHRT_MAX);

    printf("unsigned short : size=%zu, min=%u, max=%u\n",
           sizeof(unsigned short), 0U, (unsigned)USHRT_MAX);

    printf("int            : size=%zu, min=%d, max=%d\n",
           sizeof(int), INT_MIN, INT_MAX);

    printf("unsigned int   : size=%zu, min=%u, max=%u\n",
           sizeof(unsigned int), 0U, UINT_MAX);

    /* Windows(LLP64) 的 long 是 4 字节；Linux(LP64) 的 long 是 8 字节 */
    printf("long           : size=%zu, min=%ld, max=%ld   <== Windows=4, Linux=8\n",
           sizeof(long), LONG_MIN, LONG_MAX);

    printf("unsigned long  : size=%zu, min=%lu, max=%lu\n",
           sizeof(unsigned long), 0UL, ULONG_MAX);

    printf("long long      : size=%zu, min=%lld, max=%lld\n",
           sizeof(long long), LLONG_MIN, LLONG_MAX);

    /* ★ 修复点：0 -> 0ULL，与 %llu 严格匹配（原代码会报 warning C4477） */
    printf("unsigned ll    : size=%zu, min=%llu, max=%llu\n",
           sizeof(unsigned long long), 0ULL, ULLONG_MAX);

    printf("\n============ 2. Other common types ============\n");

    printf("bool           : size=%zu, sizeof(true)=%zu\n",
           sizeof(bool), sizeof(true));

    printf("wchar_t        : size=%zu   (Windows=2, Linux=4)\n", sizeof(wchar_t));

    printf("size_t         : size=%zu   (unsigned integer)\n", sizeof(size_t));

    printf("int32_t        : size=%zu, min=%lld, max=%lld\n",
           sizeof(int32_t), (long long)INT32_MIN, (long long)INT32_MAX);
    printf("int64_t        : size=%zu, min=%lld, max=%lld\n",
           sizeof(int64_t), (long long)INT64_MIN, (long long)INT64_MAX);
    printf("uint32_t       : size=%zu, max=%llu\n",
           sizeof(uint32_t), (unsigned long long)UINT32_MAX);

    printf("float          : size=%zu\n", sizeof(float));
    printf("double         : size=%zu\n", sizeof(double));
    printf("long double    : size=%zu\n", sizeof(long double));

    printf("\n============ 3. Pointers and addresses ============\n");

    int  x = 42;
    int *p = &x;

    printf("sizeof(char*)  : size=%zu   (64-bit process = 8)\n", sizeof(char *));
    printf("sizeof(void*)  : size=%zu\n", sizeof(void *));
    printf("address of &x  : %p\n", (void *)&x);
    printf("address of  p  : %p\n", (void *)p);
    printf("value of   *p  : %d   (x=%d)\n", *p, x);

    *p = 100;
    printf("after *p=100, x = %d   <== pointer changes the original variable\n", x);

    printf("\n============ 4. Overflow and wrap-around ============\n");

    /* 无符号溢出是「回绕」，C 标准有明确定义，不会崩 */
    unsigned char uc = 255;
    uc = uc + 1;                    /* 先提升为 int 运算，再截断回 unsigned char */
    printf("unsigned char 255 + 1 = %u   (wrap-around, defined)\n", (unsigned)uc);

    unsigned int u = UINT_MAX;
    u = u + 1;
    printf("unsigned int UINT_MAX + 1 = %u   (wrap-around to 0)\n", u);

    /* 有符号整数溢出是「未定义行为」：编译器可假定它不发生。
     * 写漏洞利用代码时，栈上的有符号长度/计数字段被改写就是这类问题。 */
    printf("int INT_MAX + 1 : signed overflow = undefined behavior\n");
    printf("                -> parse network length fields with UNSIGNED types\n");

    printf("\n============ 5. Conclusion ============\n");
    printf("Windows x64 (LLP64): int=4, long=4, long long=8, pointer=8\n");
    printf("Linux   x64 (LP64): int=4, long=8, long long=8, pointer=8\n");
    printf("-> for fixed-width integers use int32_t / int64_t / uint64_t\n");

    return 0;
}
