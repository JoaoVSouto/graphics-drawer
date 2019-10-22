#include "image.h"

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

/*
  Suponha uma figura 600x400
  (0, 0)  |------------------------------| (600, 0)
          |                              |
          |                              |
          |                              |
          |                              |
  (0,400) |------------------------------| (600, 400)
*/

void drawLine(Image* image, int x1, int y1, int x2, int y2) {
  int i, j;
  int diffX = x2 - x1;
  int diffY = y2 - y1;
  int currentX, currentY;
  double coefficient = !diffX ? 0 : (double)diffY / diffX;
  double accumulator = 0;

  // Caso Δx ou Δy sejam 0 => linha reta vertical ou horizontal
  if (!coefficient) {
    if (!diffX) {  // reta vertical
      swapIfBigger(&y2, &y1);
      for (i = y1; i < y2; i++) {
        sprintf(image->matrix[i][x1], "%d %d %d\n",
                image->currentColor[0],
                image->currentColor[1],
                image->currentColor[2]);
      }
    } else {  // reta horizontal
      swapIfBigger(&x2, &x1);
      for (i = x1; i < x2; i++) {
        sprintf(image->matrix[y1][i], "%d %d %d\n",
                image->currentColor[0],
                image->currentColor[1],
                image->currentColor[2]);
      }
    }
  } else {
    currentX = (x1 - 1) < 0 ? 0 : (x1 - 1);
    currentY = (y1 - 1) < 0 ? 0 : (y1 - 1);
    if (diffX >= diffY && coefficient < 0) {  // Octante 01 => reta de baixo pra cima
      while (currentX <= x2 && currentY >= y2) {
        sprintf(image->matrix[currentY][currentX], "%d %d %d\n",
                image->currentColor[0],
                image->currentColor[1],
                image->currentColor[2]);
        currentX += 1;
        accumulator += coefficient;
        if (accumulator <= -1) {
          currentY -= 1;
          accumulator = 0;
        }
      }                                              // TODO: refletir esse caso para os outros
    } else if (diffX >= diffY && coefficient > 0) {  // Octante 08
    } else if (diffX <= diffY && coefficient < 0) {  // Octante 02
    } else if (diffX <= diffY && coefficient > 0) {  // Octante 07
    }
  }
}
