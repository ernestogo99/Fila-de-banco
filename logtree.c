/*
  Ernesto dalva-541803
  Marcos antonio-496563
  Tiago mamede-540764
  */


#include "logtree.h"
#include <stdlib.h>

LogNode* criar_no(int conta, int classe, int timer, int caixa) {
    LogNode* novo = (LogNode*)malloc(sizeof(LogNode));
    if (novo == NULL) {
        exit(EXIT_FAILURE);
    }
    novo->conta = conta;
    novo->classe = classe;
    novo->timer = timer;
    novo->caixa = caixa;
    novo->left = NULL;
    novo->right = NULL;
    return novo;
}


void inserir_no(LogNode** root, int conta, int classe, int timer, int caixa) {
    if (*root == NULL) {
        *root = criar_no(conta, classe, timer, caixa);
    } 
    else {
        if (conta == (*root)->conta)  return;
        if (conta < (*root)->conta)
          {inserir_no(&(*root)->left, conta, classe, timer, caixa);}
        else
          {inserir_no(&(*root)->right, conta, classe, timer, caixa);}
    }
}
  
void log_inicializar(Log** l) {
    *l = (Log*)malloc(sizeof(Log));
    if (*l == NULL) {
        exit(EXIT_FAILURE);
    }
    (*l)->root = NULL;
}

void log_registrar(Log** l, int conta, int classe, int timer, int caixa) {
  inserir_no(&(*l)->root, conta, classe, timer, caixa);
}

void calcular_media(LogNode* galho, int classe, float* soma, int* contagem) {
    if (galho == NULL) return;
    if (galho->classe == classe) {
        (*soma) += galho->timer;
        (*contagem)++;
    }
  
    calcular_media(galho->left, classe, soma, contagem);
    calcular_media(galho->right, classe, soma, contagem);
}

void calcular_qnt_clientes(LogNode* galho, int caixa, int* contagem) {
    if (galho == NULL) return;
    if (galho->caixa == caixa) {
        (*contagem)++;
    }

    calcular_qnt_clientes(galho->left, caixa, contagem);
    calcular_qnt_clientes(galho->right, caixa, contagem);
}

float log_media_por_classe(Log** l, int classe) {
    if ((*l)->root == NULL) return 0;
  
    float soma = 0;
    int contagem = 0;
    calcular_media((*l)->root, classe, &soma, &contagem);
  
    if (contagem == 0) return 0;
    return soma / contagem;
}

int log_obter_soma_por_classe(Log** l , int classe){
      if ((*l)->root == NULL) return 0;
    
      float soma = 0;
      int contagem = 0; //apenas para utilizar a func calcular_media()
      calcular_media((*l)->root, classe, &soma, &contagem);
  
      return soma;
}

int log_obter_contagem_por_classe(Log** l , int classe){
      if ((*l)->root == NULL) return 0;

      float soma = 0;//apenas para utilizar a func calcular_media()
      int contagem = 0;
      calcular_media((*l)->root, classe, &soma, &contagem);
  
      return contagem;
}

