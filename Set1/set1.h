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
* DATA STRUCTURES
*******************************************************************************/

/* struct to store information about plaintext to score it */
typedef struct _candidate {
    char    *ciphertext;
    char    *plaintext;
    unsigned long     plain_length;
    unsigned long     num_vowels;
    unsigned long     num_consanants;
    double  vowel_cons_ratio;
    double  letter_length_ratio;
    double  score;
} Candidate;


/*******************************************************************************
* FUNCTIONS
*******************************************************************************/

int getHexInt(char c);
char getHexChar(int num);
char *hexString_to_base64String(char *input);
char *fixed_xor(char *buf1, char *buf2);
Candidate *createCandidateStruct(char *input);
void analyzeCandidate(Candidate *can);


#endif
