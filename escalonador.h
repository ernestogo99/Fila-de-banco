/*
  Ernesto dalva-541803
  Marcos antonio-496563
  Tiago mamede-540764
  */


#include "logtree.h"
#include "fila_fifo.h"

typedef struct {
    Fila_FIFO* filas[5];//0-premium 1-ouro 2-prata 3-comum 4-leezu
    int caixas;
    int delta_t;
    int disciplina[5];
    Log* log;
    int disciplina_atual;
} Escalonador;

void e_inicializar (Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5);
int e_inserir_por_fila (Escalonador *e, int classe, int num_conta, int qtde_operacoes);
int e_obter_prox_num_conta(Escalonador *e);
int e_consultar_prox_num_conta (Escalonador *e);
int e_consultar_prox_qtde_oper (Escalonador *e);
int e_consultar_prox_fila (Escalonador *e);
int e_consultar_qtde_clientes (Escalonador *e);
int e_consultar_tempo_prox_cliente (Escalonador *e);
int e_conf_por_arquivo (Escalonador *e, char *nome_arq_conf);
void e_rodar (Escalonador *e, char *nome_arq_in, char *nome_arq_out);