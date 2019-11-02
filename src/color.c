#include "color.h"

void setCurrentColor(Image* image, int red, int green, int blue) {
  image->currentColor[0] = red;
  image->currentColor[1] = green;
  image->currentColor[2] = blue;
}

void fillPolygon(Image* image, int x, int y) {
  char targetColor[MAX_CHARS_PER_LINE],
      replacementColor[MAX_CHARS_PER_LINE];

  strcpy(targetColor, image->matrix[y][x]);
  sprintf(replacementColor, "%d %d %d\n", image->currentColor[0],
          image->currentColor[1],
          image->currentColor[2]);

  floodFill(image, x, y, targetColor, replacementColor);
}

// algoritmo baseado no https://en.wikipedia.org/wiki/Flood_fill
void floodFill(Image* image, int x, int y, char targetColor[], char replacementColor[]) {
  if (!strcmp(targetColor, replacementColor)) return;

  int rgb[3];
  sscanf(targetColor, "%d %d %d\n", &rgb[0], &rgb[1], &rgb[2]);
  if (isColorDiffFromPixel(image, rgb, x, y)) return;

  putPixel(image, x, y);
  // Para o sul
  floodFill(image, x, y + 1, targetColor, replacementColor);
  // Para o norte
  floodFill(image, x, y - 1, targetColor, replacementColor);
  // Para o oeste
  floodFill(image, x - 1, y, targetColor, replacementColor);
  // Para o leste
  floodFill(image, x + 1, y, targetColor, replacementColor);
}

bool isColorDiffFromPixel(Image* image, int rgb[], int x, int y) {
  bool isDifferent = false;
  char pixelString[MAX_CHARS_PER_LINE];
  char rgbString[MAX_CHARS_PER_LINE];

  if (x < 0 || y < 0 || x >= image->columns || y >= image->rows) {
    return true;
  }

  strcpy(pixelString, image->matrix[y][x]);
  sprintf(rgbString, "%d %d %d\n", rgb[0], rgb[1], rgb[2]);

  if (strcmp(pixelString, rgbString)) {
    isDifferent = true;
  }

  return isDifferent;
}
