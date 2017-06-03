/*
CyptoPals - Set 1

Functions created while completing challenges for Set 1

See also:
    linked_list.h / linked_list.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "set1.h"
#include "linked_list.h"

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
* FUNCTIONS
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

       :INPUT is a hex digits, then converts it to the ASCII char equivalent.

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
    can->plain_length = can->num_vowels = can->num_consanants = 0;
    can->vowel_cons_ratio = can->letter_length_ratio = can->score = 0;
    return can;
}

/*****************************************************************************/
void analyzeCandidate(Candidate *can)
{
    /*  Given a "Candidate" struct, it analyzes the plaintext determined from
        XOR'ing the given ciphertext with a random byte value, assuming
        single-XOR encryption.

        Analysis by doing a makeshift frequency analysis of the English
        language, such as percentage of letters as a ratio to the string length,
        number of vowels present, etc.

        Each score is calculated and stored in the Candidate struct's
        can->score member.

        VOW_CONS_RATIO = 0.382 was determined by using the English language
        frequency analysis graph from "Introduction to Modern Cyptography",
        2nd Ed., by Jonathan Katz, page 11.
        Adding all the vowel percentages shows that vowels comprise
        roughly 38.2% of letters in English text, on average.

        This is not the most robust way to score and may be improved over time,
        but consider this a first draft.
    */

    double VOW_CONS_RATIO = 0.382;

    can->plain_length = strlen(can->plaintext);

    for (int i = 0; i < can->plain_length; i++) {
        if (isalpha(can->plaintext[i])) {
            switch(can->plaintext[i]) {
                case 'a'|'A'|'e'|'E'|'i'|'O'|'o'|'U'|'u' :
                    can->num_vowels += 1; break;
                default:
                    can->num_consanants += 1;
            }
        }
    }

    /* to prevent divide-by-zero's */
    if (can->plain_length == 0 || can->num_consanants == 0) {
        can->score = 0.0;
        return;
    }

    can->vowel_cons_ratio = (double) can->num_vowels / can->num_consanants;
    can->letter_length_ratio = ((double) can->num_vowels +
                                (double) can->num_consanants) / can->plain_length;

    /* create score -- NEEDS tweaking  */
    can->score  = can->letter_length_ratio;
    can->score += can->plain_length;
    can->score *= (1 - fabs(VOW_CONS_RATIO - can->vowel_cons_ratio));
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

    for (int i = 0; i < 128; i++) { /* iterate through ASCII char 0-127  */
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
