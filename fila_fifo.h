/*
  Ernesto dalva-541803
  Marcos antonio-496563
  Tiago mamede-540764
  */


typedef struct Fila_FIFO{
        int chave;
        int valor;
        struct Fila_FIFO *prox;
}Fila_FIFO;

int vazia(Fila_FIFO *f);
void f_inicializar (Fila_FIFO **f);
int f_inserir (Fila_FIFO **f, int chave, int valor);
int f_obter_proxima_chave (Fila_FIFO **f);
int f_consultar_proxima_chave (Fila_FIFO **f);
int f_consultar_proximo_valor (Fila_FIFO **f);
int f_num_elementos (Fila_FIFO **f);
int f_consultar_chave_por_posicao (Fila_FIFO **f, int posicao);
int f_consultar_valor_por_posicao (Fila_FIFO **f, int posicao);