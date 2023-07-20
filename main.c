#include "KeySchedule/aes_key.h"
#include "EncryptionProcess/aes.h"
#include <stdio.h>

#define AES_128BIT      0
#define AES_192BIT      1
#define AES_256BIT      2

// uint8_t Original_Key[16] = {0x2b, 0x7e, 0x15, 0x16,
//                             0x28, 0xae, 0xd2, 0xa6,
//                             0xab, 0xf7, 0x15, 0x88,
//                             0x09, 0xcf, 0x4f, 0x3c};

// uint8_t data[16] = {0x32, 0x43, 0xf6, 0xa8,
//                     0x88, 0x5a, 0x30, 0x8d,
//                     0x31, 0x31, 0x98, 0xa2,
//                     0xe0, 0x37, 0x07, 0x34};

uint8_t Original_Key[16] = {'n','g','u','y','e','n','v','a','n','m','i','n','h','1','0','7'};
uint8_t data[16] = {'1','2','3','4','5','6','7','8','9','1','2','3','4','5','6','7'};
uint8_t Round_key[16] = {};

int main()
{
    uint8_t i;
    printf("\r\n*************** AES ***************\r\n");
    
    for(i=0;i<16;i++)
    {
        printf(" %x ", data[i]);
        if(i%4==3)
            printf("\r\n");
    }

    AES_Process(data, Original_Key);

    printf("RESULT \r\n");
    for(i=0;i<16;i++)
    {
        printf(" %x ", data[i]);
        if(i%4==3)
            printf("\r\n");
    }
}