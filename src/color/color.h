#ifndef _COLOR_H_
#define _COLOR_H_

#include "../image/image.h"
#include "../utils/utils.h"

void setCurrentColor(Image* image, int red, int green, int blue);
void fillPolygon(Image* image, int x, int y);
void floodFill(Image* image, int x, int y, char targetColor[], char replacementColor[]);
bool isColorDiffFromPixel(Image* image, int rgb[], int x, int y);

#endif
