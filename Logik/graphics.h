#include <stdint.h>

#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

extern void drawRect(int x, int y, int width, int height, uint8_t color);
extern void drawCombination(int x, int y, char *p_combination, INFORMATIVE_PINS informativePins, int combinationSize);
extern void drawCombination(int x, int y, char *p_combination, INFORMATIVE_PINS informativePins, int combinationSize);

#endif // GRAPHICS_H_INCLUDED
