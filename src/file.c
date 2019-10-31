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

  compressImage(image->image);

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

void compressImage(char* image) {
  int i, counter = 1, lineNumber = 1;
  const char newLine[2] = "\n";
  char* imageCompressed;
  char* imageString;
  char* token;
  char currentLine[MAX_CHARS_PER_LINE + 1];
  char previousLine[MAX_CHARS_PER_LINE + 1];
  // exemplo de linha comprimida:
  // 1500(255 255 255)
  // 4 algarismos de repetição + 2 parenteses + 12 caracteres de cor
  char compressedLine[MAX_CHARS_PER_LINE + 2 + 4];

  imageCompressed = (char*)calloc(strlen(image), sizeof(char));
  imageString = (char*)calloc(strlen(image), sizeof(char));

  strcpy(imageString, image);

  token = strtok(imageString, newLine);

  while (token != NULL) {
    // Pula o cabeçalho
    if (lineNumber <= 3) {
      lineNumber++;
      sprintf(currentLine, "%s\n", token);
      strcat(imageCompressed, currentLine);
    } else if (lineNumber == 4) {
      lineNumber++;
      sprintf(previousLine, "%s\n", token);
    } else {
      sprintf(currentLine, "%s\n", token);
      // caso a linha anterior e a linha atual forem iguais, incrementar o counter
      if (!strcmp(previousLine, currentLine)) {
        counter += 1;
      } else {
        // caso forem diferentes, concatenar na imagem a string comprimida
        removeLastChar(previousLine);
        sprintf(compressedLine, "%d(%s)\n", counter, previousLine);
        strcat(imageCompressed, compressedLine);
        counter = 1;
      }
      strcpy(previousLine, currentLine);
    }

    token = strtok(NULL, newLine);
  }

  strcpy(image, imageCompressed);

  free(imageCompressed);
}
