/*
  Ernesto dalva-541803
  Marcos antonio-496563
  Tiago mamede-540764
  */

#include <stdlib.h>

typedef struct{
   int qtd_atendidos;
   int oper;
}Caixa;


 /*   Funções auxiliares   */
int c_inicializar(Caixa **c, int qtd_caixas);

int c_realizar_prox_operacao(Caixa **c);

int c_obter_prox_caixa(Caixa **c);

int c_obter_num_atendidos(Caixa **c, int j);

int c_obter_oper_ultimo_cliente(Caixa **c);

