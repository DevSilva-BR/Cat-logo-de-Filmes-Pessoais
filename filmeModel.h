#ifndef FILME_MODEL_H             // Verifica se o cabeçalho já foi incluído
#define FILME_MODEL_H             // Define o identificador para evitar inclusões múltiplas

#define MAX_FILMES 100            // Define o número máximo de filmes que podem ser armazenados
#define ARQUIVO_FILMES "filmes.txt" // Nome do arquivo onde os filmes serão salvos/carregados

// Define a estrutura que representa um filme
typedef struct {
    int id;                      // Identificador único do filme
    char titulo[100];           // Título do filme
    char diretor[50];           // Nome do diretor
    char genero[30];            // Gênero do filme
    int ano;                    // Ano de lançamento
    int avaliacao;              // Avaliação do filme (de 0 a 10)
} Filme;

// Declaração de um array global que armazena os filmes
extern Filme filmes[MAX_FILMES];    // `extern` indica que a variável será definida em outro arquivo (filmeModel.c)
extern int totalFilmes;             // Contador global de filmes cadastrados

// Função responsável por carregar os filmes do arquivo para a memória
void carregarFilmes();

// Função responsável por salvar os filmes da memória no arquivo
void salvarFilmes();

#endif
