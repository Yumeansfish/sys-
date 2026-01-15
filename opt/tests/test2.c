// Test 2: Counter file persistence
// Verify that counter file is created and updated correctly across multiple encryptions

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

int read_counter(const char* filename) {
    FILE* f = fopen(filename, "r");
    int counter = -1;
    if (f) {
        fscanf(f, "%d", &counter);
        fclose(f);
    }
    return counter;
}

int main() {
    printf("=== Test 2: Counter File Persistence ===\n\n");

    // Create a large key file
    FILE* f = fopen("test2_key", "wb");
    for (int i = 0; i < 1000; i++) {
        unsigned char c = (unsigned char)(i % 256);
        fwrite(&c, 1, 1, f);
    }
    fclose(f);

    // Remove counter file if exists
    remove("test2_key.counter");

    // First encryption: 5 bytes
    f = fopen("test2_msg1.txt", "w");
    fprintf(f, "AAAAA");  // 5 bytes
    fclose(f);

    system("./otp in=test2_msg1.txt out=test2_enc1 key=test2_key");

    int counter1 = read_counter("test2_key.counter");
    int ok1 = (counter1 == 5);
    print_result("Counter after first encryption (5 bytes)", 5, counter1, ok1);

    // Second encryption: 10 bytes
    f = fopen("test2_msg2.txt", "w");
    fprintf(f, "BBBBBBBBBB");  // 10 bytes
    fclose(f);

    system("./otp in=test2_msg2.txt out=test2_enc2 key=test2_key");

    int counter2 = read_counter("test2_key.counter");
    int ok2 = (counter2 == 15);  // 5 + 10
    print_result("Counter after second encryption (5+10 bytes)", 15, counter2, ok2);

    // Third encryption: 7 bytes
    f = fopen("test2_msg3.txt", "w");
    fprintf(f, "CCCCCCC");  // 7 bytes
    fclose(f);

    system("./otp in=test2_msg3.txt out=test2_enc3 key=test2_key");

    int counter3 = read_counter("test2_key.counter");
    int ok3 = (counter3 == 22);  // 5 + 10 + 7
    print_result("Counter after third encryption (5+10+7 bytes)", 22, counter3, ok3);

    // Cleanup
    remove("test2_key");
    remove("test2_key.counter");
    remove("test2_msg1.txt");
    remove("test2_msg2.txt");
    remove("test2_msg3.txt");
    remove("test2_enc1");
    remove("test2_enc2");
    remove("test2_enc3");

    assert(ok1 && "Counter should be 5 after first encryption");
    assert(ok2 && "Counter should be 15 after second encryption");
    assert(ok3 && "Counter should be 22 after third encryption");

    printf("=== Test 2 PASSED ===\n");
    return 0;
}
