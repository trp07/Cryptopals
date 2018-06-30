/*
gcc set1.c b64hexTest.c -o b64hexTest
*/

#include <stdio.h>
#include <stdlib.h>
#include "set1.h"

int main(void)
{
    FILE *fin = fopen("6_input_clean.txt", "r");
    if (fin == NULL)
        errExit("fopen failed in main");

    /* 'getline' variables */
    char *lineptr = NULL;
    size_t n;
    ssize_t read;

    /* read in base64-encoded string */
    read = getline(&lineptr, &n, fin);
    if (read == -1)
        errExit("getline failed in main");

    /* convert base64-encoded string to hex string  */
    char *ciphertext = base64String_to_hexString(lineptr);
    //printf("%s\n", ciphertext);

    /* find the possible keysize */
    int KEYSIZE = findKeySize(ciphertext);
    //printf("KEYSIZE = %d\n", KEYSIZE);

    /* break repeating xor */
    repeatedXOR_iterate(ciphertext, KEYSIZE);

    /* reap resources */
    fclose(fin);
    free(ciphertext);
    free(lineptr);
    ciphertext = lineptr = NULL;

    return 0;
}
