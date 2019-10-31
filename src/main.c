#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "image.h"
#include "utils.h"

int main(int argc, char const* argv[]) {
  char* instructions;
  char* token;
  const char blankSpace[2] = " ";

  int i, j;
  primitives primitive;

  int** polygonPoints = NULL;
  int polygonPointsCounter = 0;
  int polygonQntPoints = 0;

  Arguments arguments;
  arguments.buffer = NULL;
  arguments.counter = 0;
  arguments.mode = false;

  Image image;
  image.matrix = NULL;
  image.image = NULL;
  // Inicializa o struct da imagem com a cor preta
  image.currentColor[0] = 0;
  image.currentColor[1] = 0;
  image.currentColor[2] = 0;

  if (argv[1] != NULL && !strcmp(argv[1], "-d")) {
    printf("DECOMPRESS MODE on image: %s\n", argv[2]);
    // TODO: Criar função para descomprimir a imagem
  } else {
    instructions = readInstructions();

    // Divide a string em tokens, que no caso são espaços em branco
    token = strtok(instructions, blankSpace);

    while (token != NULL) {
      if (arguments.mode == true) {
        arguments.buffer[arguments.counter++] = atoi(token);

        if (primitive == POLYGON_POINTS) {
          primitive = POLYGON_COORDINATES;

          polygonQntPoints = arguments.buffer[0];

          polygonPoints = (int**)calloc(polygonQntPoints, sizeof(int*));
          for (i = 0; i < polygonQntPoints; i++) {
            polygonPoints[i] = (int*)calloc(POLYGON_QTD_COORDINATES, sizeof(int));
          }

          arguments.counter = 0;
          arguments.buffer = (int*)calloc(polygonQntPoints * POLYGON_QTD_COORDINATES,
                                          sizeof(int));
        }

        // Caso encontre o último argumento:
        if (checkIfHasN(token, strlen(token)) == true) {
          switch (primitive) {
            case IMAGE:
              createImage(&image, arguments.buffer[0], arguments.buffer[1]);
              break;

            case SAVE:
              saveImage(&image, token);
              break;

            case CLEAR:
              clearImage(&image,
                         arguments.buffer[0],
                         arguments.buffer[1],
                         arguments.buffer[2]);
              break;

            case COLOR:
              setCurrentColor(&image,
                              arguments.buffer[0],
                              arguments.buffer[1],
                              arguments.buffer[2]);
              break;

            case LINE:
              drawLine(&image,
                       arguments.buffer[0],
                       arguments.buffer[1],
                       arguments.buffer[2],
                       arguments.buffer[3]);
              break;

            case CIRCLE:
              drawCircle(&image,
                         arguments.buffer[0],
                         arguments.buffer[1],
                         arguments.buffer[2]);
              break;

            case POLYGON_COORDINATES:
              for (i = 0; i < arguments.counter; i += 2) {
                polygonPoints[polygonPointsCounter][0] = arguments.buffer[i];
                polygonPoints[polygonPointsCounter][1] = arguments.buffer[i + 1];
                polygonPointsCounter += 1;
              }
              polygonPointsCounter = 0;
              drawPolygon(&image, polygonQntPoints, polygonPoints);
              break;

            case RECT:
              drawRectangle(&image,
                            arguments.buffer[0],
                            arguments.buffer[1],
                            arguments.buffer[2],
                            arguments.buffer[3]);
              break;

            case FILL:
              fillPolygon(&image, arguments.buffer[0], arguments.buffer[1]);
              break;

            default:
              break;
          }

          arguments.mode = false;
          arguments.counter = 0;
        }
      }

      // Caso o token contenha alguma diretiva
      if (strstr(token, "image") != NULL) {
        primitive = IMAGE;
        arguments.mode = true;
        arguments.buffer = (int*)calloc(2, sizeof(int));
      } else if (strstr(token, "save") != NULL) {
        primitive = SAVE;
        arguments.mode = true;
        arguments.buffer = (int*)calloc(1, sizeof(int));
      } else if (strstr(token, "clear") != NULL) {
        primitive = CLEAR;
        arguments.mode = true;
        arguments.buffer = (int*)calloc(3, sizeof(int));
      } else if (strstr(token, "color") != NULL) {
        primitive = COLOR;
        arguments.mode = true;
        arguments.buffer = (int*)calloc(3, sizeof(int));
      } else if (strstr(token, "line") != NULL) {
        primitive = LINE;
        arguments.mode = true;
        arguments.buffer = (int*)calloc(4, sizeof(int));
      } else if (strstr(token, "circle") != NULL) {
        primitive = CIRCLE;
        arguments.mode = true;
        arguments.buffer = (int*)calloc(3, sizeof(int));
      } else if (strstr(token, "polygon") != NULL) {
        primitive = POLYGON_POINTS;
        arguments.mode = true;
        arguments.buffer = (int*)calloc(1, sizeof(int));
      } else if (strstr(token, "rect") != NULL) {
        primitive = RECT;
        arguments.mode = true;
        arguments.buffer = (int*)calloc(4, sizeof(int));
      } else if (strstr(token, "fill") != NULL) {
        primitive = FILL;
        arguments.mode = true;
        arguments.buffer = (int*)calloc(2, sizeof(int));
      }

      token = strtok(NULL, blankSpace);
    }
  }

  for (i = 0; i < polygonQntPoints; i++) {
    free(polygonPoints[i]);
  }
  if (polygonPoints != NULL) {
    free(polygonPoints);
  }
  for (i = 0; i < image.rows; i++) {
    for (j = 0; j < image.columns; j++) {
      free(image.matrix[i][j]);
    }
    free(image.matrix[i]);
  }
  if (image.matrix != NULL) {
    free(image.matrix);
  }
  if (image.image != NULL) {
    free(image.image);
  }
  if (arguments.buffer != NULL) {
    free(arguments.buffer);
  }

  return 0;
}
