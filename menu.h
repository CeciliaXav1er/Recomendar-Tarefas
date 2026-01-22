#ifndef HEAD_MENU
#define HEAD_MENU

#include "funcoes.h"

#define LIN_SIMPLES printf("--------------------------------------------------\n");
#define LIN_DUPLA printf("==================================================\n");


void enter();
int ler_inteiro();
void menu_admin();
void  menu_inicial();
void listar_categorias();
void menu_usuario(Usuario u);
void cabecalho(char *titulo);
void mensagem_erro(char *msg);
void imprimir_bonito(char *texto);
void mensagem_sucesso(char *msg);
void limpa_texto_csv( char *texto);
void ler_texto(char *texto, int tamanho);
void exibir_tarefa_bonita(Tarefa *t, char acao);

#endif