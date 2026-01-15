// Test 6: Empty file handling
// Verify that the program handles empty input files correctly

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void print_result(const char* test_name, int expected, int actual, int passed) {
    printf("Test: %s\n", test_name);
    printf("  Expected: %d\n", expected);
    printf("  Actual:   %d\n", actual);
    printf("  Result:   %s\n\n", passed ? "PASSED" : "FAILED");
}

long get_file_size(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) return -1;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    return size;
}

int main() {
    printf("=== Test 6: Empty File Handling ===\n\n");

    // Create empty input file
    FILE* f = fopen("test6_input", "w");
    fclose(f);

    // Create key file
    f = fopen("test6_key", "wb");
    unsigned char key[] = {0x12, 0x34, 0x56};
    fwrite(key, 1, sizeof(key), f);
    fclose(f);

    remove("test6_key.counter");

    system("./otp in=test6_input out=test6_output key=test6_key");

    // Output file should exist and be empty
    long output_size = get_file_size("test6_output");
    int ok1 = (output_size == 0);
    print_result("Output file size for empty input", 0, (int)output_size, ok1);

    // Counter should be 0 or file should indicate 0 bytes used
    f = fopen("test6_key.counter", "r");
    int counter = -1;
    if (f) {
        fscanf(f, "%d", &counter);
        fclose(f);
    }

    int ok2 = (counter == 0 || counter == -1);  // Either 0 or no counter file created
    printf("Test: Counter for empty input\n");
    printf("  Expected: 0 (or no counter file)\n");
    printf("  Actual:   %d\n", counter);
    printf("  Result:   %s\n\n", ok2 ? "PASSED" : "FAILED");

    // Cleanup
    remove("test6_input");
    remove("test6_key");
    remove("test6_key.counter");
    remove("test6_output");

    assert(ok1 && "Output file should be empty for empty input");

    printf("=== Test 6 PASSED ===\n");
    return 0;
}
