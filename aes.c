#include <stdio.h>

// prototype declare
void AddRoundKey(unsigned int*, unsigned int*);
void MixColumns(unsigned int*);
void ShiftRows(unsigned int*);
void SubBytes(unsigned int*);
void KeyExtention(unsigned int*, int);
void PrintData(unsigned int*, int);

int main(int argc, char** argv)
{
    // variables
    int round_value = 10;
    unsigned int plain_text[16] = {
        // 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
        0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34
    };
    unsigned int crypt_key[16] = {
        // 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
    };
    unsigned int result_text[16] = {0};
    for (int i = 0; i < 16; i++)
        result_text[i] = plain_text[i];

    // function call
    printf("\n");
    printf("input : ");
    for (int k = 0; k < 16; k++)
        printf("%2x ", result_text[k]);
    printf("\n");
    printf("k_sch : ");
    for (int k = 0; k < 16; k++)
        printf("%2x ", crypt_key[k]);
    printf("\n\n");

    AddRoundKey(result_text, crypt_key);
    KeyExtention(crypt_key, 0);
    for (int i = 0; i < round_value-1; i++) {
        printf("round : %d\n", i+1);
        printf("start : ");
        for (int k = 0; k < 16; k++)
            printf("%2x ", result_text[k]);
        printf("\n");
        SubBytes(result_text);
        printf("s_box : ");
        for (int k = 0; k < 16; k++)
            printf("%2x ", result_text[k]);
        printf("\n");
        ShiftRows(result_text);
        printf("s_row : ");
        for (int k = 0; k < 16; k++)
            printf("%2x ", result_text[k]);
        printf("\n");
        MixColumns(result_text);
        printf("m_col : ");
        for (int k = 0; k < 16; k++)
            printf("%2x ", result_text[k]);
        printf("\n");
        printf("k_sch : ");
        for (int k = 0; k < 16; k++)
            printf("%2x ", crypt_key[k]);
        printf("\n\n\n");
        AddRoundKey(result_text, crypt_key);
        KeyExtention(crypt_key, i+1);
    }
    SubBytes(result_text);
    ShiftRows(result_text);
    AddRoundKey(result_text, crypt_key);

    // show the result
    printf("input value : ");
    for (int i = 0; i < 16; i++) {
        printf("%2x ", plain_text[i]);
    }
    printf("\n");
    printf("result value: ");
    for (int i = 0; i < 16; i++) {
        printf("%2x ", result_text[i]);
    }
    printf("\nend\n");

    return 0;
}

void AddRoundKey(unsigned int* result, unsigned int* key)
{
    for (int i = 0; i < 16; i++)
        result[i] = result[i] ^ key[i];
}

void MixColumns(unsigned int* r)
{
    int b[16] = {0};
    for (int i = 0; i < 16; i+=4) {
        b[i+0]  = r[i+0] << 1 ^ r[i+1] ^ r[i+1] << 1 ^ r[i+2] ^ r[i+3];
        b[i+1]  = r[i+0] ^ r[i+1] << 1 ^ r[i+2] ^ r[i+2] << 1 ^ r[i+3];
        b[i+2]  = r[i+0] ^ r[i+1] ^ r[i+2] << 1 ^ r[i+3] << 1 ^ r[i+3];
        b[i+3]  = r[i+0] << 1 ^ r[i+0] ^ r[i+1] ^ r[i+2] ^ r[i+3] << 1;
    }
    for (int i = 0; i < 16; i++) {
        if (b[i] > 255) {
            b[i] = b[i] ^ 0x1b;
            b[i] = b[i] & 0xff;
        }
        r[i] = b[i];
    }
}

void ShiftRows(unsigned int* result)

{
    int buffer[16] = {0};
    for (int i = 0; i < 16; i++)
        buffer[i] = result[i];
    result[0]  = buffer[0];
    result[1]  = buffer[5];
    result[2]  = buffer[10];
    result[3]  = buffer[15];
    result[4]  = buffer[4];
    result[5]  = buffer[9];
    result[6]  = buffer[14];
    result[7]  = buffer[3];
    result[8]  = buffer[8];
    result[9]  = buffer[13];
    result[10] = buffer[2];
    result[11] = buffer[7];
    result[12] = buffer[12];
    result[13] = buffer[1];
    result[14] = buffer[6];
    result[15] = buffer[11];
}

void SubBytes(unsigned int* result)
{
    int sbox_matrix[16][16] = {
        {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
        {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
        {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
        {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
        {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
        {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
        {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
        {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
        {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
        {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
        {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
        {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
        {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
        {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
        {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
        {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
    };
    for (int i = 0; i < 16; i++) {
        unsigned int row_index = result[i] & 0x0f;
        unsigned int column_index = result[i] >> 4;
        result[i] = sbox_matrix[column_index][row_index];
    }
}

void KeyExtention(unsigned int* key, int round)
{
    unsigned int buffer[16] = {0};
    unsigned int Rcon[10][4] = {
        {0x01, 0x00, 0x00, 0x00},
        {0x02, 0x00, 0x00, 0x00},
        {0x04, 0x00, 0x00, 0x00},
        {0x08, 0x00, 0x00, 0x00},
        {0x10, 0x00, 0x00, 0x00},
        {0x20, 0x00, 0x00, 0x00},
        {0x40, 0x00, 0x00, 0x00},
        {0x80, 0x00, 0x00, 0x00},
        {0x1b, 0x00, 0x00, 0x00},
        {0x36, 0x00, 0x00, 0x00}
    };
    // buffer[ 3] = key[ 7];
    // buffer[ 7] = key[11];
    // buffer[11] = key[15];
    // buffer[15] = key[ 3];
    buffer[12] = key[13];
    buffer[13] = key[14];
    buffer[14] = key[15];
    buffer[15] = key[12];

    // printf("m_buf : ");
    // for (int k = 0; k < 16; k++)
    //     printf("%2x ", buffer[k]);
    // printf("\n");
    SubBytes(buffer);
    // printf("m_buf : ");
    // for (int k = 0; k < 16; k++)
    //     printf("%2x ", buffer[k]);
    // printf("\n");
    for (int i = 0; i < 12; i++) {
        buffer[i] = key[i];
    }
    printf("m_buf : ");
    for (int k = 0; k < 16; k++)
        printf("%2x ", key[k]);
    printf("\n");

    for (int i = 0; i < 16; i++) {
        if (i < 4) {
            key[i] = buffer[i] ^ buffer[i+12] ^ Rcon[round][i];
        } else if (i < 12) {
            key[i] = key[i-4] ^ buffer[i];
        } else {
            printf("%2x ^ %2x = ",key[i-4], key[i]);
            key[i] = key[i-4] ^ key[i];
            printf("%2x\n", key[i]);
        }
    }
    // buffer[12] = key[13];
    // buffer[13] = key[14];
    // buffer[14] = key[15];
    // buffer[15] = key[12];
    // SubBytes(buffer);
    // for (int i = 0; i < 4; i++) {
    //     key[i+12] = buffer[i+12];
    // }
    // printf("m_buf : ");
    // for (int k = 0; k < 16; k++)
    //     printf("%2x ", buffer[k]);
    // printf("\n");
    // key[12] = buffer[13];
    // key[13] = buffer[14];
    // key[14] = buffer[15];
    // key[15] = buffer[16];

    printf("m_key : ");

    for (int k = 0; k < 16; k++)
        printf("%2x ", key[k]);
    printf("\n");
}

void PrintData(unsigned int* data, int length)
{
    for (int i = 0; i < length; i++)
        printf("%2x ", data[i]);
    printf("\n");
}
