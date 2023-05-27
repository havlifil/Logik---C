/*
 * File: linkedList.c
 * Author: Filip Havlík
 * Last Modified: 27. 5. 2023
 * Description: Source file containing functions for working with strings, linked lists, and saving data to files.
 * Contact: havlifil@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <windows.h>

#include "constants.h"

/*--------------*/
/* LINKED LISTS */
/*--------------*/

typedef struct node {
    char *p_name;
    char *p_surname;
    uint16_t ID;
    uint16_t bestScore;
    struct node *p_next; // address of the next node
} NODE;

typedef struct {
    uint16_t numNodes; // number of nodes in the list
    NODE *p_first; // address of the first node
    NODE *p_last; // address of the last node
} LIST;

// create new list
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

// free whole list
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

// add one node (element) to the end of the list
NODE *addToList(LIST *p_list, char *p_name, char *p_surname, uint16_t bestScore){
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

// print whole list (debug)
void printList(LIST *p_list){
    NODE *p_actual = p_list->p_first;
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

// generate random list (debug)
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

// save list to file
void saveList(LIST *p_list){
    bubbleSortListByID(p_list);
    FILE *p_fw = fopen("logik.dat", "w");
    if(p_fw == NULL){
        printf("ERROR cannot open file");
        exit(-3);
    }
    NODE *p_actual = p_list->p_first;
    while(p_actual != NULL){
        fputs(p_actual->p_name, p_fw);
        fputc('|', p_fw);
        fputs(p_actual->p_surname, p_fw);
        fputc('|', p_fw);
        fprintf(p_fw, "%d", p_actual->bestScore);
        fputc('\n', p_fw);
        p_actual = p_actual->p_next;
    }
    fclose(p_fw);
}

// load list from file
void *loadList(LIST *p_destination){
    FILE *p_fr = fopen("logik.dat", "r");
    if(p_fr != NULL) {
        char actualChar = fgetc(p_fr);
        char name[NAMESURNAME_LENGTH];
        char surname[NAMESURNAME_LENGTH];
        char bestScore[6];
        while(actualChar != EOF){
            while(actualChar != '\n'){
                int i = 0;
                while(actualChar != '|'){
                    name[i] = actualChar;
                    actualChar = fgetc(p_fr);
                    i++;
                }
                name[i] = '\0';
                i = 0;
                actualChar = fgetc(p_fr);
                while(actualChar != '|'){
                    surname[i] = actualChar;
                    actualChar = fgetc(p_fr);
                    i++;
                }
                surname[i] = '\0';
                i = 0;
                actualChar = fgetc(p_fr);
                while(actualChar != '\n'){
                    bestScore[i] = actualChar;
                    actualChar = fgetc(p_fr);
                    i++;
                }
                bestScore[i] = '\0';
            }
            int bestScoreInt = atoi(bestScore);
            char *p_name = (char *) malloc((strlen(name)+1)*sizeof(char));
            if(p_name == NULL){
                printf("ERROR out of memory\n");
                exit(-1);
            }
            strcpy(p_name, name);
            char *p_surname = (char *) malloc((strlen(surname)+1)*sizeof(char));
            if(p_surname == NULL){
                printf("ERROR out of memory\n");
                exit(-1);
            }
            strcpy(p_surname, surname);
            addToList(p_destination, p_name, p_surname, bestScoreInt);
            actualChar = fgetc(p_fr);
        }
    }
    fclose(p_fr);
}


/*---------*/
/* STRINGS */
/*---------*/

// check if string is valid
bool validateString(char *p_string){
    if(strlen(p_string)>NAMESURNAME_LENGTH){
        return false;
    }
    char actualChar = *p_string;
    int i = 0;
    while(actualChar != '\0'){
        if((actualChar < 'A' || actualChar > 'Z') && (actualChar < 'a' || actualChar > 'z')){
            return false;
        }
        i++;
        actualChar = *(p_string+i);
    }
    return true;
}

// get string from user properly
char *getNameSurname(){
    bool valid = false;
    char buffer[1024];
    while(!valid){
        int ee = scanf(" %1023[^\n]s", buffer);
        if(ee = 0){
            printf("ERROR scanf\n");
            exit(-2);
        }
        valid = validateString(buffer);
        if(valid == false){
            printf("string is not valid");
        }
    }
    char *p_newString;
    p_newString = (char *) malloc((strlen(buffer)+1)*sizeof(char));
    if(p_newString == NULL){
        printf("ERROR out of memory\n");
        exit(-1);
    }
    strcpy(p_newString, buffer);
    return p_newString;
}

// set user (debug)
void setNewUser(LIST *p_list, uint16_t bestScore){
    int size[2];
    printf("Name: ");
    char *p_name = getNameSurname();
    printf("Surname: ");
    char *p_surname = getNameSurname();
    addToList(p_list, p_name, p_surname, bestScore);
}

// convert all letters to lower
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

// swap two neighbouring nodes
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

// sort list by ID using bubbleSort
void bubbleSortListByID(LIST *p_list){
    if(p_list->p_first != NULL){
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
}

// sort list by score using bubbleSort
void bubbleSortListByScore(LIST *p_list){
    bubbleSortListByID(p_list);
    if(p_list->p_first != NULL){
        bool swapped = true;
        NODE *p_nodeBefore=NULL;
        NODE *p_node1 = p_list->p_first;
        NODE *p_node2 = p_list->p_first->p_next;
        int j = p_list->numNodes-1;
        while(swapped==true){
            swapped = false;
            while(p_node2 != NULL){
                if(p_node1->bestScore>p_node2->bestScore){
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
}

// sort list by names
void bubbleSortListByName(LIST *p_list){
    if(p_list->p_first != NULL){
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
}

// sort list by surnames
void bubbleSortListBySurname(LIST *p_list){
    if(p_list->p_first != NULL){
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
}

/*-----*/
/* LOG */
/*-----*/

// save scoreboard info to .log file
void logScoreboard(LIST *p_list){
    FILE *p_fa = fopen("logik.log", "a");
    if(p_fa == NULL){
        printf("ERROR cannot open file");
        exit(-3);
    }
    SYSTEMTIME currentTime;
    GetLocalTime(&currentTime);
    fprintf(p_fa, "%04d-%02d-%02d %02d:%02d:%02d\n", currentTime.wYear, currentTime.wMonth, currentTime.wDay, currentTime.wHour, currentTime.wMinute, currentTime.wSecond);
    bubbleSortListByID(p_list);
    NODE *p_actual = p_list->p_first;
    while(p_actual != NULL){
        fprintf(p_fa, "%d|%s|%s|%d\n", p_actual->ID, p_actual->p_name, p_actual->p_surname, p_actual->bestScore);
        p_actual = p_actual->p_next;
    }
    fclose(p_fa);
}
