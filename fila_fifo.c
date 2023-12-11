/*
  Ernesto dalva-541803
  Marcos antonio-496563
  Tiago mamede-540764
  */


#include "fila_fifo.h"
#include <stdio.h>
#include <stdlib.h>

int vazia(Fila_FIFO *f) {
  if (f == NULL) {
    return 1;
  } else {
    return 0;
  }
}

void f_inicializar (Fila_FIFO **f){
    *f=NULL;
}

// como é uma fila,então vamos inserir no final
int f_inserir(Fila_FIFO **f, int chave, int valor) {
  Fila_FIFO *aux, *novo = malloc(sizeof(Fila_FIFO));
  if (novo) {
    novo->chave = chave;
    novo->valor = valor;
    novo->prox = NULL;

    if (vazia(*f)) { // é o primeiro?
      *f = novo;
    } else {
      // tenho que percorrer a fila até chegar no final para inserir
      aux = *f;
      while (aux->prox != NULL) {
        if (aux->chave == chave) {
          free(novo);
          return 0; // chave ja existe na fila
        }
        aux = aux->prox;
      }
      aux->prox = novo; // insere o novo  no final da fila
    }
    return 1;
  } else {
   // erro ao alocar memoria
    return 0;
  }
}

// como é uma fila , vamos  remover do inicio
int f_obter_proxima_chave(Fila_FIFO **f) {
  Fila_FIFO *remover = NULL;
  int chave = 0;
  if (*f) {
    remover = *f;
    chave = (*f)->chave;
    *f = remover->prox;
    free(remover);
    return chave;
  } else {
    // fila vazia
    return -1;
  }
}

int f_consultar_proxima_chave(Fila_FIFO **f) {
  if (vazia(*f)) {
    return -1;
  } else {
    return (*f)->chave;
  }
}

int f_consultar_proximo_valor(Fila_FIFO **f) {
  if (vazia(*f)) {
    return -1;
  } else {
    return (*f)->valor;
  }
}

int f_num_elementos(Fila_FIFO **f) {
  int contador = 0;
  Fila_FIFO *aux = *f;
  while (aux != NULL) {
    aux = aux->prox;
    ++contador;
  }
  return contador;
}

int f_consultar_chave_por_posicao(Fila_FIFO **f, int posicao) {
  int contador = 1;
  Fila_FIFO *aux = *f;

  while (aux != NULL && contador != posicao) {
    aux = aux->prox;
    ++contador;
  }

  if (aux == NULL) {
    return -1;
  } else {
    return aux->chave;
  }
}

int f_consultar_valor_por_posicao(Fila_FIFO **f, int posicao) {
  int contador = 1;
  Fila_FIFO *aux = *f;
  while (aux != NULL && contador != posicao) {
    aux = aux->prox;
    ++contador;
  }
  if (aux == NULL) {
    return -1;
  } else {
    return aux->valor;
  }
}
