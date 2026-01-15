// Test 5: Key offset (using counter)
// Verify that encryption starts from the correct offset in the key file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void print_result_hex(const char* test_name, unsigned char expected, unsigned char actual, int passed) {
    printf("Test: %s\n", test_name);
    printf("  Expected: 0x%02X\n", expected);
    printf("  Actual:   0x%02X\n", actual);
    printf("  Result:   %s\n\n", passed ? "PASSED" : "FAILED");
}

int main() {
    printf("=== Test 5: Key Offset Using Counter ===\n\n");

    // Key file: 0x00, 0x11, 0x22, 0x33, 0x44
    // If counter starts at 2, encryption should use bytes starting from index 2

    FILE* f = fopen("test5_key", "wb");
    unsigned char key[] = {0x00, 0x11, 0x22, 0x33, 0x44};
    fwrite(key, 1, sizeof(key), f);
    fclose(f);

    // Set counter to 2 (skip first 2 bytes of key)
    f = fopen("test5_key.counter", "w");
    fprintf(f, "2");
    fclose(f);

    // Input: 'A' (0x41)
    // Key byte at offset 2: 0x22
    // Expected: 0x41 ^ 0x22 = 0x63

    f = fopen("test5_input", "wb");
    unsigned char input = 0x41;
    fwrite(&input, 1, 1, f);
    fclose(f);

    system("./otp in=test5_input out=test5_output key=test5_key");

    f = fopen("test5_output", "rb");
    unsigned char output = 0;
    if (f) {
        fread(&output, 1, 1, f);
        fclose(f);
    }

    unsigned char expected = 0x41 ^ 0x22;  // 0x63
    int ok1 = (output == expected);
    print_result_hex("Encryption with offset=2 (0x41 ^ 0x22)", expected, output, ok1);

    // Verify counter is now 3
    f = fopen("test5_key.counter", "r");
    int counter = 0;
    if (f) {
        fscanf(f, "%d", &counter);
        fclose(f);
    }

    printf("Test: Counter updated correctly\n");
    printf("  Expected: 3\n");
    printf("  Actual:   %d\n", counter);
    printf("  Result:   %s\n\n", counter == 3 ? "PASSED" : "FAILED");
    int ok2 = (counter == 3);

    // Cleanup
    remove("test5_key");
    remove("test5_key.counter");
    remove("test5_input");
    remove("test5_output");

    assert(ok1 && "Encryption should use correct key offset");
    assert(ok2 && "Counter should be updated to 3");

    printf("=== Test 5 PASSED ===\n");
    return 0;
}
