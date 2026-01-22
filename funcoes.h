#ifndef HEAD_FUNCOES
#define HEAD_FUNCOES

#define FALSE 0
#define TRUE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    int fundamentos_entrada_saida;
    int estruturas_de_controle;
    int estruturas_de_repeticao;
    int vetores_e_matrizes;
    int manipulacao_de_strings;
    int funcoes_e_modularizacao;
    int ponteiros;
    int alocacao_dinamica_de_memoria;
    int structs_e_unions;
    int manipulacao_de_arquivos;
}Categoria;

typedef struct {
    int id;
    char titulo[100];
    char descricao[1000];
    int dificuldade;
    Categoria tag;
} Tarefa;

typedef struct {
    int id;
    char nome[100];
    char senha[64];
    int qtd_tarefas;
    int admin; //TRUE/FALSE
} Usuario;

typedef struct {
    int id_usuario;
    int id_tarefa;
} Historico;


// Create Read Update Delete
void criar_usuarios_csv();
void criar_usuario_binario(char nome[], char senha[], char tipo);
void criar_tarefa_binario(Tarefa t);
void criar_tarefas_csv();
void criar_historico_binario(int t_id, int u_id);

void excluir_tarefa(int id);
void excluir_usuario(int id);

void listar_usuarios();
void listar_tarefas(); 
void listar_historico(int u_id);

int  ja_fez(int id_t, int id_u);
int  gerar_proximo_id(char acao);
void incrementar_tarefas_concluidas(int id_usuario);

int verificar_usuario_existente(char login[]);
Usuario validacao_login(char login[], char senha[]);
Usuario achar_usuario_id(int id_u);
Tarefa *recomendar(int categoria, int nivel_dificuldade, int user_logado);
Tarefa achar_tarefa_id(int id_t);


#endif