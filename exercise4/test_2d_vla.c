#include <stdio.h>
#include <string.h>

void test_2d_vla(int k) {
    char buffer[k][1000];  // 2D VLA
    
    printf("Successfully declared char buffer[%d][1000]\n", k);
    
    for(int i = 0; i < k; i++) {
        snprintf(buffer[i], 1000, "Line %d", i);
    }
    
    for(int i = 0; i < k; i++) {
        printf("%s\n", buffer[i]);
    }
}

int main() {
    test_2d_vla(5);
    return 0;
}
