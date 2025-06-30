#include <stdio.h>
#include <stdlib.h>
#include "filmeView.h"        // Cabeçalho da view (declaração das funções de exibição)
#include "filmeModel.h"       // Cabeçalho do modelo (acesso à struct Filme e lista de filmes)

// Exibe os dados de um filme na tela
void exibirFilme(const Filme *f) {
    printf("ID: %d | Titulo: %s | Diretor: %s | Genero: %s | Ano: %d | Avaliacao: %d/10\n",
           f->id, f->titulo, f->diretor, f->genero, f->ano, f->avaliacao);
}

// Exibe a lista completa de filmes cadastrados
void exibirListaFilmes() {
    if (totalFilmes == 0) {                                // Verifica se há filmes cadastrados
        printf("Nenhum filme cadastrado.\n");
        return;
    }

    printf("\n==== Lista de Filmes ====\n");
    for (int i = 0; i < totalFilmes; i++) {                // Itera sobre o array de filmes
        exibirFilme(&filmes[i]);                           // Exibe cada filme
    }
}

// Limpa a tela do console, compatível com Windows e Unix
void limparTela() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

// Pausa a execução até o usuário pressionar ENTER
void pauseTela() {
    printf("\nPressione ENTER para continuar...");
    fflush(stdout);                                       // Garante que o texto será exibido antes da pausa
    int c;
    while ((c = getchar()) != '\n' && c != EOF);          // Limpa o buffer do teclado
    getchar();                                            // Aguarda o ENTER
}

// Exibe o menu principal e retorna a opção escolhida pelo usuário
int opcao(){
    int op;
    limparTela();                                         // Limpa a tela antes de mostrar o menu
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
    scanf("%d", &op);                                      // Lê a escolha do usuário

    if (op < 0 || op > 8) {                                // Valida a opção
        printf("Opcao invalida! Tente novamente.\n");
        pauseTela();                                       // Pausa para leitura da mensagem
        return -1;                                         // Retorna -1 em caso de erro
    }

    return op;                                             // Retorna a opção válida escolhida
}
