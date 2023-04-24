#include <stdio.h>

typedef struct node {
    char *p_nickname; // nickname saved in the node
    struct node *p_next; // address of the next node
} NODE;

typedef struct {
    int numNodes; // number of nodes in the list
    NODE *p_first; // address of the first node
    NODE *p_last; // address of the last node
} LIST;

LIST *createList(){
    LIST *p_list = (LIST *) malloc(sizeof(LIST));
    if(p_list == NULL){
        printf("ERROR out of memory\n");
        exit(-1);
    }
    p_list->p_first = NULL;
    p_list->p_last = NULL;
    return p_list;
}

void freeList(LIST *p_list){
    NODE *p_actualNode = p_list->p_first; // creates buffer node for actual node and set it to first node
    NODE *p_oldNode; // creates second buffer node for old node (node to free)
    while(p_actualNode != NULL){
        p_oldNode = p_actualNode;
        p_actualNode = p_actualNode->p_next;
        free(p_oldNode->p_nickname); // free dynamic value in node
        free(p_oldNode);  // free node
    }
    free(p_list); // free list
}

NODE *addToList(LIST *p_list, char *p_nickname){
    NODE *p_newNode;
    p_newNode = (NODE *) malloc(sizeof(NODE));
    if(p_newNode == NULL){
        printf("ERROR out of memory\n");
        exit(-1);
    }
    p_newNode->p_next = NULL; // sets next node to NULL
    if(p_list->p_last != NULL){ // if list is not empty
        p_list->p_last->p_next = p_newNode; // connect new node behind last node
        p_list->p_last = p_newNode; // set last node to new node
    } else { // list is empty
        p_list->p_first = p_newNode;
        p_list->p_last = p_newNode;
    }
    p_newNode->p_nickname = p_nickname;
    p_list->numNodes++;
    return p_newNode;
}
