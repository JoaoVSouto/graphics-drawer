#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readFile(char* fileName) {
  FILE* file;
  char* fileContent;
  long fileSize;

  file = fopen(fileName, "r");

  if (file == NULL) {
    printf("Erro na leitura de %s\n", fileName);
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
    printf("Leitura do %s realizada com sucesso!\n", fileName);

    fclose(file);
  }

  return fileContent;
}

void saveImage(Image* image, char* bruteImageName) {
  char* imageName;
  int i, j;

  imageName = (char*)malloc(strlen(bruteImageName));

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

  saveFile(imageName, image->image);

  free(imageName);
}

void saveFile(char* fileName, char* fileContent) {
  FILE* file;

  file = fopen(fileName, "w");

  if (file == NULL) {
    printf("\e[38;5;196mERRO: Não foi possível abrir %s\n", fileName);
  } else {
    if (fputs(fileContent, file) != EOF) {
      printf("Arquivo salvo com sucesso!\n");
    }

    fclose(file);
  }
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
      // Adiciona marcador de compressão na primeira linha do arquivo
      if (lineNumber == 1) {
        sprintf(currentLine, "%s#\n", token);
      } else {
        sprintf(currentLine, "%s\n", token);
      }
      strcat(imageCompressed, currentLine);
      lineNumber++;
    } else if (lineNumber == 4) {
      sprintf(previousLine, "%s\n", token);
      lineNumber++;
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

void decompressImage(char* fileName, char* imageContent) {
  const char newLine[2] = "\n";
  char* token;
  char* imageDecompressed;
  char* decompressionMarker;
  char* imageCopy;
  char currentLine[MAX_CHARS_PER_LINE];
  int pixelColor[3];
  int numberOfLines = 4,  // 3 + 1 => número de linhas do cabeçalho e nova linha
      lineNumber = 1,
      numberOfRepetitions,
      i;

  // Detectando se a imagem já está descomprimida
  decompressionMarker = strchr(imageContent, '#');
  if (decompressionMarker == NULL) {
    printf("\e[38;5;196mERRO: A imagem já está descomprimida...\n");
    return;
  }

  imageCopy = (char*)malloc(strlen(imageContent));
  strcpy(imageCopy, imageContent);

  token = strtok(imageCopy, newLine);

  // Descobrindo o número de linhas que terá o arquivo descomprimido
  while (token != NULL) {
    if (lineNumber <= 3) {
      lineNumber++;
    } else {
      sscanf(token, "%d", &numberOfRepetitions);
      numberOfLines += numberOfRepetitions;
    }

    token = strtok(NULL, newLine);
  }
  imageDecompressed = (char*)malloc(numberOfLines * MAX_CHARS_PER_LINE);

  lineNumber = 1;
  token = strtok(imageContent, newLine);

  while (token != NULL) {
    // Pulando o cabeçalho
    if (lineNumber <= 3) {
      if (lineNumber == 1) {  // Removendo a # do cabeçalho
        removeLastChar(token);
      }
      sprintf(currentLine, "%s\n", token);
      strcat(imageDecompressed, currentLine);
      lineNumber++;
    } else {
      sscanf(token, "%d(%d %d %d)", &numberOfRepetitions,
             &pixelColor[0], &pixelColor[1], &pixelColor[2]);
      sprintf(currentLine, "%d %d %d\n", pixelColor[0],
              pixelColor[1], pixelColor[2]);

      for (i = 0; i < numberOfRepetitions; i++) {
        strcat(imageDecompressed, currentLine);
      }
    }
    token = strtok(NULL, newLine);
  }

  saveFile(fileName, imageDecompressed);

  free(imageDecompressed);
}
