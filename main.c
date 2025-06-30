#include <stdio.h>
#include "filmeController.h"
#include "filmeView.h"

int main() {
    carregarFilmes();

    int op;
    do {
        op = opcao();

        switch(op) {
            case 1:
                listFilmes();
                pauseTela();
                break;
            case 2:
                buscarFilme();
                pauseTela();
                break;
            case 3:
                buscarFilmeGenero();
                pauseTela();
                break;
            case 4:
                adicionaFilme();
                pauseTela();
                break;
            case 5:
                editarFilme();
                pauseTela();
                break;
            case 6:
                atualizarAvaliacao();
                pauseTela();
                break;
            case 7:
                listarPorAno();
                pauseTela();
                break;
            case 8:
                listarPorTitulo();
                pauseTela();
                break;
            case 0:
                printf("Saindo...\n");
                break;
        }
    } while(op != 0);

    return 0;
}
