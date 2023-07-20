#ifndef ENCRYPTIONPROCESS_AES_KEY_H_
#define ENCRYPTIONPROCESS_AES_KEY_H_
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "../KeySchedule/aes_key.h"

#define _IN_BLOCK_P_(key,column,row)            (_Wi_KEY_P_(key,column,row))

void AES_Process(uint8_t* data, uint8_t* key);
#endif