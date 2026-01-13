#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "hello";
    char* p = str + strlen(str);  // 指向 '\0'

    printf("*p (at \\0): %d\n", *p);           // 合法，输出 0

    char* q = p + 1;                           // one past the end
    printf("Dereferencing one past end...\n");
    printf("*q: %d\n", *q);                    // UB! 但可能运行

    // 模拟你的while循环
    char* format = q;
    printf("\nSimulating while(*format):\n");
    if (*format) {  // UB!
        printf("*format is non-zero: %d\n", *format);
    } else {
        printf("*format is zero (lucky!)\n");
    }

    return 0;
}
