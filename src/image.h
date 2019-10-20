#ifndef _IMAGE_H_
#define _IMAGE_H_

typedef enum primitives {
  IMAGE,
  COLOR,
  CLEAR,
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
  int charactersWritten;
} Image;

void createImage(Image* image, int width, int height);
void clearImage(Image* image, int red, int green, int blue);

#endif
