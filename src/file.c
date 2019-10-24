#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    fileContent = malloc(fileSize + 1);  // fileSize + 1 porque com fileSize + 0 gera segmentation fault
    // Lê o arquivo passando como argumentos:
    // (string, tam em bytes de cada elemento, número de elementos a serem lidos, arquivo)
    fread(fileContent, 1, fileSize, file);
    fileContent[fileSize] = '\0';
    printf("Leitura do arquivo realizada com sucesso!\n");

    fclose(file);
  }

  return fileContent;
}

bool saveImage(Image* image, char* bruteImageName) {
  char* imageName;
  FILE* file;
  bool saveSuccess = false;
  int i, j;

  imageName = (char*)calloc(strlen(bruteImageName), sizeof(char));

  strcpy(imageName, bruteImageName);
  imageName[strlen(imageName) - 1] = '\0';
  // Caso a string tenha quatro caracteres antes do ponto, adicionar mais 1 \0
  if (strlen(imageName) == 10) {
    imageName[strlen(imageName) - 2] = '\0';
  }

  // Escreve a matriz na imagem
  for (i = 0; i < image->rows; i++) {
    for (j = 0; j < image->columns; j++) {
      strcat(image->image, image->matrix[i][j]);
    }
  }

  file = fopen(imageName, "w");

  if (file == NULL) {
    printf("Erro na abertura do arquivo %s para escrita\n", imageName);
  } else {
    if (fputs(image->image, file) != EOF) {
      printf("Arquivo salvo com sucesso!\n");
      saveSuccess = true;
    }

    fclose(file);
  }

  free(imageName);

  return saveSuccess;
}
