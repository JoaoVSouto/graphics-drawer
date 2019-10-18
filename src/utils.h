#ifndef _UTILS_H_
#define _UTILS_H_

typedef enum { false,
               true } bool;

typedef struct {
  int* buffer;
  int counter;
  bool mode;
} Arguments;

void clearBuffer(int buffer[], int size);
bool checkIfHasN(char* string, unsigned int stringLen);

#endif
