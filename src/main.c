#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "image.h"

int main() {
  char* instructions = readInstructions();
  char* token;
  const char blankSpace[2] = " ";
  // TODO: criar struct de arguments
  int i, argumentsBuffer[7] = {0}, argumentsCounter = 0, argumentMode = 0;
  enum primitives primitive;

  // Divide a string em tokens, que no caso são espaços em branco
  token = strtok(instructions, blankSpace);

  while (token != NULL) {
    if (argumentMode) {
      argumentsBuffer[argumentsCounter++] = atoi(token);

      // Caso encontre o último argumento:
      for (i = 0; i < strlen(token); i++) {
        if (token[i] == '\n') {
          if (primitive == IMAGE) {
            createImage(argumentsBuffer[0], argumentsBuffer[1]);
          }

          argumentMode = 0;
          argumentsCounter = 0;
        }
      }
    }

    if (!strcmp(token, "image")) {
      primitive = IMAGE;
      argumentMode = 1;
    }

    token = strtok(NULL, blankSpace);
  }

  return 0;
}
