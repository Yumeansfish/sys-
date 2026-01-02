#include <stdio.h>
#include <stdlib.h>

void test_vla(int k) {
    char* buffer[k];  // VLA (Variable Length Array)
    
    printf("Successfully declared char* buffer[%d]\n", k);
    
    for(int i = 0; i < k; i++) {
        buffer[i] = malloc(100);
        if(buffer[i]) {
            sprintf(buffer[i], "Line %d", i);
        }
    }
    
    for(int i = 0; i < k; i++) {
        printf("%s\n", buffer[i]);
        free(buffer[i]);
    }
}

int main() {
    test_vla(5);
    return 0;
}
