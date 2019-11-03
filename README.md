# Interpretador de primitivas gráficas

Esse projeto tem como princípio a interpretação e escrita de primitivas gráficas através da geração de um arquivo _.ppm_.

## O que foi feito?

- [x] Criação de uma imagem através da primitiva `image <largura> <altura>` .
- [x] Limpeza da imagem através de uma cor especificada pela primitiva `clear <red> <green> <blue>`.
- [x] Alteração da cor atual do pincel através da primitiva `color <red> <green> <blue>`.
- [x] Escrita da imagem no disco através da primitiva `save <image-name.ppm>`.
- [x] Plot de linha por meio do **[Algoritmo de Bresenham para desenho de linhas](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)** através da primitiva `line <x1> <y1> <x2> <y2>`.
- [x] Plot de círculo por meio do **[Algoritmo de Bresenham para desenho de círculos](https://iq.opengenus.org/bresenhams-circle-drawing-algorithm/)** através da primitiva `circle <x> <y> <raio>`, onde _x_ e _y_ representam o centro.
- [x] Plot de retângulo através da primitiva `rect <x1> <y1> <x2> <y2>`.
- [x] Plot de polígonos através da primitiva `polygon <n pontos> <x1> <y1> <x2> <y2> ... <xn> <yn>`.
- [x] Preenchimento de polígonos por meio do **[Algoritmo de Flood Fill](https://en.wikipedia.org/wiki/Flood_fill)** através da primitiva `fill <x> <y>`.
- [x] Compressão de imagens através da **[Codificação run-length (RLE)](https://en.wikipedia.org/wiki/Run-length_encoding)**.
- [x] Descompressão de imagens codificadas pelo RLE.

## O que seria feito diferente?

FINISH THIS LATER...

## Como compilar o projeto?

No terminal, execute:

1.  `cd src`
2.  `make`
3.  `./main`
4.  Para descomprimir a imagem, digite: `./main -d <image-name.ppm>`. Por exemplo, se existe uma imagem comprimida chamada `test.ppm` no atual diretório, basta executar `./main -d test.ppm`.
