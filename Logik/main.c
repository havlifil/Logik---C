#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "logik.h"
#include "linkedList.h"

void setNewUser(LIST *p_list){
    printf("Name: ");
    char *p_name = getString();
    printf("Surname: ");
    char *p_surname = getString();
    addToList(p_list, p_name, p_surname);
}

int main()
{
    /*// generating random color combination and comparing it to another combination + printing results
    INFORMATIVE_PINS actualInformativePins;
    char combination[COMBINATION_SIZE];
    char actualCombination[COMBINATION_SIZE] = {PIN_BLUE, PIN_BLACK, PIN_BLACK, PIN_WHITE, PIN_GREEN};
    printf("Right combination:\n");
    getCombination(&combination[0], COMBINATION_SIZE);
    printCombination(&combination[0], COMBINATION_SIZE);
    printf("Guessed combination:\n");
    printCombination(&actualCombination[0], COMBINATION_SIZE);
    actualInformativePins = checkCombination(&combination[0], &actualCombination[0], COMBINATION_SIZE);
    printf("guessed positions+colors: %d\nguessed colors: %d\n", actualInformativePins.guessedColorsInPositions, actualInformativePins.guessedColors);*/

    /*// creating, setting and printing user list
    LIST *p_userList = createList();
    p_userList->numNodes = 0;
    for(int i = 0; i<3; i++){
        setNewUser(p_userList);
    }
    printList(p_userList);
    freeList(p_userList);*/

    // generating and printing random list
    LIST *p_userList = generateRandomList(3);
    printList(p_userList);
    //freeList(p_userList);
    //swapping nodes
    swap(p_userList, p_userList->p_first, p_userList->p_last);
    //swap(p_userList, p_userList->p_first, p_userList->p_last);
    printf("_____________________\n");
    printList(p_userList);
    freeList(p_userList);


    /*// changing colors
    printf("\033[34m\n");
    printf("ahoj");
    printf("\033[0m\n");
    printf("ahoj");*/
    return 0;
}
