#include "funcoes.h"
#include "menu.h"


int gerar_proximo_id(char acao) {
    
    struct Controle {
        int ultimo_id_tarefa;
        int ultimo_id_usuario;
    } controle;

    FILE *arquivo = fopen("config.dat", "rb+");

    if (arquivo == NULL) {
        arquivo = fopen("config.dat", "wb+");
        if (arquivo == NULL) return 1; 

        
        int maior_t = 0;
        FILE *ft = fopen("tarefas.dat", "rb");
        if (ft != NULL) {
            Tarefa t;
            while(fread(&t, sizeof(Tarefa), 1, ft)) {
                if(t.id > maior_t) maior_t = t.id;
            }
            fclose(ft);
        }

        int maior_u = 0;
        FILE *fu = fopen("usuarios.dat", "rb");
        if (fu != NULL) {
            Usuario u;
            while(fread(&u, sizeof(Usuario), 1, fu)) {
                if(u.id > maior_u) maior_u = u.id;
            }
            fclose(fu);
        }


        controle.ultimo_id_tarefa = maior_t;
        controle.ultimo_id_usuario = maior_u;
        fwrite(&controle, sizeof(struct Controle), 1, arquivo);
        rewind(arquivo);
    } else {
        fread(&controle, sizeof(struct Controle), 1, arquivo);
    }

    int id_gerado = 0;

    if (acao == 'T' || acao == 't') {
        controle.ultimo_id_tarefa++; 
        id_gerado = controle.ultimo_id_tarefa;
    } else {
        controle.ultimo_id_usuario++;
        id_gerado = controle.ultimo_id_usuario;
    }

    rewind(arquivo);
    fwrite(&controle, sizeof(struct Controle), 1, arquivo);
    fclose(arquivo);

    return id_gerado;
}


Tarefa achar_tarefa_id(int id_t) {

    FILE *arquivo = fopen("tarefas.dat", "rb"); 
    Tarefa t;
    t.id = -1; 

    if (arquivo == NULL) {
        mensagem_erro("Nenhuma tarefa foi cadastrada.");
        return t; 
    }

    while (fread(&t, sizeof(Tarefa), 1, arquivo)) {
        if (t.id == id_t) {
            fclose(arquivo); 
            return t;        
        }
    }

    fclose(arquivo); 
    t.id = -1;       
    return t;
}

Usuario achar_usuario_id(int id_u) {

    FILE *arquivo = fopen("usuarios.dat", "rb"); 
    Usuario u;
    u.id = -1; 

    if (arquivo == NULL) {
        mensagem_erro("Nenhum usuário foi cadastrado.");
        return u; 
    }

    while (fread(&u, sizeof(Usuario), 1, arquivo)) {
        if (u.id == id_u) {
            fclose(arquivo); 
            return u;        
        }
    }

    fclose(arquivo); 
    u.id = -1;       
    return u;

}

void criar_tarefa_binario(Tarefa t) {
    FILE *tarefa = fopen("tarefas.dat", "ab"); // "a" pois se não existir cria, e se existir atualiza
    if(tarefa==NULL) {
        mensagem_erro("Erro ao abrir o arquivo!");
        return;
    }   //&var,tamanho,quantidade,arquivo 
    fwrite(&t, sizeof(Tarefa), 1, tarefa);
    fclose(tarefa);
    mensagem_sucesso("A tarefa foi adicionada!");
    enter();
    return;
}

void criar_tarefas_csv() {
    FILE *tarefa_binario = fopen("tarefas.dat", "rb");
    if(tarefa_binario==NULL) {
        mensagem_erro("Nenhuma tarefa foi cadastrada ainda.");
        return;
    }
    FILE *tarefa_csv = fopen("tarefa.csv", "w");
    Tarefa t;
    //cabeçalho
    fprintf(tarefa_csv, "ID;Titulo;Descricao;Dificuldade;ES;Controle;Repeticao;Vetores;Strings;Funcoes;Ponteiros;Alocacao;Structs;Arquivos\n");
    while(fread(&t, sizeof(Tarefa), 1, tarefa_binario)) {

        //para não afetar a visualizaçãoo do CSV
        limpa_texto_csv(t.titulo);
        limpa_texto_csv(t.descricao);

        fprintf(tarefa_csv,"%d;%s;%s;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
        t.id,
        t.titulo,
        t.descricao,
        t.dificuldade,
        //categorias
        t.tag.fundamentos_entrada_saida,
        t.tag.estruturas_de_controle,
        t.tag.estruturas_de_repeticao,
        t.tag.vetores_e_matrizes,
        t.tag.manipulacao_de_strings,
        t.tag.funcoes_e_modularizacao,
        t.tag.ponteiros,
        t.tag.alocacao_dinamica_de_memoria,
        t.tag.structs_e_unions,
        t.tag.manipulacao_de_arquivos);
    }
    fclose(tarefa_binario);
    fclose(tarefa_csv);
    mensagem_sucesso("O arquivo 'tarefas.csv' foi criado!");
    enter();
    return;
}

void criar_usuario_binario(char nome[], char senha[], char tipo) {
    FILE *usuario = fopen("usuarios.dat", "ab");
    if(usuario==NULL) {
        mensagem_erro("Erro ao abrir o arquivo!");
        return;
    }

    Usuario u;
    if (tipo=='A') u.admin = TRUE;
    if (tipo=='P') u.admin = FALSE;

    strcpy(u.nome, nome);
    strcpy(u.senha, senha);

    u.qtd_tarefas = 0;
    u.id = gerar_proximo_id('U');

    fwrite(&u, sizeof(Usuario), 1, usuario);
    fclose(usuario);
    return;
}

void criar_usuarios_csv() {
    FILE *usuario_binario = fopen("usuarios.dat", "rb");
    if(usuario_binario==NULL) {
        mensagem_erro("Nenhum usuário foi cadastrado ainda.");
        return;
    }
    FILE *usuario_csv = fopen("usuarios.csv", "w");
    Usuario u;
    
    fprintf(usuario_csv, "ID;Nome;Senha;QuantidadeTarefas;ehAdmin\n");
    while(fread(&u, sizeof(Usuario), 1, usuario_binario)) {

        limpa_texto_csv(u.nome);
        limpa_texto_csv(u.senha);

        fprintf(usuario_csv, "%d;%s;%s;%d;%d\n",
                u.id,
                u.nome,
                u.senha,
                u.qtd_tarefas,
                u.admin);
    }
    fclose(usuario_binario);
    fclose(usuario_csv);
    mensagem_sucesso("O arquivo 'usuarios.csv' foi criado!");
    enter();
    return;
}

void criar_historico_binario(int t_id, int u_id) {
    FILE *historico = fopen("historico.dat", "ab");
    if(historico==NULL) {
        mensagem_erro("Erro ao abrir o arquivo!");
        return;
    }
    Historico registro;
    registro.id_usuario = u_id;
    registro.id_tarefa = t_id;
    fwrite(&registro, sizeof(Historico), 1, historico);
    fclose(historico);

    return;
}

void listar_usuarios() {
    FILE *arquivo = fopen("usuarios.dat", "rb");

    if(arquivo==NULL) {
        mensagem_erro("Nenhum usuário foi cadastrado, ou o arquivo não foi encontrado.");
        return;
    }
    Usuario u;

    cabecalho("LISTA DE USUÁRIOS CADASTRADOS");
    printf(" %-5s | %-30s | %-15s\n", "ID", "NOME", "TAREFAS CONCLUÍDAS");
    LIN_SIMPLES;
    while (fread(&u, sizeof(Usuario), 1, arquivo)) {
        printf(" %03d   | %-30s | %d\n", u.id, u.nome, u.qtd_tarefas);
    }
    LIN_SIMPLES;
    fclose(arquivo);
    //pausa pro adm conseguir ler antes de voltar pro
    enter();
    return;
}

void listar_tarefas() {
    FILE *arquivo = fopen("tarefas.dat", "rb");
    if(arquivo==NULL) {
        mensagem_erro("Nenhuma tarefa foi cadastrada, ou o arquivo não foi encontrado");
        return;
    }

    Tarefa t;
    cabecalho("LISTA DE TAREFAS CADASTRADAS");
    while(fread(&t, sizeof(Tarefa), 1, arquivo)) {
        exibir_tarefa_bonita(&t, 'L');
    }
    fclose(arquivo);
    enter();
}

void listar_historico(int u_id) {
    FILE *historico = fopen("historico.dat", "rb");

    if (historico==NULL) {
        mensagem_erro("Não há nenhum dado gravado no histórico");
        return;
    }

    int achou = FALSE;

    Historico h;
    Tarefa t;

    while (fread(&h, sizeof(Historico), 1, historico)) {
        if(h.id_usuario==u_id) {
            t = achar_tarefa_id(h.id_tarefa);
            if (t.id == -1) {
                mensagem_erro("Uma tarefa salva não existe mais");
                continue;
            }
            exibir_tarefa_bonita(&t,'L');
            achou = TRUE;
        }
    }

    if (!(achou)) {
        mensagem_erro("O usuário não possui tarefas salvas no histórico.");
    }
    fclose(historico);
    enter();
    return;
}

Usuario validacao_login(char login[], char senha[]) {
    Usuario user_lido;
    FILE *arquivo = fopen("usuarios.dat", "rb");
    if(arquivo==NULL) {
        user_lido.id = -1;
        return user_lido;
    }
    while(fread(&user_lido, sizeof(Usuario), 1 , arquivo)) {
        if((strcmp(user_lido.nome, login) == 0) && (strcmp(user_lido.senha, senha) == 0)) {
            fclose(arquivo);
            return user_lido;
        }
    }
    fclose(arquivo);
    user_lido.id = -1;
    return user_lido;
}

int verificar_usuario_existente(char login[]) {
    Usuario user_lido;
    FILE *arquivo = fopen("usuarios.dat", "rb");
    if(arquivo==NULL) {
        return 1;
    }
    while(fread(&user_lido, sizeof(Usuario), 1 , arquivo)) {
        if((strcmp(user_lido.nome, login) == 0)) {
            fclose(arquivo);
            return 0;
        }
    }
    fclose(arquivo);
    return 1;
}

int ja_fez(int id_t, int id_u) {
    FILE *arquivo = fopen("historico.dat", "rb");
    if (arquivo==NULL) {
        return FALSE;
    }

    Historico aux;

    while (fread(&aux, sizeof(Historico), 1, arquivo)) {
        if (aux.id_usuario == id_u && aux.id_tarefa == id_t) {
            fclose(arquivo);
            return TRUE;
        }
    }

    fclose(arquivo);
    return FALSE;
}

Tarefa *recomendar(int categoria, int nivel_dificuldade, int user_logado) {
    int tem_categoria =  FALSE;
    FILE *arquivo = fopen("tarefas.dat", "rb");
    if (arquivo==NULL) return NULL;

    Tarefa *tarefa_R = (Tarefa*)malloc(sizeof(Tarefa));
    if (tarefa_R==NULL) {
        mensagem_erro("Erro na alocação de memória!");
        return NULL;
    }

    while (fread(tarefa_R, sizeof(Tarefa), 1, arquivo)) {
        if (tarefa_R->dificuldade == nivel_dificuldade) {
            switch (categoria)
            {   
                case 1: tem_categoria = tarefa_R->tag.fundamentos_entrada_saida; break;
                case 2: tem_categoria = tarefa_R->tag.estruturas_de_controle; break;
                case 3: tem_categoria = tarefa_R->tag.estruturas_de_repeticao; break; // 1/0
                case 4: tem_categoria = tarefa_R->tag.vetores_e_matrizes; break;
                case 5: tem_categoria = tarefa_R->tag.manipulacao_de_strings; break;
                case 6: tem_categoria = tarefa_R->tag.funcoes_e_modularizacao; break;
                case 7: tem_categoria = tarefa_R->tag.ponteiros; break;
                case 8: tem_categoria = tarefa_R->tag.alocacao_dinamica_de_memoria; break;
                case 9: tem_categoria = tarefa_R->tag.structs_e_unions; break;
                case 10: tem_categoria = tarefa_R->tag.manipulacao_de_arquivos; break;
            }
            if (tem_categoria) {
                if (!ja_fez(tarefa_R->id, user_logado)) {
                    fclose(arquivo);
                    return tarefa_R;
                }
            }
        }
    }
    free(tarefa_R);
    fclose(arquivo);
    return NULL;
}

void excluir_tarefa(int id) {
    FILE *arquivo = fopen("tarefas.dat", "rb");
    if (arquivo == NULL) {
        mensagem_erro("Erro ao abrir o arquivo de tarefas!");
        return;
    }

    FILE *temp = fopen("temp_tarefas.dat", "wb");
    if (temp == NULL) {
        fclose(arquivo);
        mensagem_erro("Erro ao criar arquivo temporário!");
        return;
    }

    Tarefa t;
    int encontrou = 0;

    while(fread(&t, sizeof(Tarefa), 1, arquivo)) {
        if (t.id == id) {
            encontrou = 1;

        } else {
            fwrite(&t, sizeof(Tarefa), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrou) {
        remove("tarefas.dat");
        rename("temp_tarefas.dat", "tarefas.dat");
        mensagem_sucesso("Tarefa excluída com sucesso!");
        enter();

    } else {
        remove("temp_tarefas.dat");
        mensagem_erro("Tarefa não encontrada com esse ID.");
    }
}

void excluir_usuario(int id) {
    FILE *arquivo = fopen("usuarios.dat", "rb");
    if (arquivo == NULL) {
        mensagem_erro("Erro ao abrir o arquivo de usuários!");
        return;
    }

    FILE *temp = fopen("temp_usuarios.dat", "wb");
    if (temp == NULL) {
        fclose(arquivo);
        mensagem_erro("Erro ao criar arquivo temporário!");
        return;
    }

    Usuario u;
    int encontrou = 0;

    while(fread(&u, sizeof(Usuario), 1, arquivo)) {
        if (u.id == id) {
            encontrou = 1;
        } else {
            fwrite(&u, sizeof(Usuario), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrou) {
        remove("usuarios.dat");
        rename("temp_usuarios.dat", "usuarios.dat");
        mensagem_sucesso("Usuário excluído com sucesso!");
        enter();
    } else {
        remove("temp_usuarios.dat");
        mensagem_erro("Usuário não encontrado com esse ID.");
    }
}

void incrementar_tarefas_concluidas(int id_usuario) {

    FILE *arquivo = fopen("usuarios.dat", "rb");
    if (arquivo == NULL) return;

    FILE *temp = fopen("temp_usuarios.dat", "wb");
    if (temp == NULL) {
        fclose(arquivo);
        return;
    }

    Usuario u;

    while(fread(&u, sizeof(Usuario), 1, arquivo)) {

        if(u.id == id_usuario) {
            u.qtd_tarefas = u.qtd_tarefas + 1;
        }
        fwrite(&u, sizeof(Usuario), 1, temp);
    }

    fclose(arquivo);
    fclose(temp);
    remove("usuarios.dat");
    rename("temp_usuarios.dat", "usuarios.dat");

}