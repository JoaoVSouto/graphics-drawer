#ifndef _UTILS_H_
#define _UTILS_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum bool { false,
                    true } bool;

typedef struct Arguments {
  int* buffer;
  int counter;
  bool mode;
} Arguments;

void clearBuffer(int buffer[], int size);
bool checkIfHasN(char* string, unsigned int stringLen);
void swapNumbers(int* x, int* y);
bool swapIfBigger(int* x, int* y);
void removeLastChar(char* string);
float bytesToMegaBytes(long bytes);
float bytesToKiloBytes(long bytes);

#endif
