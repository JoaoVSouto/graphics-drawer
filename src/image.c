#include "image.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARS_PER_LINE 12
#define HEADER_SIZE 20

void createImage(Image* image, int width, int height) {
  // No pior caso, por cada linha na imagem terá no máximo 12 caracteres
  int imageSize = width * height * MAX_CHARS_PER_LINE + HEADER_SIZE;
  int i, j;

  // Alocando a matriz
  image->matrix = (char***)calloc(height, sizeof(char**));
  for (i = 0; i < height; i++) {
    image->matrix[i] = (char**)calloc(width, sizeof(char*));
    for (j = 0; j < width; j++) {
      image->matrix[i][j] = (char*)calloc(MAX_CHARS_PER_LINE, sizeof(char));
    }
  }

  image->rows = height;
  image->columns = width;

  image->image = (char*)calloc(imageSize, sizeof(char));

  sprintf(image->image, "P3\n%d %d\n255\n", width, height);
}

void clearImage(Image* image, int red, int green, int blue) {
  int i, j;

  for (i = 0; i < image->rows; i++) {
    for (j = 0; j < image->columns; j++) {
      sprintf(image->matrix[i][j], "%d %d %d\n", red, green, blue);
    }
  }
}

void setCurrentColor(Image* image, int red, int green, int blue) {
  image->currentColor[0] = red;
  image->currentColor[1] = green;
  image->currentColor[2] = blue;
}

void drawLine(Image* image, int x1, int y1, int x2, int y2) {
  double coeficient = (y2 - y1) / (x2 - x1);
  int diffX = x2 - x1;
  int diffY = y2 - y1;
  // TODO: criar condições para linhas com diffX == 0 e diffY == 0

  if (diffX >= diffY && coeficient < 0) {         // Octante 08
  } else if (diffX >= diffY && coeficient > 0) {  // Octante 01
  } else if (diffX <= diffY && coeficient < 0) {  // Octante 07
  } else if (diffX <= diffY && coeficient > 0) {  // Octante 02
  }
}
