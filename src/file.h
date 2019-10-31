#ifndef _FILE_H_
#define _FILE_H_

#include "image.h"
#include "utils.h"

char* readInstructions();
bool saveImage(Image* image, char* bruteImageName);
void compressImage(char* image);

#endif
