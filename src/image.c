#include "image.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARS_PER_LINE 12
#define HEADER_SIZE 20

void createImage(Image* image, int width, int height) {
  // No pior caso, por cada linha na imagem terá no máximo 12 caracteres
  int imageSize = width * height * MAX_CHARS_PER_LINE + HEADER_SIZE;
  image->imageFile = (char*)calloc(imageSize, sizeof(char));

  image->charactersWritten = sprintf(image->imageFile,
                                     "P3\n%d %d\n255\n", width, height);
}
