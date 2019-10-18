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

void createImage(int width, int height);

#endif
