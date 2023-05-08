#include <time.h>
#include <stdbool.h>
#include "constants.h"

typedef struct{
    char combination[COMBINATION_SIZE];
    int guessedColors;
    int guessedColorsInPositions;
}COMBINATION;

COMBINATION generateCombination(int combinationSize){
    srand(time(0));
    COMBINATION combination;
    for(int i = 0; i<combinationSize; i++){
        combination.combination[i] = rand()%8;
        combination.guessedColors = -1;
        combination.guessedColorsInPositions = -1;
    }
}

COMBINATION generateBlankCombination(char *p_output, int combinationSize){
    srand(time(0));
    COMBINATION combination;
    for(int i = 0; i<combinationSize; i++){
        combination.combination[i] = PIN_NEUTRAL;
        combination.guessedColors = -1;
        combination.guessedColorsInPositions = -1;
    }
}

bool combinationIsValid(COMBINATION combination, int combinationSize){
    for(int i = 0; i<combinationSize; i++){
        if(combination.combination[i]==PIN_NEUTRAL){
            return false;
        }
    }
    return true;
}

COMBINATION checkCombination(COMBINATION rightCombination, COMBINATION combination, int combinationSize){
    combination.guessedColors = 0;
    combination.guessedColorsInPositions = 0;
    // check for pins with right color and position
    for(int i = 0; i<combinationSize; i++){
        if(combination.combination[i]==rightCombination.combination[i]){
            combination.guessedColorsInPositions++;
            combination.combination[i] = '*';
            rightCombination.combination[i] = '*';
        }
    }
    // check for pins with only right color
    for(int i = 0; i<combinationSize; i++){
        for(int x = 0; (x<combinationSize)&&(combination.combination[i]!='*'); x++){
            if(combination.combination[i]==rightCombination.combination[x]){
                combination.guessedColors++;
                combination.combination[i] = '*';
                rightCombination.combination[x] = '*';
            }
        }
    }
    return combination;
}

void printCombination(char *p_combination, int combinationSize){
    for(int i = 0; i<combinationSize; i++){
        printf("#%d ", i);
        printf("%d ", *(p_combination+i));
        switch(*(p_combination+i)){
        case PIN_RED:
            printf("red");
            break;
        case PIN_GREEN:
            printf("green");
            break;
        case PIN_BLUE:
            printf("blue");
            break;
        case PIN_YELLOW:
            printf("yellow");
            break;
        case PIN_WHITE:
            printf("white");
            break;
        case PIN_BLACK:
            printf("black");
            break;
        case PIN_GRAY:
            printf("gray");
            break;
        case PIN_MAGENTA:
            printf("magenta");
            break;
        default:
            printf("unknown");
            break;
        }
        printf("\n");
    }
}




















