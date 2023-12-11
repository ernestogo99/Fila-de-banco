/*
  Ernesto dalva-541803
  Marcos antonio-496563
  Tiago mamede-540764
  */



#include "escalonador.h"
#include "caixa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void e_inicializar(Escalonador *e, int caixas, int delta_t, int n_1, int n_2,
                   int n_3, int n_4, int n_5) {
  // Inicializar Filas
  int i;
  for (i = 0; i < 5; i++)
    f_inicializar(&(e->filas[i]));

  // Inicializar log
  log_inicializar(&e->log);

  e->caixas = caixas;
  e->delta_t = delta_t;
  e->disciplina[0] = n_1;
  e->disciplina[1] = n_2;
  e->disciplina[2] = n_3;
  e->disciplina[3] = n_4;
  e->disciplina[4] = n_5;
  e->disciplina_atual = 0;
}

int e_inserir_por_fila(Escalonador *e, int classe, int num_conta, int qtde_operacoes) {

  return f_inserir(&(e->filas[classe]), num_conta, qtde_operacoes);

}

int e_obter_prox_num_conta(Escalonador *e) {
  int conta;
  int i;
 
  return f_obter_proxima_chave(&(e->filas[e->disciplina_atual]));; //-1 se fila vazia
}

int e_consultar_prox_num_conta(Escalonador *e) {
  int conta;
  int i;

  return f_consultar_proxima_chave(&(e->filas[e->disciplina_atual])); //-1 fila vazia
}

int e_consultar_prox_qtde_oper(Escalonador *e) {
  int qtde_oper;
  int i;

  qtde_oper = f_consultar_proximo_valor(&(e->filas[e->disciplina_atual]));

  if (qtde_oper == -1)
    return 0;
  else
    return qtde_oper;
}

int e_consultar_prox_fila(Escalonador *e) {
  int prox;

  if (e->disciplina_atual ==
      4) { /*Já atendeu os n_5 clientes da última fila, vai para a primeira*/
    e->disciplina_atual = 0;
    prox = e->disciplina[0];
  } else { /*Já atendeu os n_ clientes das outras filas, vai para a próxima*/
    e->disciplina_atual = (e->disciplina_atual) + 1;
    prox = e->disciplina[(e->disciplina_atual)];
  }

  return prox;
}
int e_consultar_qtde_clientes(Escalonador *e) {
  int soma = 0;
  int i;

  for (i = 0; i < 5; i++) {
    soma += f_num_elementos(&(e->filas[i]));
  }

  return soma;
}

int e_consultar_tempo_prox_cliente(Escalonador *e) {
  int tempo, op;

  if (e_consultar_qtde_clientes(e) == 0)
    return -1;

  op = e_consultar_prox_qtde_oper(e);
  tempo = op * (e->delta_t);
  return tempo;
}

int e_conf_por_arquivo(Escalonador *e, char *nome_arq_conf) {
  FILE *arquivo = fopen(nome_arq_conf, "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir arquivos.\n");
    return 0; // Falha ao abrir o arquivo
  }

  int qtde_caixas, delta_t, conta, operac, classe_num;
  int disciplina[5];
  char classe[8];

  if (fscanf(arquivo, "qtde de caixas = %d\n", &qtde_caixas) == EOF)
    return 0;
  if (fscanf(arquivo, "delta t = %d\n", &delta_t) == EOF)
    return 0;
  if (fscanf(arquivo, "disciplina de escalonamento = {%d,%d,%d,%d,%d}\n",
             &disciplina[0], &disciplina[1], &disciplina[2], &disciplina[3],
             &disciplina[4]) == EOF)
    return 0;

  e_inicializar(e, qtde_caixas, delta_t, disciplina[0], disciplina[1],
                disciplina[2], disciplina[3], disciplina[4]);

  while (fscanf(arquivo, "%s - conta %d - %d operacao(oes)\n", classe, &conta,
                &operac) != EOF) {
    if (strcmp(classe, "Premium") == 0)
      classe_num = 0;
    else if (strcmp(classe, "Ouro") == 0)
      classe_num = 1;
    else if (strcmp(classe, "Prata") == 0)
      classe_num = 2;
    else if (strcmp(classe, "Bronze") == 0)
      classe_num = 3;
    else if (strcmp(classe, "Leezu") == 0)
      classe_num = 4;

    e_inserir_por_fila(e, classe_num, conta, operac);
  }

  fclose(arquivo);
  return 1;
}

void e_rodar(Escalonador *e, char *nome_arq_in, char *nome_arq_out) {
  int i, conta, oper, naux;
  int tempo = 0, aux_oper; /*Armazena a quantidade de operações pendentes no
                              instante "tempo"*/
  int tot_cli[5];
  float temp_esp[5], tot_oper[5];
  const char *str_fila[] = {"Premium", "Ouro", "Prata", "Bronze", "Leezu"};
  Caixa *cxs;
  Log *registrador;
  FILE *arq_saida;

  if (!e_conf_por_arquivo(e, nome_arq_in))
    return;
  if ((arq_saida = fopen(nome_arq_out, "a+")) == NULL)
    return;

  log_inicializar(&registrador);
  if (!c_inicializar(&cxs, e->caixas))
    return;

  /* Inicializa a quantidade total de operações de todas as filas */
  for (i = 0; i < 5; i++)
    tot_oper[i] = 0;

  for (int i = 0; i < 5; i++) {
    tot_cli[i] = f_num_elementos(&e->filas[i]);
  }

  naux = e->disciplina[0]; /*Quantidade primária de clientes a serem atendidos
                              será a disciplina Premium*/

  while (e_consultar_tempo_prox_cliente(e) !=
         -1) { /* Repete até atender todas as filas */

    while (naux > 0) { /* Realiza os atendimentos da fila atual enquanto houver
                          alguém determinado pela disciplina */
      aux_oper = e_consultar_prox_qtde_oper(e);
      tot_oper[e->disciplina_atual] +=
          aux_oper; /* Contabiliza a quantidade de operações por fila */
      conta = e_obter_prox_num_conta(e);
      naux--; /* Um cliente a menos atendido */
      if (conta != -1) {
        oper = c_realizar_prox_operacao(&cxs);
        tempo += (oper * e->delta_t);
        i = c_obter_prox_caixa(&cxs);
        cxs[i].oper = aux_oper; /* Cliente entra no caixa i para realizar
                                   aux_oper operações */
        cxs[i].qtd_atendidos +=
            1; /* Contabiliza +1 cliente atendido no caixa i */
        log_registrar(&registrador, conta, e->disciplina_atual, tempo, i + 1);
        fprintf(arq_saida,
                "T = %d min: Caixa %d chama da categoria %s cliente da conta "
                "%d para realizar %d operacao(oes).\n",
                tempo, i + 1, str_fila[e->disciplina_atual], conta, aux_oper);
      }
    }
    naux = e_consultar_prox_fila(e);
  }

  oper = c_obter_oper_ultimo_cliente(&cxs);
  tempo += (oper * e->delta_t);

  fprintf(arq_saida, "Tempo total de atendimento: %d minutos.\n", tempo);

  for (i = 0; i < 5; i++) {
    temp_esp[i] = log_media_por_classe(&registrador, i);
    fprintf(arq_saida, "Tempo medio de espera dos %d clientes %s: %.2f\n",
            tot_cli[i], str_fila[i], temp_esp[i]);
  }

  for (i = 0; i < 5; i++)
    fprintf(arq_saida, "Quantidade media de operacoes por cliente %s = %.2f\n",
            str_fila[i], (tot_oper[i] / tot_cli[i]));

  for (i = 0; cxs[i].oper != -1; i++)
    fprintf(arq_saida, "O caixa de número %d atendeu %d clientes.\n", i + 1,
            c_obter_num_atendidos(&cxs, i));

  fclose(arq_saida);
}
