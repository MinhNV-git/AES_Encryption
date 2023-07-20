#include "aes.h"

extern uint8_t S_box[256];

// const uint8_t matrix[16] = {2,1,1,3,3,2,1,1,1,3,2,1,1,1,3,2};

static void AES_SubBytes(uint8_t*);
static void AES_ShiftRows(uint8_t*);
static void AES_AddRoundKey(uint8_t* ip, uint8_t* roundkey);
static void AES_MixColumns(uint8_t*);
static uint8_t multix2_gf_2_8(uint8_t);
static uint8_t multix3_gf_2_8(uint8_t);

static void AES_SubBytes(uint8_t* input)
{
    uint8_t i;
    for(i=0;i<16;i++)
    {
        *(input+i) = S_box[*(input+i)]; 
    }
}
static void AES_ShiftRows(uint8_t* ip)
{
    uint8_t pos;
    uint8_t i,j;

    for(j=0;j<4;j++)
    {
        i=j;
        while (i>0)
        {
            pos = _IN_BLOCK_P_(ip,0,j);
            _IN_BLOCK_P_(ip,0,j) = _IN_BLOCK_P_(ip,1,j);
            _IN_BLOCK_P_(ip,1,j) = _IN_BLOCK_P_(ip,2,j);
            _IN_BLOCK_P_(ip,2,j) = _IN_BLOCK_P_(ip,3,j);
            _IN_BLOCK_P_(ip,3,j) = pos;
            i--;
        }
    }
}

/*  multi x2 on the GF(2^8) Feild
    2*byte =    {2*byte                     if (2*byte <= 0xFF)
                {(uint8_t)2*byte ^ 0x11B    if(2*byte > 0xFF)

    3*byte = 2*byte ^ byte;
*/
static uint8_t multix2_gf_2_8(uint8_t byte)
{
    uint16_t pos, result;
    pos = 2*byte;
    if(pos>0xff)
        result = pos ^ 0x11B;
    else
        result = pos;
    return (uint8_t)result;
}
static uint8_t multix3_gf_2_8(uint8_t byte)
{
    uint16_t pos, result;
    pos = 2*byte;
    if(pos>0xff)
        result = pos ^ 0x11B;
    else
        result = pos;
    result ^= byte;
    return (uint8_t)result;
}
static void AES_MixColumns(uint8_t* ip)
{
    uint8_t cp_ip[16];
    uint8_t i;
    for(i=0;i<16;i++)
    {
        cp_ip[i] = *(ip+i);
    }

    for(i=0;i<4;i++)
    {
        _IN_BLOCK_P_(ip,i,0) = multix2_gf_2_8(_IN_BLOCK_P_(cp_ip,i,0)) ^ multix3_gf_2_8(_IN_BLOCK_P_(cp_ip,i,1)) ^ _IN_BLOCK_P_(cp_ip,i,2) ^ _IN_BLOCK_P_(cp_ip,i,3);
        _IN_BLOCK_P_(ip,i,1) = multix2_gf_2_8(_IN_BLOCK_P_(cp_ip,i,1)) ^ multix3_gf_2_8(_IN_BLOCK_P_(cp_ip,i,2)) ^ _IN_BLOCK_P_(cp_ip,i,0) ^ _IN_BLOCK_P_(cp_ip,i,3);
        _IN_BLOCK_P_(ip,i,2) = multix2_gf_2_8(_IN_BLOCK_P_(cp_ip,i,2)) ^ multix3_gf_2_8(_IN_BLOCK_P_(cp_ip,i,3)) ^ _IN_BLOCK_P_(cp_ip,i,0) ^ _IN_BLOCK_P_(cp_ip,i,1);
        _IN_BLOCK_P_(ip,i,3) = multix2_gf_2_8(_IN_BLOCK_P_(cp_ip,i,3)) ^ multix3_gf_2_8(_IN_BLOCK_P_(cp_ip,i,0)) ^ _IN_BLOCK_P_(cp_ip,i,2) ^ _IN_BLOCK_P_(cp_ip,i,1);
    }
}
static void AES_AddRoundKey(uint8_t* ip, uint8_t* roundkey)
{
    uint8_t i;
    for(i=0;i<16;i++)
    {
        *(ip+i) ^= *(roundkey+i);
    }
}


void AES_Process(uint8_t* data, uint8_t* key)
{
    uint8_t Round_Key[16];
    uint8_t i;
    key_schedule(key, 0);

    // init round
    AES_GetRoundKey(Round_Key, 0);
    AES_AddRoundKey(data, Round_Key);

    // 10 round
    for(i=1;i<10;i++)
    {
        AES_SubBytes(data);
        AES_ShiftRows(data);
        AES_MixColumns(data);
        AES_GetRoundKey(Round_Key, i);
        AES_AddRoundKey(data,Round_Key);
    }

    // final round
    AES_SubBytes(data);
    AES_ShiftRows(data);
    AES_GetRoundKey(Round_Key,10);
    AES_AddRoundKey(data, Round_Key);
}

/*************************************/