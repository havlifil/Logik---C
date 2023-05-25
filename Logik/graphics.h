#include <stdint.h>

#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

extern void drawRect(int x, int y, int width, int height, uint8_t color);
extern void drawCombination(int x, int y, char *p_combination, int combinationSize);
extern void drawCombinationSmall(int x, int y, char *p_combination, INFORMATIVE_PINS informativePins, int combinationSize);
extern void printScoreboard(LIST *p_list);

#endif // GRAPHICS_H_INCLUDED
