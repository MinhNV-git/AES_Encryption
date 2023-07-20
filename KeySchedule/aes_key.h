#ifndef KEYSCHEDULE_AES_KEY_H_
#define KEYSCHEDULE_AES_KEY_H_
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define AES_BIT         0           // 128bit -> 0 ; 192bit -> 1 ; 256bit -> 2

#define _Wi_KEY_P_(key,i,j)          (*(key+4*i + j))   // j=[0,3]

#if (AES_BIT == 0)
#define N_key       4          
#define Round       11   
#elif (AES_BIT == 1)
#define N_key       6          
#define Round       13   
#elif (AES_BIT == 2)
#define N_key       8          
#define Round       15   
#endif

void key_schedule(uint8_t* key, uint8_t type);
void AES_GetRoundKey(uint8_t* Round_Key, uint8_t round);

void display_key();
#endif