// Test 1: Basic XOR encryption/decryption
// Verify that encrypting then decrypting returns original text

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
    printf("=== Test 1: Basic XOR Encryption/Decryption ===\n\n");

    // Create test input file
    FILE* f = fopen("test1_input.txt", "w");
    fprintf(f, "Hello World!");
    fclose(f);

    // Create key file (must be at least as long as input)
    f = fopen("test1_key", "wb");
    unsigned char key[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0, 0x11, 0x22, 0x33, 0x44};
    fwrite(key, 1, sizeof(key), f);
    fclose(f);

    // Remove counter file if exists
    remove("test1_key.counter");

    // Encrypt
    int ret = system("./otp in=test1_input.txt out=test1_encrypted key=test1_key");

    // Check counter file exists and has correct value
    f = fopen("test1_key.counter", "r");
    int counter = 0;
    if (f) {
        fscanf(f, "%d", &counter);
        fclose(f);
    }

    char expected_counter[32], actual_counter[32];
    sprintf(expected_counter, "12");
    sprintf(actual_counter, "%d", counter);
    int counter_ok = (counter == 12);
    print_result("Counter after encryption", expected_counter, actual_counter, counter_ok);

    // Decrypt (XOR is symmetric, so we encrypt again with same key starting from 0)
    // Reset counter to 0
    f = fopen("test1_key.counter", "w");
    fprintf(f, "0");
    fclose(f);

    system("./otp in=test1_encrypted out=test1_decrypted key=test1_key");

    // Read decrypted content
    f = fopen("test1_decrypted", "r");
    char decrypted[100] = {0};
    if (f) {
        fread(decrypted, 1, sizeof(decrypted)-1, f);
        fclose(f);
    }

    int decrypt_ok = (strcmp(decrypted, "Hello World!") == 0);
    print_result("Decrypted content matches original", "Hello World!", decrypted, decrypt_ok);

    // Cleanup
    remove("test1_input.txt");
    remove("test1_key");
    remove("test1_key.counter");
    remove("test1_encrypted");
    remove("test1_decrypted");

    assert(counter_ok && "Counter should be 12 after encrypting 12 bytes");
    assert(decrypt_ok && "Decrypted content should match original");

    printf("=== Test 1 PASSED ===\n");
    return 0;
}
