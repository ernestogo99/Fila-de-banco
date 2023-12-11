/*
  Ernesto dalva-541803
  Marcos antonio-496563
  Tiago mamede-540764
  */


#include "caixa.h"

/* Inicializa os caixas conforme a quantidade especificada por "qtd_caixas".*/
int c_inicializar(Caixa **c, int qtd_caixas){
    register int i;
    *c = (Caixa *) malloc((qtd_caixas + 1) * sizeof(Caixa)); /* Alocar uma posição adicional para indicar o final do vetor */
    if(*c == NULL)
        return 0;

    (*c + qtd_caixas) -> oper = -1; /* Indica o fim do vetor caixas */

    for(i = 0; (*c + i) -> oper != -1 ; i++){
        (*c + i) -> qtd_atendidos = 0;
        (*c + i) -> oper = 0;
    }
  return 1;
}

/* Realiza operações dos clientes que estão nos caixas e retorna a última quantidade de
  operações realizadas pela primeira pessoa que terminou suas atividades*/
int c_realizar_prox_operacao(Caixa **c){
  register int i;
  int m = (*c) -> oper;

  for(i = 1; (*c + i) -> oper != -1; i++){
    if(((*c) + i) -> oper < m)
      m = ((*c) + i) -> oper;
  }
  for(i = 0; (*c + i) -> oper != -1 ; i++){
    if((*c + i) -> oper != 0)
      (*c + i) -> oper = ((*c + i) -> oper) - m;
  }
  return m;
}

/* Retorna o primeiro caixa disponível ou um inteiro diferente de zero caso não houver nenhum 
 disponível. */
int c_obter_prox_caixa(Caixa **c){
  int register i = 0;

  while((*c + i) -> oper != -1 && (*c + i) -> oper != 0)
    i++;

  return i;
}

/* Retorna a quantidade total de clientes atendidos pelo caixa j */
int c_obter_num_atendidos(Caixa **c, int j){
  return (*c + j) -> qtd_atendidos;
}

/* Retorna a quantidade de operações do último cliente a deixar o caixa */
int c_obter_oper_ultimo_cliente(Caixa **c){
  register int i;	
  int ult_oper = (*c) -> oper;

  for(i = 1; (*c + i) -> oper != -1; i++){
    if(  (*c + i) -> oper > ult_oper  )
      ult_oper = (*c + i) -> oper;
  }

  return ult_oper;
}