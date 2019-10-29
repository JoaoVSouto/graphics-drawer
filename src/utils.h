#ifndef _UTILS_H_
#define _UTILS_H_

#include <string.h>
#include "image.h"

typedef enum bool { false,
                    true } bool;

typedef enum bool_trespass { falsy,
                             truthy,
                             trespass } bool_trespass;

typedef struct Arguments {
  int* buffer;
  int counter;
  bool mode;
} Arguments;

void clearBuffer(int buffer[], int size);
bool checkIfHasN(char* string, unsigned int stringLen);
void swapNumbers(int* x, int* y);
bool swapIfBigger(int* x, int* y);

#endif
