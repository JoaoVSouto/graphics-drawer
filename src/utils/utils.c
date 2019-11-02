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

void swapNumbers(int* x, int* y) {
  int aux;

  aux = *x;
  *x = *y;
  *y = aux;
}

bool swapIfBigger(int* x, int* y) {
  int aux;
  bool changed = false;

  if (*x < *y) {
    aux = *x;
    *x = *y;
    *y = aux;
    changed = true;
  }

  return changed;
}

void removeLastChar(char* string) {
  int i;
  char* newString;

  newString = (char*)calloc(strlen(string) - 1, sizeof(char));

  for (i = 0; i < strlen(string) - 1; i++) {
    newString[i] = string[i];
  }

  strcpy(string, newString);

  free(newString);
}

float bytesToMegaBytes(long bytes) {
  return (float)bytes / pow(10, 6);
}

float bytesToKiloBytes(long bytes) {
  return (float)bytes / pow(10, 3);
}
