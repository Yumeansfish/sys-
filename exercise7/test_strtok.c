#include <string.h>
#include <stdio.h>

int main() {
    char str[] = "ab,cd,,";
    printf("Testing: \"%s\"\n\n", str);

    char* token = strtok(str, ",");
    int count = 0;
    while(token != NULL) {
        printf("Token %d: \"%s\"\n", ++count, token);
        token = strtok(NULL, ",");
    }
    printf("\nTotal tokens: %d\n", count);
    return 0;
}
