#ifndef _UTILS_H_
#define _UTILS_H_

typedef enum bool { false,
                    true } bool;

typedef struct Arguments {
  int* buffer;
  int counter;
  bool mode;
} Arguments;

void clearBuffer(int buffer[], int size);
bool checkIfHasN(char* string, unsigned int stringLen);
void swapIfBigger(int* x, int* y);

#endif
