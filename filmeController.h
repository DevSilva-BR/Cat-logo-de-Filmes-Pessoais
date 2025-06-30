#ifndef FILME_CONTROLLER_H       // Verifica se o identificador já foi definido
#define FILME_CONTROLLER_H       // Define o identificador para evitar múltiplas inclusões

// Função que carrega os dados dos filmes do arquivo (geralmente usada na inicialização)
void carregarFilmes();

// Função que salva os dados dos filmes no arquivo (usada após alterações)
void salvarFilmes();

// Exibe todos os filmes cadastrados
int listFilmes();

// Permite buscar um filme pelo título ou parte dele
int buscarFilme();

// Permite buscar filmes por um gênero específico
int buscarFilmeGenero();

// Adiciona um novo filme ao catálogo
int adicionaFilme();

// Edita os dados de um filme já existente
int editarFilme();

// Atualiza apenas a avaliação (nota) de um filme específico
int atualizarAvaliacao();

// Lista os filmes filtrando por ano de lançamento
int listarPorAno();

// Lista os filmes em ordem alfabética de título
int listarPorTitulo();

#endif
