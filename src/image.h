#ifndef _IMAGE_H_
#define _IMAGE_H_

enum primitives {
  IMAGE,
  COLOR,
  CLEAR,
  RECT,
  CIRCLE,
  POLYGON,
  FILL,
  SAVE
};

void createImage(int width, int height);

#endif
