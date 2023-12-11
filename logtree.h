/*
  Ernesto dalva-541803
  Marcos antonio-496563
  Tiago mamede-540764
  */


typedef struct LogNode {
    int conta;
    int classe;
    int timer;
    int caixa;
    struct LogNode* left;
    struct LogNode* right;
} LogNode;

typedef struct {
    LogNode* root;
} Log;


LogNode* criar_no(int conta, int classe, int timer, int caixa);
void calcular_media(LogNode* root, int classe, float* soma, int* contagem);
void calcular_qnt_clientes(LogNode* galho, int caixa, int* contagem);
void inserir_no(LogNode** root, int conta, int classe, int timer, int caixa);

void log_inicializar(Log **l);
void log_registrar(Log **l, int conta, int classe, int timer, int caixa);
float log_media_por_classe(Log **l, int classe);
int log_obter_soma_por_classe(Log **l, int classe);
int log_obter_contagem_por_classe(Log **l, int classe);
int log_obter_contagem_por_caixa(Log** l , int caixa);