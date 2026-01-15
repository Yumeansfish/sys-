// Test 3: Default key file name
// Verify that default key file "key" is used when key= option is not provided

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void print_result(const char* test_name, const char* expected, const char* actual, int passed) {
    printf("Test: %s\n", test_name);
    printf("  Expected: %s\n", expected);
    printf("  Actual:   %s\n", actual);
    printf("  Result:   %s\n\n", passed ? "PASSED" : "FAILED");
}

int main() {
    printf("=== Test 3: Default Key File ===\n\n");

    // Create default key file named "key"
    FILE* f = fopen("key", "wb");
    unsigned char keydata[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
    fwrite(keydata, 1, sizeof(keydata), f);
    fclose(f);

    // Remove counter file if exists
    remove("key.counter");

    // Create input file
    f = fopen("test3_input.txt", "w");
    fprintf(f, "Test!");  // 5 bytes
    fclose(f);

    // Encrypt without specifying key (should use default "key")
    system("./otp in=test3_input.txt out=test3_output");

    // Check if key.counter was created
    int counter_exists = 0;
    f = fopen("key.counter", "r");
    if (f) {
        counter_exists = 1;
        int counter;
        fscanf(f, "%d", &counter);
        fclose(f);

        char expected[32], actual[32];
        sprintf(expected, "5");
        sprintf(actual, "%d", counter);
        print_result("Counter value in key.counter", expected, actual, counter == 5);
    }

    print_result("Default key.counter file created", "exists", counter_exists ? "exists" : "not found", counter_exists);

    // Cleanup
    remove("key");
    remove("key.counter");
    remove("test3_input.txt");
    remove("test3_output");

    assert(counter_exists && "key.counter should be created when using default key");

    printf("=== Test 3 PASSED ===\n");
    return 0;
}
