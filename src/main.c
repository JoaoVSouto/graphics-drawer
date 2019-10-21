#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "image.h"
#include "utils.h"

int main() {
  char* instructions = readInstructions();
  char* token;
  const char blankSpace[2] = " ";

  int i, j;
  primitives primitive;

  Arguments arguments;
  arguments.counter = 0;
  arguments.mode = false;

  // Inicializa o struct da imagem com a cor preta
  Image image;
  image.currentColor[0] = 0;
  image.currentColor[1] = 0;
  image.currentColor[2] = 0;

  // Divide a string em tokens, que no caso são espaços em branco
  token = strtok(instructions, blankSpace);

  while (token != NULL) {
    if (arguments.mode == true) {
      arguments.buffer[arguments.counter++] = atoi(token);

      // Caso encontre o último argumento:
      if (checkIfHasN(token, strlen(token)) == true) {
        if (primitive == IMAGE) {
          createImage(&image, arguments.buffer[0], arguments.buffer[1]);
        } else if (primitive == SAVE) {
          saveImage(&image, token);
        } else if (primitive == CLEAR) {
          clearImage(&image,
                     arguments.buffer[0],
                     arguments.buffer[1],
                     arguments.buffer[2]);
        } else if (primitive == COLOR) {
          setCurrentColor(&image,
                          arguments.buffer[0],
                          arguments.buffer[1],
                          arguments.buffer[2]);
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
    }

    token = strtok(NULL, blankSpace);
  }

  for (i = 0; i < image.rows; i++) {
    for (j = 0; j < image.columns; j++) {
      free(image.matrix[i][j]);
    }
    free(image.matrix[i]);
  }
  free(image.matrix);
  free(image.image);
  free(arguments.buffer);

  return 0;
}
