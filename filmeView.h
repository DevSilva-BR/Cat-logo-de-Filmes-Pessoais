#ifndef FILME_VIEW_H              // Verifica se o identificador FILME_VIEW_H já foi definido
#define FILME_VIEW_H              // Define o identificador FILME_VIEW_H para evitar inclusões múltiplas

#include "filmeModel.h"          // Inclui o arquivo de cabeçalho com a definição da struct Filme

// Função que exibe as informações de um único filme passado como ponteiro
void exibirFilme(const Filme *f);

// Função que exibe todos os filmes cadastrados (possivelmente usando uma lista global)
void exibirListaFilmes();

// Função utilitária para pausar a tela, normalmente até o usuário pressionar uma tecla
void pauseTela();

// Função utilitária para limpar o console (comandos diferentes dependendo do SO)
void limparTela();

// Função que exibe o menu de opções e retorna a escolha do usuário
int opcao();

#endif
