#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef enum primitives {
  IMAGE,
  COLOR,
  CLEAR,
  LINE,
  RECT,
  CIRCLE,
  POLYGON,
  FILL,
  SAVE
} primitives;

typedef struct Image {
  char* image;
  char*** matrix;
  int columns;
  int rows;
  int currentColor[3];
} Image;

void createImage(Image* image, int width, int height);
void clearImage(Image* image, int red, int green, int blue);
void setCurrentColor(Image* image, int red, int green, int blue);
void drawLine(Image* image, int x1, int y1, int x2, int y2);

#endif
