#include <stdint.h>
#include <stdio.h>

#include "conio2.h"
#include "logik.h"
#include "constants.h"

void drawRect(int x, int y, int width, int height, uint8_t color){
    textbackground(color);
    for(int i = 0; i<height; i++){
        gotoxy(x,y+i);
        for(int x = 0; x<width; x++){
            printf("  ");
        }
    }
}

/*---------*/
/* SCREENS */
/*---------*/

void drawCombination(int x, int y, char *p_combination, INFORMATIVE_PINS informativePins, int combinationSize){
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
        case PIN_NEUTRAL:
            color = COLOR_NEUTRAL;
            break;
        }
        drawRect(x+(i*8)+(i*2), y, 4, 4, color);
    }
    if(informativePins.guessedColorsInPositions !=0){
        for(int i = 0; i<informativePins.guessedColorsInPositions; i++){
            drawRect(x+(i*2)+i, y+5, 1, 1, COLOR_INFO_COLOR_IN_POSITION);
        }
    }
    if(informativePins.guessedColors !=0){
        for(int i = 0; i<informativePins.guessedColors; i++){
            drawRect(x+(informativePins.guessedColorsInPositions*3)+(i*2)+i, y+5, 1, 1, COLOR_INFO_COLOR);
        }
    }
}

void drawCombinationSmall(int x, int y, char *p_combination, INFORMATIVE_PINS informativePins, int combinationSize){
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
        case PIN_NEUTRAL:
            color = COLOR_NEUTRAL;
            break;
        }
        drawRect(x+(i*4)+i, y, 2, 2, color);
    }
    if(informativePins.guessedColorsInPositions !=0){
        for(int i = 0; i<informativePins.guessedColorsInPositions; i++){
            drawRect(x+(i*2)+i, y+3, 1, 1, COLOR_INFO_COLOR_IN_POSITION);
        }
    }
    if(informativePins.guessedColors !=0){
        for(int i = 0; i<informativePins.guessedColors; i++){
            drawRect(x+(informativePins.guessedColorsInPositions*3)+(i*2)+i, y+3, 1, 1, COLOR_INFO_COLOR);
        }
    }
}
