/*
CyptoPals - Set 1

Functions created while completing challenges for Set 1

See also:
    linked_list.h / linked_list.c
*/

#ifndef SET1_H
#define SET1_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*******************************************************************************
* FUNCTIONS
*   listed in order as they appear in set1.c
*******************************************************************************/

/* General Utilities */
void errExit(char *message);


/* Cryptography functions */
int getHexInt(char c);
char getHexChar(int num);
char *string_to_hexString(char *input);
char *hexString_to_base64String(char *input);
char *base64String_to_hexString(char *input);
int base64char_to_int(char c);
char *fixed_xor(char *buf1, char *buf2);
int score_plaintext(char *plaintext);
char *singleXOR_iterate(char *input);
char *encryptXor(char *plaintext, char *key);
int hammingDist(char *str1, char *str2);
int findKeySize(char *input);
void repeatedXOR_iterate(char *ciphertext, int keysize);





#endif
