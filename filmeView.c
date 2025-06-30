#include <stdio.h>
#include <stdlib.h>
#include "filmeView.h"
#include "filmeModel.h"

void exibirFilme(const Filme *f) {
    printf("ID: %d | Titulo: %s | Diretor: %s | Genero: %s | Ano: %d | Avaliacao: %d/10\n",
           f->id, f->titulo, f->diretor, f->genero, f->ano, f->avaliacao);
}

void exibirListaFilmes() {
    if (totalFilmes == 0) {
        printf("Nenhum filme cadastrado.\n");
        return;
    }

    printf("\n==== Lista de Filmes ====\n");
    for (int i = 0; i < totalFilmes; i++) {
        exibirFilme(&filmes[i]);
    }
}

void limparTela() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseTela() {
    printf("\nPressione ENTER para continuar...");
    fflush(stdout);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

int opcao(){
    int op;
    limparTela();
    printf("===== Catalogo de Filmes =====\n");
    printf("1 - Listar Filmes\n");
    printf("2 - Buscar por Diretor\n");
    printf("3 - Buscar por Genero\n");
    printf("4 - Adicionar Filme\n");
    printf("5 - Editar Filme\n");
    printf("6 - Atualizar Avaliacao\n");
    printf("7 - Listar por Ano\n");
    printf("8 - Listar por Titulo\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &op);
    if (op < 0 || op > 8) {
        printf("Opcao invalida! Tente novamente.\n");
        pauseTela();
        return -1;
    }
    return op;
}
