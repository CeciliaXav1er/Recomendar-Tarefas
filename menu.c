#include "menu.h"
#include "funcoes.h"

void ler_texto(char *texto, int tamanho) {
    int valida = FALSE;
    int primeira_tentativa = TRUE;
    do {
        if (!primeira_tentativa) {
            printf(">> O campo não pode estar vazio. Digite novamente: ");
        }
        if (fgets(texto, tamanho, stdin) != NULL) {
            
        size_t len = strlen(texto);
        
        if (len > 0 && texto[len - 1] == '\n') {
            texto[len - 1] = '\0';
            len--;
        } else {
          int c;
          while ((c = getchar()) != '\n' && c != EOF);
        }
        if (len==0) {
            primeira_tentativa = FALSE;
            valida = FALSE;
        } else {
            valida = TRUE;
        }
      } else {
            valida = TRUE;
      }
        
    } while (valida == 0);
    
}

int ler_inteiro() {
  char texto[100];
  if (fgets(texto, sizeof(texto), stdin) != NULL) {
    //remove espaços e tabs
    int i = 0;
    while (texto[i] == ' ' || texto[i] == '\t') {
      i++;
    }
    //verifica se é um número
    if (texto[i] < '0' || texto[i] > '9') {
      //se não for, retorna -1
      return -1;
    }
    //se sim, retorna o número
    return atoi(texto);
  }
  return -1;
}

void limpa_texto_csv(char *texto) {
  for (int i = 0; texto[i] != '\0'; i++) {
    if (texto[i] == ';') {
      texto[i] = ',';
    }
    if (texto[i] == '\n') {
      texto[i] = ' ';
    }
  }
}

void imprimir_bonito(char *texto) {
  int contador = 0;
  int limite = 40;

  for (int i = 0; texto[i] != '\0'; i++) {

    if (texto[i] == '|') {
      texto[i] = ' ';
      printf("\n");
      printf("   ");
      contador = 0;
    } else {
      printf("%c", texto[i]);
      contador++;
    }

    if (contador >= limite && texto[i] == ' ') {
      printf("\n");
      contador = 0;
    }
  }
  printf("\n");
}

void cabecalho(char *titulo) {

// identifica se o SO é WIN ou LINUX
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif

  printf("==================================================\n");
  printf("             SISTEMA DE RECOMENDAÇÃO              \n");
  printf("==================================================");

  if (titulo != NULL) {
    printf("\n>> %s \n", titulo);
    printf("==================================================\n");
  }
}

void menu_inicial() {

  cabecalho("BEM-VINDO");
  printf(" [1] Fazer Login\n");
  printf(" [2] Cadastrar Novo Usuario\n");
  printf(" [0] Sair do Sistema\n");
  printf("==================================================\n");
  printf(" > Digite sua opcao: ");
}

void menu_usuario(Usuario u) {

  cabecalho("MENU DO USUÁRIO");
  printf(" >> OLÁ, %s! O QUE VAMOS ESTUDAR?\n", u.nome);
  printf(" > Você já fez o total de [ %d ] questões!\n", u.qtd_tarefas);
  printf("--------------------------------------------------\n");

  printf(" [1] Quero uma Recomendação!\n");
  printf(" [2] Ver meu Histórico\n");
  printf(" [0] Deslogar\n");
  printf("==================================================\n");
  printf(" > Digite sua opcao: ");
}

void menu_admin() {

  cabecalho("PAINEL DO ADMINISTRADOR");
  printf(" [1] Cadastrar Nova Tarefa\n");
  printf(" [2] Listar Todas as Tarefas\n");
  printf(" [3] Listar Todos os Usuarios\n");
  printf(" [4] Buscar Tarefa por ID\n");
  printf(" [5] Buscar Usuario por ID\n");
  printf(" --- GERENCIAMENTO ---\n");
  printf(" [6] Excluir uma Tarefa\n");
  printf(" [7] Excluir um Usuario\n");
  printf(" --- EXPORTACAO DE DADOS ---\n");
  printf(" [8] Gerar CSV de Tarefas\n");
  printf(" [9] Gerar CSV de Usuarios\n");
  printf("\n");
  printf(" * Nota: Os arquivos CSV não se atualizam sozinhos.\n");
  printf(" [0] Voltar ao Menu Principal\n");
  printf("==================================================\n");
  printf(" > Digite sua opcao: ");
}

void mensagem_sucesso(char *msg) { printf("\n>> [SUCESSO] %s \n\n", msg); }

void mensagem_erro(char *msg) {
  printf("\n>> [ERRO] %s \n\n", msg);
  enter();
}

void exibir_tarefa_bonita(Tarefa *t, char acao) {
  // L = Listar, R = Recomendar
  if (acao == 'R') {
    cabecalho("RECOMENDAÇÃO ENCONTRADA");
  } else if (acao == 'L') {
    //?
  }

  printf("ID: %03d  | Dificuldade: %d                   \n", t->id,
         t->dificuldade);
  printf("--------------------------------------------------\n");
  printf("TÍTULO: %-38s \n", t->titulo);
  printf("--------------------------------------------------\n");
  printf("DESCRIÇÃO:\n   ");
  imprimir_bonito(t->descricao);
  printf("--------------------------------------------------\n");
  if (t->tag.fundamentos_entrada_saida)
    printf("   - Fundamentos E/S\n");
  if (t->tag.estruturas_de_controle)
    printf("   - Est. Controle\n");
  if (t->tag.estruturas_de_repeticao)
    printf("   - Est. Repetição\n");
  if (t->tag.vetores_e_matrizes)
    printf("   - Vetores/Matrizes\n");
  if (t->tag.manipulacao_de_strings)
    printf("   - Manip. Strings\n");
  if (t->tag.funcoes_e_modularizacao)
    printf("   - Funções/Modularização\n");
  if (t->tag.ponteiros)
    printf("   - Ponteiros\n");
  if (t->tag.alocacao_dinamica_de_memoria)
    printf("   - Alocação Dinâmica\n");
  if (t->tag.structs_e_unions)
    printf("   - Structs e Unions\n");
  if (t->tag.manipulacao_de_arquivos)
    printf("   - Manip. Arquivos\n");
  printf("==================================================\n");
}

void listar_categorias() {

  printf("--------------------------------------------------\n");
  printf(" >> Categorias\n");
  printf("--------------------------------------------------\n");
  printf(" [1] Fundamentos E/S       [2] Est. Controle\n");
  printf(" [3] Est. Repetição        [4] Vetores/Matrizes\n");
  printf(" [5] Manip. Strings        [6] Funções\n");
  printf(" [7] Ponteiros             [8] Alocação Dinâmica\n");
  printf(" [9] Structs e Unions      [10] Manip. Arquivos\n");
  printf("--------------------------------------------------\n");
}

void enter() {
  printf("\nPressione ENTER para continuar...");
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}