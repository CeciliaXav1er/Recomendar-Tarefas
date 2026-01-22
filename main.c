
#include "funcoes.h"
#include "menu.h"

int main() {

  setlocale(LC_ALL, "Portuguese");
  // sei que algo desse tipo não é recomendado
  char *chave_adm = "Bolota123";
  char nome_login[100], senha_login[64], senha_adm[64];
  Tarefa nova_tarefa;
  char mensagem[200];

  int resposta = -1;

  while (resposta != 0) {

    int categoria = -1, opcao_adm = -1, opcao_user = -1, dificuldade = -1,
        opcao_hist, existe = FALSE, adm, id_excluir, id_achar;

    menu_inicial();
    resposta = ler_inteiro();

    switch (resposta) {
    case 1:
      // login
      cabecalho("LOGIN DE USUÁRIO");
      printf("> Digite seus dados para entrar:\n\n");
      printf("Usuário: ");
      ler_texto(nome_login, sizeof(nome_login));
      printf("Senha: ");
      ler_texto(senha_login, sizeof(senha_login));

      Usuario usuario_logado = validacao_login(nome_login, senha_login);

      if (usuario_logado.id == -1) {
        mensagem_erro("Usuário ou senha invalidos!");
      } else {
        if (usuario_logado.admin == TRUE) { //  MENU ADMINISTRADOR
          memset(&nova_tarefa, 0,
                 sizeof(Tarefa)); // para nao deixar lixo de memoria
          do {
            menu_admin();
            opcao_adm = ler_inteiro();
            switch (opcao_adm) {
            case 1:
              nova_tarefa.id = gerar_proximo_id('T');
              printf("> Título: ");
              ler_texto(nova_tarefa.titulo, sizeof(nova_tarefa.titulo));
              printf("> Descrição (Para adicionar parágrafos, use '|'): ");
              ler_texto(nova_tarefa.descricao, sizeof(nova_tarefa.descricao));
              do {
                printf("\n> Dificuldade (1-5): ");
                nova_tarefa.dificuldade = ler_inteiro();
                if (nova_tarefa.dificuldade < 1 ||
                    nova_tarefa.dificuldade > 5) {
                  mensagem_erro("Dificuldade deve estar entre 1 e 5");
                }
              } while (nova_tarefa.dificuldade < 1 ||
                       nova_tarefa.dificuldade > 5);

              categoria = -1;
              while (categoria != 0) {
                listar_categorias();
                printf(">> Escolha uma categoria (ou 0 para sair): ");
                categoria = ler_inteiro();
                if (categoria < 0 || categoria > 10) {
                  mensagem_erro("Categoria inválida! Digite entre 0 e 10.");
                  continue;
                }
                switch (categoria) {
                case 1:
                  nova_tarefa.tag.fundamentos_entrada_saida = 1;
                  printf("\n>> Categoria 'Fundamentos E/S' adicionada!\n");
                  break;
                case 2:
                  nova_tarefa.tag.estruturas_de_controle = 1;
                  printf("\n>> Categoria 'Est. Controle' adicionada!\n");
                  break;
                case 3:
                  nova_tarefa.tag.estruturas_de_repeticao = 1;
                  printf("\n>> Categoria 'Est. Repetição' adicionada!\n");
                  break;
                case 4:
                  nova_tarefa.tag.vetores_e_matrizes = 1;
                  printf("\n>> Categoria 'Vetores/Matrizes' adicionada!\n");
                  break;
                case 5:
                  nova_tarefa.tag.manipulacao_de_strings = 1;
                  printf("\n>> Categoria 'Manip. Strings' adicionada!\n");
                  break;
                case 6:
                  nova_tarefa.tag.funcoes_e_modularizacao = 1;
                  printf(
                      "\n>> Categoria 'Funções/Modularização' adicionada!\n");
                  break;
                case 7:
                  nova_tarefa.tag.ponteiros = 1;
                  printf("\n>> Categoria 'Ponteiros' adicionada!\n");
                  break;
                case 8:
                  nova_tarefa.tag.alocacao_dinamica_de_memoria = 1;
                  printf("\n>> Categoria 'Alocação Dinâmica' adicionada!\n");
                  break;
                case 9:
                  nova_tarefa.tag.structs_e_unions = 1;
                  printf("\n>> Categoria 'Structs e Unions' adicionada!\n");
                  break;
                case 10:
                  nova_tarefa.tag.manipulacao_de_arquivos = 1;
                  printf("\n>> Categoria 'Manip. Arquivos' adicionada!\n");
                  break;
                case 0:
                  printf("Seleção de categorias finalizada.\n");
                  break;
                default:
                  mensagem_erro("Opção inválida! Selecione outra opção");
                }
              }
              LIN_SIMPLES;
              criar_tarefa_binario(nova_tarefa);

              break;
            case 2:
              LIN_SIMPLES;
              listar_tarefas();
              break;
            case 3:
              listar_usuarios();
              break;

            case 4:
              printf(">> Digite o ID da tarefa para procurar (0 para sair): ");
              id_achar = ler_inteiro();
              Tarefa achar_tarefa = achar_tarefa_id(id_achar);
              if (achar_tarefa.id == -1) {
                mensagem_erro("A tarefa mencionada não foi encontrada");
              } else {
                mensagem_sucesso("A tarefa foi encontrada!");
                exibir_tarefa_bonita(&achar_tarefa, 'L');
              }

              enter();
              break;
            case 5:
              printf(">> Digite o ID do usuário para procurar (0 para sair): ");
              id_achar = ler_inteiro();
              if (id_achar == 0) {
                printf(">> Parando procura por Usuário... \n");
                enter();
                break;
              }
              Usuario achar_usuario = achar_usuario_id(id_achar);
              if (achar_usuario.id == -1) {
                mensagem_erro("O usuário mencionado não foi encontrado");
              } else {
                mensagem_sucesso("O Usuário foi encontrado!");
                LIN_SIMPLES;
                printf(" %03d   | %-30s | %d\n", achar_usuario.id,
                       achar_usuario.nome, achar_usuario.qtd_tarefas);
                LIN_SIMPLES;
              }
              enter();
              break;

            case 6:
              printf(">> Digite o ID da tarefa para excluir (0 para sair): ");
              id_excluir = ler_inteiro();
              excluir_tarefa(id_excluir);
              break;
            case 7:
              printf(">> Digite o ID do usuário para excluir (0 para sair): ");
              id_excluir = ler_inteiro();

              if (id_excluir == 0) {
                printf(">> Parando exclusão de dados. ");
                enter();
                break;
              }

              // pro adm n se excluir!
              if (id_excluir == usuario_logado.id) {
                mensagem_erro(
                    "Você não pode excluir seu próprio usuário logado!");
              } else {
                excluir_usuario(id_excluir);
              }
              break;
            case 8:
              criar_tarefas_csv();
              break;
            case 9:
              criar_usuarios_csv();
              break;
            case 0:
              printf(">> Saindo...");
              enter();
              break;
            default:
              mensagem_erro("Opção inválida! Selecione outra opção");
              break;
            }
          } while (opcao_adm != 0);

        } else { // Menu USER
          do {
            menu_usuario(usuario_logado);
            opcao_user = ler_inteiro();
            switch (opcao_user) {
            case 1:

              printf("\n>> Digite os filtros para a sua tarefa: \n");
              do {
                printf("> Defina a dificuldade(1-5): ");
                dificuldade = ler_inteiro();
                if (dificuldade < 1 || dificuldade > 5) {
                  mensagem_erro("Dificuldade deve estar entre 1 e 5");
                }
              } while (dificuldade < 1 || dificuldade > 5);
              listar_categorias();
              do {
                printf("> Escolha uma categoria: ");
                categoria = ler_inteiro();
                if (categoria < 1 || categoria > 10) {
                  mensagem_erro("Categoria inválida! Digite entre 1 e 10.");
                }
              } while (categoria < 1 || categoria > 10);

              Tarefa *t;
              t = recomendar(categoria, dificuldade, usuario_logado.id);
              if (t == NULL) {
                mensagem_erro("Não foi achada nenhuma tarefa com esse filtro");
                break;
              }
              exibir_tarefa_bonita(t, 'R');
              printf("Salvar no histórico? (1/0): ");
              opcao_hist = ler_inteiro();
              if (opcao_hist == 1) {
                criar_historico_binario(t->id, usuario_logado.id);
                incrementar_tarefas_concluidas(usuario_logado.id);
                usuario_logado.qtd_tarefas++;
                sprintf(mensagem,
                        "A Tarefa: %s, foi adicionada com sucesso ao seu "
                        "histórico!",
                        t->titulo);
                mensagem_sucesso(mensagem);
                enter();
              } else {
                if (opcao_hist == 0) {
                  printf("A Tarefa: %s, não foi adicionada ao seu histórico",
                         t->titulo);
                  enter();
                } else {
                  mensagem_erro(
                      "Opção inválida! A tarefa não foi salva no histórico");
                }
              }
              if (t != NULL)
                free(t);
              break;
            case 2:
              listar_historico(usuario_logado.id);
              break;
            case 0:
              printf(">> Saindo...");
              enter();
              break;
            default:
              mensagem_erro("Você selecionou uma opção inválida!");
              break;
            }
          } while (opcao_user != 0);
          printf(">> Saindo...\n");
        }
      }
      break;
    case 2:
      do {

        cabecalho("CADASTRO DE USUÁRIO");
        printf("> Digite seus dados para entrar:\n\n");
        printf("Usuário: ");
        ler_texto(nome_login, sizeof(nome_login));
        printf("Senha: ");
        ler_texto(senha_login, sizeof(senha_login));

        if ((verificar_usuario_existente(nome_login)) == FALSE) {
          mensagem_erro("Já possui um usuário cadastrado com esse nome.");
        }
      } while (!(verificar_usuario_existente(nome_login)));

      do {
        printf("\nO usuário será administrador? (1/0): ");
        adm = ler_inteiro();
        if (!(adm == 1 || adm == 0)) {
          mensagem_erro("Digite apenas 1 (Verdadeiro) ou 0 (Falso)!");
        }
      } while (!(adm == 1 || adm == 0));
      if (adm) {
        printf("> Digite a Chave de Admin: ");
        ler_texto(senha_adm, sizeof(senha_adm));
        if (strcmp(senha_adm, chave_adm) == 0) {
          sprintf(mensagem, "O usuário %s, foi cadastrado como administrador!",
                  nome_login);
          mensagem_sucesso(mensagem);
          criar_usuario_binario(nome_login, senha_login, 'A');
          enter();
          break;
        } else {
          mensagem_erro("Senha errada, finalizando menu de cadastro...");
          break;
        }
      } else {
        sprintf(mensagem, "O usuário %s, foi cadastrado!", nome_login);
        mensagem_sucesso(mensagem);
        criar_usuario_binario(nome_login, senha_login, 'P');
        enter();
        break;
      }
      break;
    case 0:
      printf("\n>> Finalizando o processo...\n");
      break;
    default:
      mensagem_erro("Opção inválida! Selecione outra opção");
      break;
    }
  }
}