#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
    char *p_name;
    char *p_surname;
    int ID;
    int bestScore;
    struct node *p_next; // address of the next node
} NODE;

typedef struct {
    int numNodes; // number of nodes in the list
    NODE *p_first; // address of the first node
    NODE *p_last; // address of the last node
} LIST;

// creates new list
LIST *createList(){
    LIST *p_list = (LIST *) malloc(sizeof(LIST));
    if(p_list == NULL){
        printf("ERROR out of memory\n");
        exit(-1);
    }
    p_list->p_first = NULL;
    p_list->p_last = NULL;
    p_list->numNodes = 0;
    return p_list;
}

// frees whole list
void freeList(LIST *p_list){
    NODE *p_actualNode = p_list->p_first; // creates buffer node for actual node and set it to first node
    NODE *p_oldNode; // creates second buffer node for old node (node to free)
    while(p_actualNode != NULL){
        p_oldNode = p_actualNode;
        p_actualNode = p_actualNode->p_next;
        // frees dynamic values
        free(p_oldNode->p_name);
        free(p_oldNode->p_surname);
        free(p_oldNode);  // frees node
    }
    free(p_list); // frees list
}

// adds one node (element) to the end of the list
NODE *addToList(LIST *p_list, char *p_name, char *p_surname, int bestScore){
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
    p_list->numNodes++;
    // saves data to the node
    p_newNode->p_name = p_name;
    p_newNode->p_surname = p_surname;
    p_newNode->ID = p_list->numNodes;
    p_newNode->bestScore = bestScore;
    return p_newNode;
}

// prints whole list
void printList(LIST *p_list){
    NODE *p_actual;
    p_actual = p_list->p_first;
    if(p_actual == NULL){
        printf("List is empty.\n");
    } else {
        while(p_actual != NULL){
            printf("\nName: %s\n", p_actual->p_name);
            printf("Surname: %s\n", p_actual->p_surname);
            printf("ID: %d\n", p_actual->ID);
            printf("best score: %d\n", p_actual->bestScore);
            p_actual = p_actual->p_next;
        }
    }

}

// generating random list
LIST *generateRandomList(int numNodes){
    srand(time(0));
    LIST *p_randomList = createList();
    char *p_name;
    char *p_surname;
    char buffer[16];
    int length;
    for(int i = 0; i<numNodes; i++){
        length = rand()%14+1;
        for(int i = 0; i<length; i++){
            switch(rand()%2){
            case 0:
                buffer[i] = (char)(rand()%26+97);
                break;
            case 1:
                buffer[i] = (char)(rand()%26+65);
                break;
            }
        }
        buffer[length] = '\0';
        p_name = (char *) malloc((strlen(buffer)+1)*sizeof(char));
        if(p_name == NULL){
        printf("ERROR out of memory\n");
        exit(-1);
        }
        strcpy(p_name, buffer);
        length = rand()%14+1;
        for(int i = 0; i<length; i++){
            switch(rand()%2){
            case 0:
                buffer[i] = (char)(rand()%26+97);
                break;
            case 1:
                buffer[i] = (char)(rand()%26+65);
                break;
            }
        }
        buffer[length] = '\0';
        p_surname = (char *) malloc((strlen(buffer)+1)*sizeof(char));
        if(p_surname == NULL){
            printf("ERROR out of memory\n");
            exit(-1);
        }
        strcpy(p_surname, buffer);
        addToList(p_randomList, p_name, p_surname, 0);
    }
    return p_randomList;
}

/*---------*/
/* STRINGS */
/*---------*/

// gets string from user properly
char *getString(){
    char buffer[1024];
    char *p_newString;
    int ee = scanf(" %1023[^\n]s", buffer);
    if(ee = NULL){
        printf("ERROR scanf\n");
        exit(-2);
    }
    p_newString = (char *) malloc((strlen(buffer)+1)*sizeof(char));
    if(p_newString == NULL){
        printf("ERROR out of memory\n");
        exit(-1);
    }
    strcpy(p_newString, buffer);
    return p_newString;
}

void toLower(char *p_string){
    for(int i = 0; p_string[i]!='\0'; i++){
        if(((int)*(p_string+i)>64)&&((int)*(p_string+i)<91)){
            *(p_string+i) = *(p_string+i)+32;
        }
    }
}

/*--------------------*/
/* SORTING ALGORITHMS */
/*--------------------*/

// swaps two neighbouring nodes
void swapNodes(LIST *p_list, NODE *p_nodeBefore, NODE *p_node1, NODE *p_node2){
    NODE *p_holder;
    if(p_node1 == p_list->p_first && p_node2 == p_list->p_last){
        p_node1->p_next = NULL;
        p_node2->p_next = p_list->p_first;
        p_holder = p_list->p_first;
        p_list->p_first = p_list->p_last;
        p_list->p_last = p_holder;
    } else if(p_node1 == p_list->p_first) {
        p_holder = p_node1->p_next;
        p_node1->p_next = p_node2->p_next;
        p_node2->p_next = p_list->p_first;
        p_list->p_first = p_holder;
    } else if(p_node2 == p_list->p_last){
        p_list->p_last = p_nodeBefore->p_next;
        p_holder = p_nodeBefore->p_next;
        p_nodeBefore->p_next = p_node1->p_next;
        p_node1->p_next = p_node2->p_next;
        p_node2->p_next = p_holder;
    } else {
        p_holder = p_nodeBefore->p_next;
        p_nodeBefore->p_next = p_node1->p_next;
        p_node1->p_next = p_node2->p_next;
        p_node2->p_next = p_holder;
    }
}


// sorts list by ID using bubbleSort
void bubbleSortListByID(LIST *p_list){
    bool swapped = true;
    NODE *p_nodeBefore=NULL;
    NODE *p_node1 = p_list->p_first;
    NODE *p_node2 = p_list->p_first->p_next;
    int j = p_list->numNodes-1;
    while(swapped==true){
        swapped = false;
        while(p_node2 != NULL){
            if(p_node1->ID>p_node2->ID){
                swapNodes(p_list, p_nodeBefore, p_node1, p_node2);
                swapped = true;
            }
            p_nodeBefore = p_node1;
            p_node1 = p_node2;
            p_node2 = p_node2->p_next;
        }
        p_node1 = p_list->p_first;
        p_node2 = p_list->p_first->p_next;
        j--;
    }
}

void bubbleSortListByName(LIST *p_list){
    bool swapped = true;
    NODE *p_nodeBefore=NULL;
    NODE *p_node1 = p_list->p_first;
    NODE *p_node2 = p_list->p_first->p_next;
    int j = p_list->numNodes-1;
    while(swapped==true){
        swapped = false;
        while(p_node2 != NULL){
            char string1[strlen(p_node1->p_name)+1], string2[strlen(p_node2->p_name)+1];
            strcpy(string1, p_node1->p_name);
            strcpy(string2, p_node2->p_name);
            toLower(&string1[0]);
            toLower(&string2[0]);
            if(strcmp(string1, string2)>0){
                swapNodes(p_list, p_nodeBefore, p_node1, p_node2);
                swapped = true;
            }
            p_nodeBefore = p_node1;
            p_node1 = p_node2;
            p_node2 = p_node2->p_next;
        }
        p_node1 = p_list->p_first;
        p_node2 = p_list->p_first->p_next;
        j--;
    }
}

void bubbleSortListBySurname(LIST *p_list){
    bool swapped = true;
    NODE *p_nodeBefore=NULL;
    NODE *p_node1 = p_list->p_first;
    NODE *p_node2 = p_list->p_first->p_next;
    int j = p_list->numNodes-1;
    while(swapped==true){
        swapped = false;
        while(p_node2 != NULL){
            char string1[strlen(p_node1->p_surname)+1], string2[strlen(p_node2->p_surname)+1];
            strcpy(string1, p_node1->p_surname);
            strcpy(string2, p_node2->p_surname);
            toLower(&string1[0]);
            toLower(&string2[0]);
            if(strcmp(string1, string2)>0){
                swapNodes(p_list, p_nodeBefore, p_node1, p_node2);
                swapped = true;
            }
            p_nodeBefore = p_node1;
            p_node1 = p_node2;
            p_node2 = p_node2->p_next;
        }
        p_node1 = p_list->p_first;
        p_node2 = p_list->p_first->p_next;
        j--;
    }
}










