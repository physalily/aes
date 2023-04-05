#include <stdio.h>

// prototype declare
int* AddRoundKey(int*, int*);
int* InvMixColumns(int*);
int* InvShiftRows(int*);
int* InvSubBytes(int*, int*);

int main(char argc, char** argv)
{
    // variables
    int plain_text[16] = {0};
    int crypt_key[16] = {0};
    int sbox_matrix[16][16] = {0};

    // function call
    printf("hello aes\n");

    return 0;
}

int* AddRoundKey(int* text, int* key)
{
    int result[16] = {0};
    for (int i = 0; i < 16; i++) {
        result[i] = text[i] ^ key[i];
    }
    return result;
}

int* InvMixColumns(int* text)
{
    int result[16] = {0};
    return result;
}

int* InvShiftRows(int* text)
{
    int result[16] = {0};
    return result;
}

int* InvSubBytes(int* text, int* sbox)
{
    int result[16] = {0};
    return result;
}
