#ifndef FILME_MODEL_H
#define FILME_MODEL_H

#define MAX_FILMES 100
#define ARQUIVO_FILMES "filmes.txt"

typedef struct {
    int id;
    char titulo[100];
    char diretor[50];
    char genero[30];
    int ano;
    int avaliacao; // 0 a 10
} Filme;

extern Filme filmes[MAX_FILMES];
extern int totalFilmes;

void carregarFilmes();
void salvarFilmes();

#endif
