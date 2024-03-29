#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/utils.h"

#define MAX_CHARS_PER_LINE 12
#define HEADER_SIZE 20
#define POLYGON_QTD_COORDINATES 2

typedef enum primitives {
  IMAGE,
  COLOR,
  CLEAR,
  LINE,
  RECT,
  CIRCLE,
  POLYGON_POINTS,
  POLYGON_COORDINATES,
  FILL,
  SAVE
} primitives;

typedef struct Image {
  char* image;
  char*** matrix;
  int columns,
      rows,
      currentColor[3];
  long size,
      charsWritten;
} Image;

void createImage(Image* image, int width, int height);
void drawLine(Image* image, int x1, int y1, int x2, int y2);
void drawCircle(Image* image, int xC, int yC, int radius);
void displayCircle(Image* image, int xC, int yC, int x, int y);
void drawPolygon(Image* image, int polygonQntPoints, int** polygonPoints);
void drawRectangle(Image* image, int x1, int y1, int x2, int y2);
void putPixel(Image* image, int x, int y);

#endif
