/*
Utility functions to created linked lists
*/

#include <stdlib.h>
#include "linked_list.h"
#include "set1.h"


/*******************************************************************************
* FUNCTIONS
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
