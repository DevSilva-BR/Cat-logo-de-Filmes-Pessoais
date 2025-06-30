#include <stdio.h>                  // Biblioteca padrão de entrada e saída
#include "filmeController.h"       // Arquivo de cabeçalho que contém funções relacionadas à lógica e dados dos filmes (Model/Controller)
#include "filmeView.h"             // Arquivo de cabeçalho com funções de interação com o usuário (View)

int main() {
    carregarFilmes();              // Carrega os filmes previamente salvos (geralmente de um arquivo)

    int op;                        // Variável para armazenar a opção do menu selecionada pelo usuário
    do {
        op = opcao();              // Exibe o menu e recebe a opção escolhida pelo usuário

        switch(op) {               // Estrutura de decisão baseada na opção do usuário
            case 1:
                listFilmes();      // Lista todos os filmes cadastrados
                pauseTela();       // Pausa a tela para que o usuário possa ver a saída
                break;
            case 2:
                buscarFilme();     // Permite buscar um filme pelo título
                pauseTela();
                break;
            case 3:
                buscarFilmeGenero(); // Permite buscar filmes por gênero
                pauseTela();
                break;
            case 4:
                adicionaFilme();   // Adiciona um novo filme ao catálogo
                pauseTela();
                break;
            case 5:
                editarFilme();     // Edita os dados de um filme já cadastrado
                pauseTela();
                break;
            case 6:
                atualizarAvaliacao(); // Atualiza a nota/avaliação de um filme
                pauseTela();
                break;
            case 7:
                listarPorAno();    // Lista os filmes ordenados por ano de lançamento
                pauseTela();
                break;
            case 8:
                listarPorTitulo(); // Lista os filmes ordenados por título
                pauseTela();
                break;
            case 0:
                printf("Saindo...\n"); // Mensagem de encerramento do programa
                break;
        }
    } while(op != 0);              // Continua executando até o usuário escolher sair (opção 0)

    return 0;
}
