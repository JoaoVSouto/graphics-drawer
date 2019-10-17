#include "file.h"
#include <stdio.h>
#include <stdlib.h>

char* readInstructions() {
  FILE* file;
  char* fileContent;
  long fileSize;

  file = fopen("instructions.txt", "r");

  if (file == NULL) {
    printf("Erro na leitura de instructions.txt\n");
  } else {
    // Seta o cursor para o final do arquivo
    fseek(file, 0, SEEK_END);
    // fileSize recebe o tamanho em bytes do arquivo
    fileSize = ftell(file);
    // Seta o cursor para o início do arquivo
    fseek(file, 0, SEEK_SET);

    // Aloca espaço de memória suficiente para formar a string
    fileContent = malloc(fileSize);
    // Lê o arquivo passando como argumentos:
    // (string, tam em bytes de cada elemento, número de elementos a serem lidos, arquivo)
    fread(fileContent, 1, fileSize, file);
    fileContent[fileSize] = '\0';

    fclose(file);
  }

  return fileContent;
}
