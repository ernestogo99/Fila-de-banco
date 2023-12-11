#include "escalonador.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
  Ernesto dalva-541803
  Marcos antonio-496563
  Tiago mamede-540764
  */

int main(int argc, char *argv[]) {
  Escalonador e;

  char entrada[17] = "entrada-", saida[15] = "saida-";

  if ( argc < 2 ){ /* nenhum arquivo informado na linha de comando */
    printf("Arquivo de entrada não informado");
    return EXIT_FAILURE;
  }

  /* adequando o nome dos arquivos aos padroes requeridos */
  sprintf(argv[1], "%04d", atoi(argv[1]));
  strcat(saida, argv[1]);
  strcat(entrada, argv[1]);
  strcat(entrada, ".txt");
  strcat(saida, ".txt");

  e_rodar(&e, entrada, saida);
  
  return 0;
}
