#include "image.h"

void createImage(Image* image, int width, int height) {
  // No pior caso, por cada linha na imagem terá no máximo 12 caracteres
  long imageSize = width * height * MAX_CHARS_PER_LINE + HEADER_SIZE;
  int i, j;

  image->size = imageSize;

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

  image->image = (char*)malloc(imageSize);

  image->charsWritten = sprintf(image->image, "P3\n%d %d\n255\n", width, height);
}

void clearImage(Image* image, int red, int green, int blue) {
  int i, j;

  for (i = 0; i < image->rows; i++) {
    for (j = 0; j < image->columns; j++) {
      sprintf(image->matrix[i][j], "%d %d %d\n", red, green, blue);
    }
  }
}

/*
  Suponha uma figura 600x400, os pixels estão dispostos da seguinte forma:
  (0, 0)  |------------------------------| (600, 0)
          |                              |
          |                              |
          |                              |
          |                              |
  (0,400) |------------------------------| (600, 400)
*/

void drawLine(Image* image, int x1, int y1, int x2, int y2) {
  const int diffX = x2 - x1;
  const int diffY = y2 - y1;
  double slope, error = 0.0;
  if (abs(diffX) >= abs(diffY)) {
    slope = !diffX ? 0 : (double)diffY / diffX;
  } else {
    slope = !diffY ? 0 : (double)diffX / diffY;
  }
  int currentX, currentY, i;

  // Caso Δx ou Δy sejam 0 => linha reta vertical ou horizontal
  if (!slope) {
    if (!diffX) {  // reta vertical
      swapIfBigger(&y2, &y1);

      // Caso ultrapasse o limite da imagem
      if (y2 >= image->rows) {
        y2 = image->rows - 1;
      }

      if (x1 >= image->columns) {
        x1 = image->columns - 1;
      }

      for (i = y1; i < y2; i++) {
        putPixel(image, x1, i);
      }
    } else {  // reta horizontal
      swapIfBigger(&x2, &x1);

      if (y1 >= image->rows) {
        y1 = image->rows - 1;
      }

      if (x2 >= image->columns) {
        x2 = image->columns - 1;
      }

      for (i = x1; i < x2; i++) {
        putPixel(image, i, y1);
      }
    }
  } else {
    currentX = (x1 - 1) < 0 ? 0 : (x1 - 1);
    currentY = (y1 - 1) < 0 ? 0 : (y1 - 1);

    if (abs(diffX) >= abs(diffY) && slope < 0) {  // Octante 01 => reta de baixo pra cima
      // Caso caia nessa condição, ela troca as coordenadas.
      // Isso acontece porque a reta estava escrita no Octante 06
      // que é o inverso do Octante 01, logo a lógica é a mesma.
      if (swapIfBigger(&x2, &x1) == true) {
        swapNumbers(&y1, &y2);
        currentY = (y1 - 1) < 0 ? 0 : (y1 - 1);
      }

      for (currentX = x1; currentX < x2; currentX++) {
        putPixel(image, currentX, currentY);
        error += slope;
        if (error <= -0.5) {
          currentY -= 1;
          if (currentY < 0) {
            currentY = 0;
          }
          error += 1;
        }
      }
    } else if (abs(diffX) >= abs(diffY) && slope > 0) {  // Octante 08 => reta de cima pra baixo
      if (swapIfBigger(&x2, &x1) == true) {
        swapNumbers(&y1, &y2);
        currentY = (y1 - 1) < 0 ? 0 : (y1 - 1);
      }

      for (currentX = x1; currentX < x2; currentX++) {
        putPixel(image, currentX, currentY);
        error += slope;
        if (error >= 0.5) {
          currentY += 1;
          if (currentY >= image->rows) {
            currentY = image->rows - 1;
          }
          error -= 1;
        }
      }
    } else if (abs(diffX) <= abs(diffY) && slope < 0) {  // Octante 02 => reta de baixo pra cima
      if (swapIfBigger(&y1, &y2) == true) {
        swapNumbers(&x1, &x2);
        currentX = (x1 - 1) < 0 ? 0 : (x1 - 1);
      }

      for (currentY = y1 - 1; currentY > y2; currentY--) {
        putPixel(image, currentX, currentY);
        error += slope;
        if (error <= -0.5) {
          currentX += 1;
          if (currentX >= image->columns) {
            currentX = image->columns - 1;
          }
          error += 1;
        }
      }
    } else if (abs(diffX) <= abs(diffY) && slope > 0) {  // Octante 07 => reta de cima pra baixo
      if (swapIfBigger(&y2, &y1) == true) {
        swapNumbers(&x1, &x2);
        currentX = (x1 - 1) < 0 ? 0 : (x1 - 1);
      }

      for (currentY = y1; currentY < y2; currentY++) {
        putPixel(image, currentX, currentY);
        error += slope;
        if (error >= 0.5) {
          currentX += 1;
          if (currentX >= image->columns) {
            currentX = image->columns - 1;
          }
          error -= 1;
        }
      }
    }
  }
}

// baseado no algoritmo do https://iq.opengenus.org/bresenhams-circle-drawing-algorithm/
void drawCircle(Image* image, int xC, int yC, int radius) {
  // (xC, yC) indica o ponto central do círculo
  int currentX = 0,
      currentY = radius,
      decisionParam = 3 - (2 * radius);

  displayCircle(image, xC, yC, currentX, currentY);

  while (currentY >= currentX) {
    currentX += 1;

    if (decisionParam > 0) {
      currentY -= 1;
      decisionParam += 4 * (currentX - currentY) + 10;
    } else {
      decisionParam += 4 * currentX + 6;
    }

    displayCircle(image, xC, yC, currentX, currentY);
  }
}

void displayCircle(Image* image, int xC, int yC, int x, int y) {
  // Condicionais são realizadas para que caso o círculo seja desenhado
  // no extremo da imagem, seja impedido de gerar segmentation fault
  if (xC + x >= 0 && xC + x < image->columns && yC + y >= 0 && yC + y < image->rows) {
    putPixel(image, xC + x, yC + y);  // Octante 1
  }
  if (xC - x >= 0 && xC - x < image->columns && yC + y >= 0 && yC + y < image->rows) {
    putPixel(image, xC - x, yC + y);  // Octante 4
  }
  if (xC + x >= 0 && xC + x < image->columns && yC - y >= 0 && yC - y < image->rows) {
    putPixel(image, xC + x, yC - y);  // Octante 8
  }
  if (xC - x >= 0 && xC - x < image->columns && yC - y >= 0 && yC - y < image->rows) {
    putPixel(image, xC - x, yC - y);  // Octante 5
  }
  if (xC + y >= 0 && xC + y < image->columns && yC + x >= 0 && yC + x < image->rows) {
    putPixel(image, xC + y, yC + x);  // Octante 2
  }
  if (xC - y >= 0 && xC - y < image->columns && yC + x >= 0 && yC + x < image->rows) {
    putPixel(image, xC - y, yC + x);  // Octante 3
  }
  if (xC + y >= 0 && xC + y < image->columns && yC - x >= 0 && yC - x < image->rows) {
    putPixel(image, xC + y, yC - x);  // Octante 7
  }
  if (xC - y >= 0 && xC - y < image->columns && yC - x >= 0 && yC - x < image->rows) {
    putPixel(image, xC - y, yC - x);  // Octante 6
  }
}

void drawPolygon(Image* image, int polygonQntPoints, int** polygonPoints) {
  int previousPoint[2], currentPoint[2];
  int polygonPointsRemover = 0;

  if (polygonQntPoints > 2) {
    // Desenhando a linha que liga o primeiro ponto ao último
    drawLine(image,
             polygonPoints[0][0],
             polygonPoints[0][1],
             polygonPoints[polygonQntPoints - 1][0],
             polygonPoints[polygonQntPoints - 1][1]);
  }

  if (polygonQntPoints > 0) {
    previousPoint[0] = polygonPoints[polygonPointsRemover][0];
    previousPoint[1] = polygonPoints[polygonPointsRemover++][1];
    polygonQntPoints -= 1;
  }

  while (polygonQntPoints > 0) {
    currentPoint[0] = polygonPoints[polygonPointsRemover][0];
    currentPoint[1] = polygonPoints[polygonPointsRemover++][1];
    polygonQntPoints -= 1;

    drawLine(image, previousPoint[0], previousPoint[1], currentPoint[0], currentPoint[1]);

    previousPoint[0] = currentPoint[0];
    previousPoint[1] = currentPoint[1];
  }
}

void drawRectangle(Image* image, int x1, int y1, int x2, int y2) {
  int height, width;

  // Assegura que a coordenada mais a esquerda sempre ficará no x1
  if (swapIfBigger(&x2, &x1) == true) {
    swapNumbers(&y2, &y1);
  }

  height = y2 - y1;
  width = x2 - x1;

  // desenhando linha vertical esquerda
  drawLine(image, x1, y1, x1, y1 + height);
  // desenhando linha horizontal de baixo
  drawLine(image, x1, y1, x1 + width, y1);
  // desenhando linha vertical direita
  drawLine(image, x1 + width, y1, x2, y2);
  // desenhando linha horizontal de cima
  drawLine(image, x1, y1 + height, x2, y2);
}

void putPixel(Image* image, int x, int y) {
  sprintf(image->matrix[y][x], "%d %d %d\n",
          image->currentColor[0],
          image->currentColor[1],
          image->currentColor[2]);
}
