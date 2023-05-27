/*
 * File: logik.h
 * Author: Filip Havlík
 * Last Modified: 27. 5. 2023
 * Description: Header file containing function declaration for logik.c.
 * Contact: havlifil@gmail.com
 */

#include <stdbool.h>

#ifndef LOGIK_H_INCLUDED
#define LOGIK_H_INCLUDED

typedef struct{
    int guessedColors;
    int guessedColorsInPositions;
}INFORMATIVE_PINS;

extern void generateCombination(char *p_output, int combinationSize);
extern void generateBlankCombination(char *p_output, int combinationSize);
extern INFORMATIVE_PINS checkCombination(char *p_rightCombination, char *p_combination, int combinationSize);
extern void printCombination(char *p_combination, int combinationSize);
extern bool combinationIsValid(char *p_combination, int combinationSize);

#endif // LOGIK_H_INCLUDED
