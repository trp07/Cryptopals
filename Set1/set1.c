/*
CyptoPals - Set 1

Functions created while completing challenges for Set 1

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "set1.h"

/*******************************************************************************
* GLOBAL VARs
*******************************************************************************/

/* array of base64 characters */
char base64_vals[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                        'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                        'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                        'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                        's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
                        '3', '4', '5', '6', '7', '8', '9', '+', '/'};



/*******************************************************************************
* FUNCTIONS - GENERAL UTILITIES
*******************************************************************************/

void errExit(char *message)
{
    /* error and exit function */

    fprintf(stderr, "[!] %s\n", message);
    exit(EXIT_FAILURE);
}



/*******************************************************************************
* FUNCTIONS - CRYPTOGRAPHY
*******************************************************************************/


int getHexInt(char c)
{
    /* Utility function to convert hex characters to integers.

       :INPUT is a hex digits currently represented in ASCII, then converts
       it to an integer.

       :RETURNS the hexadecimal value as an integer, i.e. 0xd = 13
    */

    int num = (int) c;

    if (num >= 48 && num <= 57)         /* ascii 0-9 */
        num -= 48;
    else if (num >= 65 && num <= 70)    /* ascii A-F */
        num = num - 65 + 10;
    else if (num >= 97 && num <= 102)   /* ascii a-f */
        num = num - 97 + 10;
    else {
        fprintf(stderr, "[!] 'getHexInt' received"
                " a non-hex character: %d\n", num);
        exit(EXIT_FAILURE);
    }

    return num;
}


/*****************************************************************************/
char getHexChar(int num)
{
    /* Utility function to convert int numbers to their hex char equivalents.

       :INPUT is a hex digit, then converts it to the ASCII char equivalent.

       :RETURN the hexadecimal value as an integer, i.e. 0xd = 13
    */
    switch(num) {
        case 0:  return '0'; break;
        case 1:  return '1'; break;
        case 2:  return '2'; break;
        case 3:  return '3'; break;
        case 4:  return '4'; break;
        case 5:  return '5'; break;
        case 6:  return '6'; break;
        case 7:  return '7'; break;
        case 8:  return '8'; break;
        case 9:  return '9'; break;
        case 10: return 'a'; break;
        case 11: return 'b'; break;
        case 12: return 'c'; break;
        case 13: return 'd'; break;
        case 14: return 'e'; break;
        case 15: return 'f'; break;
        default: return '*';
    }
}


/*****************************************************************************/
char *string_to_hexString(char *input)
{
    /*  Given a string, returns the same string but with hex character
        equivalents
    */

    int a, b, index = 0;
    char *result = (char *) malloc(sizeof(char) * strlen(input) * 2 + 1);

    for (int i = 0; i < strlen(input); i++) {
        if ((int) input[i] <= 15) {
            result[index++] = '0';
            result[index++] = getHexChar(input[i]);
        } else {
            a = (int) input[i] / 16;
            b = (int) input[i] % 16;
            result[index++] = getHexChar(a);
            result[index++] = getHexChar(b);
        }
    }

    return result;
}

/*****************************************************************************/
char *hexString_to_base64String(char *input)
{
    /*  This function converts the characters to their numerical equivalent,
        then converts the input string to Base64

        :INPUT is a string of hexadecimal digits without the leading '0x'

        :RETURN is a base64 encoded string

        *** Must use free() in the calling function to free memory allocated.
    */

    /* get length of input string */
    int INPUT_LEN  = strlen(input);
    int OUTPUT_LEN = (INPUT_LEN / 2) * 4 / 3;

    /* pad output string length if needed to make its length a power of 3 */
    int PADDING = (INPUT_LEN / 2) % 3;
    if (PADDING) {
        PADDING = 3 - PADDING;
        INPUT_LEN += PADDING;
        OUTPUT_LEN += PADDING;
    }

    /* allocate memory for the input string so we can append padding */
    char *hex = (char *) malloc(sizeof(char) * INPUT_LEN + 1);
    strcpy(hex, input);
    if (PADDING == 1)
        strcat(hex, "00");
    else if (PADDING == 2)
        strcat(hex, "0000");

    /* Calculate length of output string
       OUTPUT is calculated by taking (INPUT_LEN / 2) which represents the
       number of hex bytes, since each hex byte is 2 characters.  Then
       Multiple by 4/3 since for every 3 hex ints produces 4 base64 chars */

    /* allocate memory for output string */
    char *base64String = (char *) malloc(sizeof(char) * OUTPUT_LEN + 1);
    int index = 0;

    /* create placeholder vars for conversion from char->hex->base64 */
    int nums[3], idx1, idx2, idx3, idx4;

    /*  Read in 6 chars from input string at a time, where 2 chars correspond
        to a hex number.  The 6 chars will be converted to 3 hex numbers,
        which will create 24 bits of data for the 3 numbers.  Since each base64
        char is a 6 bit index value, the 24 bits will create 4 base64 chars.  */
    for (int i = 0; i < INPUT_LEN; i += 6) { /* read 6 chars at a time */

        for (int j = 0; j < 3; j++) {  /* create 3 ints from the 6 chars */

            nums[j] = getHexInt(hex[i + j*2])*16 + getHexInt(hex[i+1 + j*2]);
        }

        /* now convert the nums[] to index values in the base64_vals array
           this requires masking and shifting bits to make 3 integers composed
           of 24 bits to become 4 characters of 6 bits  */
        idx1 = (nums[0] & 0xfc) >> 2;
        idx2 = ((nums[0] & 0x03) << 4) + ((nums[1] & 0xf0) >> 4);
        idx3 = ((nums[1] & 0x0f) << 2) + ((nums[2] & 0xd0) >> 6);
        idx4 = (nums[2] & 0x3f);

        base64String[index++] = base64_vals[idx1];
        base64String[index++] = base64_vals[idx2];
        base64String[index++] = base64_vals[idx3];
        base64String[index++] = base64_vals[idx4];
    }

    /* correct last couple of characters if padding was used to make the last
       Base64 character or last two characters a '=' */
    if (PADDING == 1)
        base64String[OUTPUT_LEN] = '=';
    else if (PADDING == 2) {
        base64String[OUTPUT_LEN] = '=';
        base64String[OUTPUT_LEN - 1] = '=';
    }

    /* free memory and return */
    free(hex);
    hex = NULL;

    return base64String;
}


/*****************************************************************************/
char *base64String_to_hexString(char *input)
{
    /*  This function converts a base64-encoded string to a hexadecimal
        equivalent string.

        :INPUT is a base64-encoded string

        :RETURN is a hexadecimal string

        *** Must use free() in the calling function to free memory allocated.
    */

    int INPUT_LEN = strlen(input);
    int OUTPUT_LEN = (INPUT_LEN * 2) * 3 / 4; // 4 chars produce 3 ints
    int PADDING = 0;

    /* was the base64-encoded string padded? If so, modify string lengths*/
    if (input[INPUT_LEN - 1] == '=') {
        PADDING++;
    }
    if (input[INPUT_LEN - 2] == '=') {
        PADDING++;
    }
    INPUT_LEN  -= PADDING;
    OUTPUT_LEN -= (2 * PADDING);


    /* allocate memory for output string, 'index' will be used to assign
       hex chars at various index locations  */
    char *output = (char *) malloc(sizeof(char) * OUTPUT_LEN + 1);
    int index = 0;

    /* vars for converting base64 to hex, 'b' denotes base64, 'h' for hex */
    int b1, b2, b3, b4, h1, h2, h3;

    /* read in 4 chars at a time to produce 3 ints for the output */
    for (int i = 0; i < INPUT_LEN; i += 4) {
        b1 = base64char_to_int(input[i]);
        b2 = base64char_to_int(input[i + 1]);
        b3 = base64char_to_int(input[i + 2]);
        b4 = base64char_to_int(input[i + 3]);

        /* validate b1-b4.  If base64char_to_int returned -1 for b1-b4,
           then it's probably because it read the trailing '=' symbols.
           Make them 0 for now, then truncate the output string before return */
        if (b1 == -1 || b2 == -1 || b3 == -1 || b4 == -1) {
            if (i >= INPUT_LEN)
                b1 = 0;
            if (i + 1 >= INPUT_LEN)
                b2 = 0;
            if (i + 2 >= INPUT_LEN)
                b3 = 0;
            if (i + 3 >= INPUT_LEN)
                b4 = 0;
        }

        /* convert from 6-bit base64 to 8-bit hex */
        h1 = (b1 << 2) + (b2 >> 4);
        h2 = ((b2 & 0xf) << 4) + ((b3 & 0x3c) >> 2);
        h3 = ((b3 & 0x03) << 6) + b4;

        /* assign hex chars to output string */
        output[index++] = getHexChar((h1 / 16));
        output[index++] = getHexChar((h1 % 16));
        output[index++] = getHexChar((h2 / 16));
        output[index++] = getHexChar((h2 % 16));
        output[index++] = getHexChar((h3 / 16));
        output[index++] = getHexChar((h3 % 16));
    }

    output[OUTPUT_LEN] = '\0';
    return output;
}

/*****************************************************************************/
int base64char_to_int(char c)
{
    /* Given a base64 characters, returns the integer equivalent, as shown in
       the 'base64_vals' global var at the top.

       Returns -1 on error.
    */
    int result = 0;
    switch(c) {
        case 'A'...'Z':
            result = ((int) c) - 65 + 0;
            break;
        case 'a'...'z':
            result = ((int) c) - 97 + 26;
            break;
        case '0'...'9':
            result = ((int) c) - 48 + 52;
            break;
        case '+':
            result = 62;
            break;
        case '/':
            result = 63;
            break;
        default:
            result = -1;
    }
    return result;
}


/*****************************************************************************/
char *fixed_xor(char *buf1, char *buf2)
{
    /* This function will do a fixed XOR of two equal-length buffers.

       :INPUT are two equal-length char buffers of hex digits

       :RETURN a dynamically allocated buffer of their XOR.

       *** Must use free() in the calling function to free memory allocated.
    */

    if (strlen(buf1) != strlen(buf2)) {
        fprintf(stderr, "Cannot do Fixed_Xor: buffers need to be same size\n");
        exit(EXIT_FAILURE);
    }

    /* create variables and allocate memory for 'result' string */
    int bufsize = strlen(buf1);
    char *result = (char *) malloc(sizeof(char) * bufsize + 1);
    int res;

    /* step through buf1 and buf2, XOR their integer equivalents, then convert
       back to ASCII */
    for (int i = 0; i < bufsize; i++) {
        res = getHexInt(buf1[i]) ^ getHexInt(buf2[i]);
        result[i] = getHexChar(res);
    }

    return result;
}


/*****************************************************************************/
int score_plaintext(char *plaintext)
{
    /*  Given a plaintext string, it does a makeshift frequency analysis of the
        English language by adding a specified value to a 'score' variable
        based on what the current character being analyzed is.

        Technique borrowed from:
        https://github.com/talshorer/cryptopals/blob/master/set1/single_byte_xor.c

        :INPUT is a plaintext string

        :RETURNS an integer indicating its score.  The higher the better.
    */


    int plain_len = strlen(plaintext);
    int score = 0;

    for (int i = 0; i < plain_len; i++) {
        switch(plaintext[i]) {
            case 'a'...'z':     /* fallthrough */
            case 'A'...'Z':     /* fallthrough */
                score += 4; break;
            case '0'...'9':     /* fallthrough */
            case '\'':          /* fallthrough */
            case '\n':          /* fallthrough */
            case '\t':          /* fallthrough */
            case ',':           /* fallthrough */
            case '.':           /* fallthrough */
            case ' ':
                score += 2; break;
            case '!':           /* fallthrough */
            case '?':           /* fallthrough */
            case '-':           /* fallthrough */
            case '/':
                score += 1; break;
        }
    }

    return score;
}


/*****************************************************************************/
char *singleXOR_iterate(char *input)
{
    /* Given a string encrypted via the single-xor method, functions iterates
       through all possible byte values as the XOR key. Function creates a
       linked-list of all "candidates" and does a makeshift frequency analysis
       to score each decrypted string.  Returns the 'best' candidate.

       :INPUT an encrypted string

       :RETURNS the decrypted string
    */

    int INPUT_LEN = strlen(input);
    int *INPUT_ARR = (int *) malloc(sizeof(int) * (INPUT_LEN / 2));
    int index = 0;

    /* create an array of numerical representations of the input string */
    for (int i = 0; i < INPUT_LEN; i += 2) {
        INPUT_ARR[index++] = getHexInt(input[i]) * 16 + getHexInt(input[i + 1]);
    }


    char byte;     /* xor string against this */
    int num;
    int score, score_best = -1;  /* set score_best initially low */

    /* two array strings to hold plaintext and find the best one */
    char *plain = (char *) malloc(sizeof(char) * (strlen(input) / 2) + 1);
    char *plain_best = (char *) malloc(sizeof(char) * (strlen(input) / 2) + 1);

    for (int i = 0; i < 256; i++) { /* iterate through 1-byte 0-255  */
        byte = (char) i;
        index = 0;

        for (int j = 0; j < INPUT_LEN / 2; j++) { /* iterate through INPUT_ARR */
            num = INPUT_ARR[j];
            num ^= byte;
            plain[index++] = (char) num;
        }
        plain[index] = '\0';

        score = score_plaintext(plain);

        /* compare scores */
        if (score > score_best) {
            score_best = score;
            strcpy(plain_best, plain);
        }

    }

    /* reap resources and return */
    free(INPUT_ARR);
    free(plain);
    INPUT_ARR = NULL;
    plain = NULL;

    return plain_best;
}

/*****************************************************************************/
char *encryptXor(char *plaintext, char *key)
{
    /*  Given a plaintext string and a key, this function returns the cipher
        text that results from reapeated xor encryption.
    */

    char *result;
    char *cipher = (char *) malloc(sizeof(char) * strlen(plaintext) + 1);


    for (int i = 0; i < strlen(plaintext); i++) {
         cipher[i] = plaintext[i] ^ key[i % strlen(key)];
    }

    result = string_to_hexString(cipher);

    free(cipher);
    cipher = NULL;
    return result;
}


/*****************************************************************************/
int hammingDist(char *str1, char *str2)
{
    /*  Given two strings of equal length, it returns the hamming/edit distance
        between each string.  Typically, the number of different characters
        between the strings, but this will do it bit-by-bit.

        RETURNS -1 on error
    */

    if (strlen(str1) != strlen(str2))
        return -1;

    int len = strlen(str1);
    int hamming = 0;
    int temp;

    for (int i = 0; i < len; i++) {
        if (str1[i] != str2[i])
            temp = str1[i] ^ str2[i];  // find bits where they differ

            /* find out which bits are set, indicating a difference */
            if (temp & 1)
                hamming++;
            if (temp & 2)
                hamming++;
            if (temp & 4)
                hamming++;
            if (temp & 8)
                hamming++;
            if (temp & 16)
                hamming++;
            if (temp & 32)
                hamming++;
            if (temp & 64)
                hamming++;
            if (temp & 128)
                hamming++;
    }

    return hamming;
}


/*****************************************************************************/
int findKeySize(char *input)
{
    /*  Given a hex string, find the KEYSIZE based on the hamming distance.

        *  "For each KEYSIZE, take the first KEYSIZE worth of bytes, and the
        second KEYSIZE worth of bytes, and find the edit distance between them.
        Normalize this result by dividing by KEYSIZE."

        * "The KEYSIZE with the smallest normalized edit distance is probably
        the key. You could proceed perhaps with the smallest 2-3 KEYSIZE
        values. Or take 4 KEYSIZE blocks instead of 2 and average the distances."
    */

    int MAX_SIZE = 41;      /* max keysize that will be checked */
    int KEYSIZE, ham12, ham34;
    double ham_avg, ham_min = 1000; /* set ham_min arbitrarily high at first */

    char *block1, *block2, *block3, *block4;
    block1 = (char *) malloc(sizeof(char) * MAX_SIZE + 1);
    block2 = (char *) malloc(sizeof(char) * MAX_SIZE + 1);
    block3 = (char *) malloc(sizeof(char) * MAX_SIZE + 1);
    block4 = (char *) malloc(sizeof(char) * MAX_SIZE + 1);

    /* try keysizes from 2-40 */
    for (int i = 2; i < 41; i++) {

        /* grab a slice of the input string */
        for (int j = 0; j < i; j++) {
            block1[j] = input[0 * i + j];
            block2[j] = input[1 * i + j];
            block3[j] = input[2 * i + j];
            block4[j] = input[3 * i + j];
        }

        /* null-terminate the blocks */
        block1[i] = block2[i] = block3[i] = block4[i] = '\0';

        /* find hamming distances of each block and get normalized-average */
        ham12 = hammingDist(block1, block2);
        ham34 = hammingDist(block3, block4);
        ham_avg = (double) (ham12 + ham34) / (2 * i);
        //printf("[%d] -> %f\n", i, ham_avg);

        if (ham_avg < ham_min) {
            ham_min = ham_avg;
            KEYSIZE = i;
        }
    }

    /* free memory and return */
    free(block1);
    free(block2);
    free(block3);
    free(block4);
    block1 = block2 = block3 = block4 = NULL;

    return KEYSIZE;
}

/*****************************************************************************/
void repeatedXOR_iterate(char *ciphertext, int keysize)
{

    /* how big are each block?  */
    int cipherlen = strlen(ciphertext);
    int remainder = cipherlen % keysize;
    int blocklen = cipherlen / keysize;

    /* for hex string, each two string digits equate to one plain char */
    char *plaintext = (char *) malloc((sizeof(char) * cipherlen) / 2 + 1);
    int index;

    for (int i = 0; i < keysize; i++) {
        index = 0;
        char *block   = (char *) malloc(sizeof(char) * blocklen * 2 + 2 + 1);
        char *partial = (char *) malloc(sizeof(char) * blocklen * 2 + 2 + 1);

        /* break ciphertext into blocks stepping every keysize-num chars */
        for (int j = 0; j < (2 * blocklen); j += 2) {
            block[j]   = ciphertext[j / 2 * keysize + i];
            block[j+1] = ciphertext[j / 2 * keysize + i + 1];
        }

        /* if cipherlen % keysize != 0, then add remaining chars */
        if (remainder != 0 && i < remainder) {
            block[2 * blocklen]     = ciphertext[blocklen * keysize + i];
            block[2 * blocklen + 1] = ciphertext[blocklen * keysize + i + 1];
        } else {
            block[2 * blocklen]     = '\0';
            block[2 * blocklen + 1] = '\0';
        }

        /* null-terminate the block */
        block[2 * blocklen + 2] = '\0';
        //printf("block[%d] = %s\n", i, block);

        /* call singleXOR_iterate on each block */
        partial = singleXOR_iterate(block);

        /* place each char of 'partial' back into plaintext at keysize steps */
        for (int k = 0; k < strlen(partial); k++) {
            plaintext[index + i] = partial[k];
            index += keysize;
            if (index > cipherlen)
                index = cipherlen;
        }

        /* reap block resources */
        free(block);
        free(partial);
        block = partial = NULL;
    }

    printf("%s\n", plaintext);
    free(plaintext);
    plaintext = NULL;
}
