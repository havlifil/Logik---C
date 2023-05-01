#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conio2.h"
#include "constants.h"
#include "logik.h"
#include "linkedList.h"
#include "graphics.h"

void setNewUser(LIST *p_list){
    printf("Name: ");
    char *p_name = getString();
    printf("Surname: ");
    char *p_surname = getString();
    addToList(p_list, p_name, p_surname);
}

int main()
{
    char combination[COMBINATION_SIZE];
    generateCombination(&combination, COMBINATION_SIZE);
    drawRect(1,1,30,7,6);
    drawCombination(&combination, COMBINATION_SIZE);
    textbackground(0);
    return 0;
}
