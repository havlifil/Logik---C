#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#include "conio2.h"
#include "logik.h"
#include "linkedList.h"
#include "constants.h"

// gets command line width
int getCommandLineWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}

// gets command line height
int getCommandLineHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return rows;
}

// sets all colors to default and places cursor to 1,1
void setDefaultGraphics(){
    textbackground(0);
    textcolor(15);
    gotoxy(1,1);
}

// draws rectangle from x, y with current width and height
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

// SCREEN GAME

// draws combination
void drawCombination(int x, int y, char *p_combination, int combinationSize){
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
}

// draws smaller combination with including informative pins
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

// SCREEN SCOREBOARD

void printScoreboard(LIST *p_list){
    setDefaultGraphics();
    bubbleSortListByID(p_list);
    NODE *p_actual = p_list->p_first;
    drawRect(1, 1, 29, 3, COLOR_WHITE);
    textbackground(COLOR_BLACK);
    textcolor(COLOR_WHITE);
    gotoxy(2, 2);
    printf("ID   ");
    gotoxy(8, 2);
    printf("NAME               ");
    gotoxy(28, 2);
    printf("SURNAME            ");
    gotoxy(48, 2);
    printf("BESTSCORE");
    int row = 1;
    while(p_actual != NULL){
        gotoxy(2, (row*2)+2);
        printf("%d", p_actual->ID);
        gotoxy(8, (row*2)+2);
        printf("%s", p_actual->p_name);
        gotoxy(28, (row*2)+2);
        printf("%s", p_actual->p_surname);
        gotoxy(48, (row*2)+2);
        printf("%d", p_actual->bestScore);
        p_actual = p_actual->p_next;
        row++;
    }
    /*bubbleSortListByName(p_list);
    p_actual = p_list->p_first;
    //printf("By name:\n");
    while(p_actual != NULL){
        printf("ID: %d NAME: %s SURNAME: %s BESTSCORE: %d\n", p_actual->ID, p_actual->p_name, p_actual->p_surname, p_actual->bestScore);
        p_actual = p_actual->p_next;
    }
    bubbleSortListBySurname(p_list);
    p_actual = p_list->p_first;
    //printf("By surname:\n");
    while(p_actual != NULL){
        printf("ID: %d NAME: %s SURNAME: %s BESTSCORE: %d\n", p_actual->ID, p_actual->p_name, p_actual->p_surname, p_actual->bestScore);
        p_actual = p_actual->p_next;
    }*/
}
