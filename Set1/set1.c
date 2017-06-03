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
                        '3', '4', '5', '6', '7', '8', '9', '+', '\\'};


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
Candidate *createCandidateStruct(char *input)
{
    /* Creates a Candidate struct and returns a pointer to it  */
    Candidate *can = (Candidate *) malloc(sizeof(Candidate));
    can->ciphertext = input;
    can->plaintext = (char *) malloc(sizeof(char) * (strlen(input) / 2) + 1);
    can->plain_length = 0;
    can->score = 0.0;
    return can;
}

/*****************************************************************************/
void analyzeCandidate(Candidate *can)
{
    /*  Given a "Candidate" struct, it analyzes the plaintext determined from
        XOR'ing the given ciphertext with a random byte value, assuming
        single-XOR encryption.

        Each score is calculated and stored in the Candidate struct's
        can->score member.
    */
    can->score = scorePlaintext(can->plaintext);
}


/*****************************************************************************/
int scorePlaintext(char *plaintext)
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
char *findHighestScore(LinkedList *list)
{
    /* function that will return the candidate's plaintext with the highest
       score.     */

    double score = 0;
    Candidate *tmp, *can;

    list->current = list->head;
    while (list->current != NULL) {
        tmp = (Candidate *) list->current->data;

        if (tmp->score > score) {
            can = tmp;
            score = can->score;
            //printf("score: %f\n", score);
        }

        list->current = list->current->next;
    }

    char *result = (char *) can->plaintext;
    return result;
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

    /* create an array of numerical representation of the input string */
    for (int i = 0; i < INPUT_LEN; i += 2) {
        INPUT_ARR[index++] = getHexInt(input[i]) * 16 + getHexInt(input[i + 1]);
    }

    LinkedList *list = ListInit();

    char byte;     /* xor string against this */
    int num;

    for (int i = 0; i < 256; i++) { /* iterate through 1-byte 0-255  */
        byte = (char) i;
        Candidate *can = createCandidateStruct(input);  // set1.c
        index = 0;

        for (int j = 0; j < INPUT_LEN / 2; j++) { /* iterate through INPUT_ARR */
            num = INPUT_ARR[j];
            num ^= byte;
            can->plaintext[index++] = (char) num;
        }

        /* add Candidate to LinkedList (see linked_list.c) */
        insert_node(list, (void *) can);

        /* analyze plaintext and 'score' it */
        analyzeCandidate(can);
    }

    char *result = (char *) malloc(sizeof(char) * INPUT_LEN);
    memset(result, '\0', INPUT_LEN);
    strcpy(result, findHighestScore(list));

    freeLinkedList(list);
    free(INPUT_ARR);
    INPUT_ARR = NULL;

    return result;
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



/*******************************************************************************
* FUNCTIONS - LINKED LIST UTILITIES
*******************************************************************************/

LinkedList *ListInit(void)
{
    /*  Creates the data structure to manage the linked list

        :INPUT is nothing

        :RETURNS the LinkedList data structure
    */

    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    list->size = 0;

    return list;
}


/******************************************************************************/
void insert_node(LinkedList *list, void *item)
{
    /*  Inserts a data item into the list

        :INPUT is a LinkedList already initialized, as well as the data item
        the list will track, such as a Candidate struct (see set1.c)

        :RETURNS nothing
    */

    Node *node = (Node *) malloc(sizeof(Node));     // create a node struct
    node->data = item;      // point it at the Candidate struct

    if (list->size == 0) {  // list is empty
        node->next = NULL;
        list->tail = node;
    } else {    // node is not empty... insert at head
        node->next = list->head;
    }

    list->head = node;
    list->current = node;
    list->size++;

    return;
}


/******************************************************************************/
void freeLinkedList(LinkedList *list)
{
    /*  Frees all members in the linked list to avoid memory leaks

        :INPUT a LinkedList that was previously used.  This program assumes
        the data element in the Node struct was a "Candidate" struct from
        set1.h

        :RETURNS nothing
    */

    Candidate *can;
    Node *node;

    //printf("LinkedList current size: %u\n", list->size);

    list->current = list->head;     // point to head node
    while (list->current != NULL) {   // iterate through list
        node = list->current;
        can = (Candidate *) node->data;

        list->current = list->current->next;

        free(can->plaintext);
        free(can);
        free(node);

        list->size--;
        //printf("LinkedList current size: %u\n", list->size);

        can->plaintext = NULL;
        can = NULL;
        node = NULL;
    }

    free(list);
    list = NULL;

    //printf("LinkedList 100%% free!\n");
    return;
}

/******************************************************************************/
