// Test 4: XOR correctness
// Verify that the XOR operation produces correct results

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
    printf("=== Test 4: XOR Correctness ===\n\n");

    // Input: 0x41 ('A')
    // Key:   0xFF
    // Expected output: 0x41 ^ 0xFF = 0xBE

    FILE* f = fopen("test4_input", "wb");
    unsigned char input = 0x41;  // 'A'
    fwrite(&input, 1, 1, f);
    fclose(f);

    f = fopen("test4_key", "wb");
    unsigned char key = 0xFF;
    fwrite(&key, 1, 1, f);
    fclose(f);

    remove("test4_key.counter");

    system("./otp in=test4_input out=test4_output key=test4_key");

    f = fopen("test4_output", "rb");
    unsigned char output = 0;
    if (f) {
        fread(&output, 1, 1, f);
        fclose(f);
    }

    unsigned char expected = 0x41 ^ 0xFF;  // 0xBE
    int ok1 = (output == expected);
    print_result_hex("Single byte XOR (0x41 ^ 0xFF)", expected, output, ok1);

    // Test 2: Multiple bytes
    // Input: "ABC" (0x41, 0x42, 0x43)
    // Key:   0x00, 0xFF, 0x0F
    // Expected: 0x41^0x00=0x41, 0x42^0xFF=0xBD, 0x43^0x0F=0x4C

    f = fopen("test4_input2", "wb");
    unsigned char input2[] = {0x41, 0x42, 0x43};
    fwrite(input2, 1, 3, f);
    fclose(f);

    f = fopen("test4_key2", "wb");
    unsigned char key2[] = {0x00, 0xFF, 0x0F};
    fwrite(key2, 1, 3, f);
    fclose(f);

    remove("test4_key2.counter");

    system("./otp in=test4_input2 out=test4_output2 key=test4_key2");

    f = fopen("test4_output2", "rb");
    unsigned char output2[3] = {0};
    if (f) {
        fread(output2, 1, 3, f);
        fclose(f);
    }

    unsigned char expected2[] = {0x41, 0xBD, 0x4C};
    int ok2 = (output2[0] == expected2[0]);
    int ok3 = (output2[1] == expected2[1]);
    int ok4 = (output2[2] == expected2[2]);

    print_result_hex("Multi-byte XOR byte 0 (0x41 ^ 0x00)", expected2[0], output2[0], ok2);
    print_result_hex("Multi-byte XOR byte 1 (0x42 ^ 0xFF)", expected2[1], output2[1], ok3);
    print_result_hex("Multi-byte XOR byte 2 (0x43 ^ 0x0F)", expected2[2], output2[2], ok4);

    // Cleanup
    remove("test4_input");
    remove("test4_input2");
    remove("test4_key");
    remove("test4_key2");
    remove("test4_key.counter");
    remove("test4_key2.counter");
    remove("test4_output");
    remove("test4_output2");

    assert(ok1 && "Single byte XOR should be correct");
    assert(ok2 && ok3 && ok4 && "Multi-byte XOR should be correct");

    printf("=== Test 4 PASSED ===\n");
    return 0;
}
