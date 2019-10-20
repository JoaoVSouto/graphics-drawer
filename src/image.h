#ifndef _IMAGE_H_
#define _IMAGE_H_

typedef enum {
  IMAGE,
  COLOR,
  CLEAR,
  RECT,
  CIRCLE,
  POLYGON,
  FILL,
  SAVE
} primitives;

typedef struct {
  char* imageFile;
  int columns;
  int rows;
  int currentColor[3];
  int charactersWritten;
} Image;

void createImage(Image* image, int width, int height);

#endif
