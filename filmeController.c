#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filmeModel.h"
#include "filmeView.h"
#include "filmeController.h"

void carregarFilmes() {
    FILE *file = fopen(ARQUIVO_FILMES, "r");
    if (!file) return;

    char linha[500];
    while (fgets(linha, sizeof(linha), file) && totalFilmes < MAX_FILMES) {
        Filme *f = &filmes[totalFilmes];
        char *token = strtok(linha, ";");

        while (token) {
            char *sep = strchr(token, ':');
            if (sep) {
                *sep = '\0';
                char *valor = sep + 1;

                if (strcmp(token, "id") == 0) f->id = atoi(valor);
                else if (strcmp(token, "titulo") == 0) strncpy(f->titulo, valor, sizeof(f->titulo));
                else if (strcmp(token, "diretor") == 0) strncpy(f->diretor, valor, sizeof(f->diretor));
                else if (strcmp(token, "genero") == 0) strncpy(f->genero, valor, sizeof(f->genero));
                else if (strcmp(token, "ano") == 0) f->ano = atoi(valor);
                else if (strcmp(token, "avaliacao") == 0) f->avaliacao = atoi(valor);
            }
            token = strtok(NULL, ";");
        }
        totalFilmes++;
    }
    fclose(file);
}

void salvarFilmes() {
    FILE *file = fopen(ARQUIVO_FILMES, "w");
    if (!file) {
        perror("Erro ao salvar filmes");
        return;
    }

    for (int i = 0; i < totalFilmes; i++) {
        Filme *f = &filmes[i];
        fprintf(file, "id:%d;titulo:%s;diretor:%s;genero:%s;ano:%d;avaliacao:%d;\n",
                f->id, f->titulo, f->diretor, f->genero, f->ano, f->avaliacao);
    }
    fclose(file);
}

int listFilmes() {
    exibirListaFilmes();
    return 1;
}

int buscarFilme() {
    char nome[50];
    printf("Digite o nome do diretor: ");
    scanf(" %[^\n]", nome);

    int achou = 0;
    for (int i = 0; i < totalFilmes; i++) {
        if (strstr(filmes[i].diretor, nome)) {
            exibirFilme(&filmes[i]);
            achou = 1;
        }
    }
    if (!achou)
        printf("Nenhum filme encontrado para o diretor '%s'.\n", nome);

    return achou;
}

int buscarFilmeGenero() {
    char genero[30];
    printf("Digite o genero: ");
    scanf(" %[^\n]", genero);

    int achou = 0;
    for (int i = 0; i < totalFilmes; i++) {
        if (strstr(filmes[i].genero, genero)) {
            exibirFilme(&filmes[i]);
            achou = 1;
        }
    }
    if (!achou)
        printf("Nenhum filme encontrado para o genero '%s'.\n", genero);

    return achou;
}

int adicionaFilme() {
    if (totalFilmes >= MAX_FILMES) {
        printf("Limite de filmes atingido!\n");
        return 0;
    }

    Filme novo;
    novo.id = totalFilmes + 1;

    printf("Titulo: ");
    scanf(" %[^\n]", novo.titulo);

    printf("Diretor: ");
    scanf(" %[^\n]", novo.diretor);

    printf("Genero: ");
    scanf(" %[^\n]", novo.genero);

    printf("Ano: ");
    scanf("%d", &novo.ano);

    printf("Avaliação (0-10): ");
    scanf("%d", &novo.avaliacao);
    if (novo.avaliacao < 0 || novo.avaliacao > 10) {
        printf("Avaliacao invalida! Definindo para 0.\n");
        novo.avaliacao = 0;
    }

    filmes[totalFilmes++] = novo;
    salvarFilmes();

    printf("Filme adicionado!\n");
    return 1;
}

int editarFilme() {
    int id;
    printf("Digite o ID do filme a editar: ");
    scanf("%d", &id);

    if (id < 1 || id > totalFilmes) {
        printf("ID inválido.\n");
        return 0;
    }

    Filme *f = &filmes[id - 1];
    char buffer[100];
    int novoValor;

    printf("Novo título (ENTER para manter): ");
    getchar();
    fgets(buffer, 100, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(f->titulo, buffer);
    }

    printf("Novo diretor (ENTER para manter): ");
    fgets(buffer, 100, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(f->diretor, buffer);
    }

    printf("Novo genero (ENTER para manter): ");
    fgets(buffer, 100, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(f->genero, buffer);
    }

    printf("Novo ano (0 para manter): ");
    scanf("%d", &novoValor);
    if (novoValor != 0)
        f->ano = novoValor;

    printf("Nova avaliacao (0-10, -1 para manter): ");
    scanf("%d", &novoValor);
    if (novoValor >= 0 && novoValor <= 10)
        f->avaliacao = novoValor;

    salvarFilmes();
    printf("Filme atualizado com sucesso!\n");
    return 1;
}

int atualizarAvaliacao() {
    int id;
    printf("Digite o ID do filme: ");
    scanf("%d", &id);

    if (id < 1 || id > totalFilmes) {
        printf("ID inválido.\n");
        return 0;
    }

    Filme *f = &filmes[id - 1];
    int novaAvaliacao;

    do {
        printf("Nova avaliacao (0-10): ");
        scanf("%d", &novaAvaliacao);
        if (novaAvaliacao < 0 || novaAvaliacao > 10)
            printf("Avaliação deve ser entre 0 e 10.\n");
    } while (novaAvaliacao < 0 || novaAvaliacao > 10);

    f->avaliacao = novaAvaliacao;
    salvarFilmes();
    printf("Avaliacaoo atualizada com sucesso!\n");
    return 1;
}

int compararAno(const void *a, const void *b) {
    Filme *fa = (Filme *)a;
    Filme *fb = (Filme *)b;
    if (fa->ano != fb->ano)
        return fa->ano - fb->ano;
    return strcmp(fa->titulo, fb->titulo);
}

int compararTitulo(const void *a, const void *b) {
    Filme *fa = (Filme *)a;
    Filme *fb = (Filme *)b;
    return strcmp(fa->titulo, fb->titulo);
}

int listarPorAno() {
    if (totalFilmes == 0) {
        printf("Nenhum filme cadastrado.\n");
        return 0;
    }

    Filme ordenados[MAX_FILMES];
    memcpy(ordenados, filmes, sizeof(Filme) * totalFilmes);
    qsort(ordenados, totalFilmes, sizeof(Filme), compararAno);

    printf("\n==== Filmes Ordenados por Ano ====\n");
    for (int i = 0; i < totalFilmes; i++) {
        exibirFilme(&ordenados[i]);
    }
    return 1;
}

int listarPorTitulo() {
    if (totalFilmes == 0) {
        printf("Nenhum filme cadastrado.\n");
        return 0;
    }

    Filme ordenados[MAX_FILMES];
    memcpy(ordenados, filmes, sizeof(Filme) * totalFilmes);
    qsort(ordenados, totalFilmes, sizeof(Filme), compararTitulo);

    printf("\n==== Filmes Ordenados por Título ====\n");
    for (int i = 0; i < totalFilmes; i++) {
        exibirFilme(&ordenados[i]);
    }
    return 1;
}
