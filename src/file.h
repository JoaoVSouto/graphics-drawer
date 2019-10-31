#ifndef _FILE_H_
#define _FILE_H_

#include "image.h"
#include "utils.h"

char* readFile(char* fileName);
void saveImage(Image* image, char* bruteImageName);
void saveFile(char* fileName, char* fileContent);
void compressImage(char* image);
void decompressImage(char* fileName, char* imageContent);

#endif
