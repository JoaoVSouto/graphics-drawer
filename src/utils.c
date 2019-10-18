#include "utils.h"

void clearBuffer(int buffer[], int size) {
  int i;

  for (i = 0; i < size; i++) {
    buffer[i] = 0;
  }
}

bool checkIfHasN(char* string, unsigned int stringLen) {
  unsigned int i;
  bool hasN = false;

  for (i = 0; i < stringLen; i++) {
    if (string[i] == '\n') {
      hasN = true;
      break;
    }
  }

  return hasN;
}
