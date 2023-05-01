#include <time.h>
#include "constants.h"
#include "graphics.h"

typedef struct{
    int guessedColors;
    int guessedColorsInPositions;
}INFORMATIVE_PINS;

void generateCombination(char *p_output, int combinationSize){
    srand(time(0));
    for(int i = 0; i<combinationSize; i++){
        *(p_output+i) = rand()%8;
    }
}

INFORMATIVE_PINS checkCombination(char *p_rightCombination, char *p_combination, int combinationSize){
    INFORMATIVE_PINS informativePins;
    informativePins.guessedColors = 0;
    informativePins.guessedColorsInPositions = 0;
    // copy information about combinations from arrays
    char rightCombination[combinationSize];
    char combination[combinationSize];
    for(int i = 0; i<combinationSize; i++){
        rightCombination[i] = *(p_rightCombination+i);
        combination[i] = *(p_combination+i);
    }
    // check for pins with right color and position
    for(int i = 0; i<combinationSize; i++){
        if(combination[i]==rightCombination[i]){
            informativePins.guessedColorsInPositions++;
            combination[i] = '*';
            rightCombination[i] = '*';
        }
    }
    // check for pins with only right color
    for(int i = 0; i<combinationSize; i++){
        for(int x = 0; (x<combinationSize)&&(combination[i]!='*'); x++){
            if(combination[i]==rightCombination[x]){
                informativePins.guessedColors++;
                combination[i] = '*';
                rightCombination[x] = '*';
            }
        }
    }
    return informativePins;
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

void drawCombination(char *p_combination, int combinationSize){
    uint8_t color;
    for(int i = 0; i<combinationSize; i++){
        switch(*(p_combination+i)){
        case PIN_RED:
            color = COLOR_RED;
            break;
        case PIN_BLUE:
            color = COLOR_BLUE;
            break;
        case PIN_YELLOW:
            color = COLOR_YELLOW;
            break;
        case PIN_GREEN:
            color = COLOR_GREEN;
            break;
        case PIN_MAGENTA:
            color = COLOR_MAGENTA;
            break;
        case PIN_GRAY:
            color = COLOR_GRAY;
            break;
        case PIN_BLACK:
            color = COLOR_BLACK;
            break;
        case PIN_WHITE:
            color = COLOR_WHITE;
            break;
        }
        drawRect(2+(i*8)+(i*2), 2, 4, 4, color);
    }
}


















