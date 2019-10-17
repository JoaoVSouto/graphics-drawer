#include <stdio.h>
#include <string.h>
#include "file.h"
#include "image.h"

int main() {
  char* instructions = readInstructions();
  char* token;
  const char blankSpace[2] = " ";
  int i, *argumentsBuffer;
  enum primitives primitive;

  // Divide a string em tokens, que no caso são espaços em branco
  token = strtok(instructions, blankSpace);

  while (token != NULL) {
    if (!strcmp(token, "image")) {
      primitive = IMAGE;
    }

    for (i = 0; i < strlen(token); i++) {
      if (token[i] == '\n') {
        printf("new linw!\n");
      }
    }

    token = strtok(NULL, blankSpace);
  }

  return 0;
}
