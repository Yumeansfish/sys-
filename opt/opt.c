#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Exercise 21. (60') Write a program called otp to encrypt files using a one-time pad. A one-time
// pad is an extremely simple and also very secure encryption scheme that works as follows: each
// byte xi of the cleartext file (input) produces a byte yi = xi ⊕ ki in the ciphertext file (output) using
// one byte ki of the key, where ⊕ is the xor operator.
// A one-time pad is such that a key byte is used only once. This means that you need large keys, and
// that you need to remember which bytes you used of those keys. So, your encryption program must
// use a key file f , plus an auxiliary file named f .counter that stores the number of bytes already
// used in f .
// The otp program must accept the following optional command-line options:
// • in=input-file defines the input cleartext file. By default, the program must read the cleartext
// file from the standard input (stdin).
// • out=output-file defines the output ciphertext file. By default, the program must write the
// cleartext file onto the standard output (stdout).
// • key=key-file defines the output ciphertext file. By default, the program must use a key file
// called key. This also determines the name of the counter file to associate with a particular
// key file. The name of the counter file is then key-file.counter. If a counter file does not yet
// exist, the counter is assumed to be 0.
// For example, imagine that you and your friend share a large secret key (say 10MB) that you store
// in a file called secretkey. This is the first time you use this key file, and you start by encrypting a
// message with the following command:
// ./otp in=private_message1.txt out=encrypted_message1 key=secretkey!
// This creates a file called encrypted_message1 and also a file called secretkey.couter that contains
// the number n of characters used from the beginning of the key file, which is also exactly the
// number of characters in private_message1.txt and in encrypted_message1. The number n is stored
// in the counter file in decimal characters.
// Then you use again the same key file to encrypt another message:
// ./otp in=message2.txt out=message2 key=secretkey!
// This second command reads the number from the counter file, and then starts encrypting the
// second message with the (n + 1)-th character in the key file, and then updates the counter file.
// Hint: in your implementation, you might want to use the following functions from the standard
// library: fopen, fread, fwrite, fseek, and of course fprintf, etc. Notice that you can open the key
// counter file in read/write mode ("r+"), and after reading the current counter you can use rewind to
// go back to the beginning of that file to write the new value of the counter.


void encode(char* in, char* ke, char* out)
{
    // 打开输出文件
    FILE* output = NULL;
    if (!out) output = stdout;
    else output = fopen(out, "wb");

    // 打开输入文件
    FILE* input = NULL;
    if (!in) input = stdin;
    else input = fopen(in, "rb");

    // 读取输入到buffer
    unsigned char input_buffer[5000];
    size_t input_size = fread(input_buffer, 1, sizeof(input_buffer), input);

    // 确定key文件名
    const char* key_name = ke ? ke : "key";

    // 打开key文件
    FILE* key = fopen(key_name, "rb");

    // 读取counter文件
    char counter_filename[256];
    sprintf(counter_filename, "%s.counter", key_name);
    int counter = 0;
    FILE* counter_file = fopen(counter_filename, "r");
    if (counter_file) {
        fscanf(counter_file, "%d", &counter);
        fclose(counter_file);
    }

    // 跳过已经用过的key字节
    fseek(key, counter, SEEK_SET);

    // 读取key到buffer
    unsigned char key_buffer[5000];
    size_t key_size = fread(key_buffer, 1, sizeof(key_buffer), key);

    // XOR加密
    for (size_t i = 0; i < input_size && i < key_size; i++) {
        unsigned char res = input_buffer[i] ^ key_buffer[i];
        fwrite(&res, 1, 1, output);
    }

    // 更新counter文件
    counter_file = fopen(counter_filename, "w");
    fprintf(counter_file, "%d", counter + (int)input_size);
    fclose(counter_file);

    // 关闭文件
    if (in) fclose(input);
    if (out) fclose(output);
    fclose(key);
}






int main(int argc, char* argv[])
{
    char* input = NULL;
    char* output = NULL;
    char* key = NULL;

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "in=", 3) == 0) {
            input = argv[i] + 3;
        } else if (strncmp(argv[i], "out=", 4) == 0) {
            output = argv[i] + 4;
        } else if (strncmp(argv[i], "key=", 4) == 0) {
            key = argv[i] + 4;
        }
    }

    encode(input, key, output);
    return 0;
}