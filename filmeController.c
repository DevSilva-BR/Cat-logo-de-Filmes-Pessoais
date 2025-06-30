#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filmeModel.h"
#include "filmeView.h"
#include "filmeController.h"



/**
 * carregarFilmes(); func~ção para carrega os filmes vindo do filme.txt
 */
void carregarFilmes() {
    FILE *file = fopen(ARQUIVO_FILMES, "r");  // Abre o arquivo para leitura
    if (!file) return;                        // Se não conseguir abrir, encerra a função

    char linha[500];
    while (fgets(linha, sizeof(linha), file) && totalFilmes < MAX_FILMES) {
        Filme *f = &filmes[totalFilmes];      // Aponta para a próxima posição disponível
        char *token = strtok(linha, ";");     // Quebra a linha em tokens separados por ;

        while (token) {
            char *sep = strchr(token, ':');   // Localiza o separador de campo ':'
            if (sep) {
                *sep = '\0';                  // Quebra a string no caractere ':'
                char *valor = sep + 1;

                // Compara o campo e preenche os dados
                if (strcmp(token, "id") == 0) f->id = atoi(valor);
                else if (strcmp(token, "titulo") == 0) strncpy(f->titulo, valor, sizeof(f->titulo));
                else if (strcmp(token, "diretor") == 0) strncpy(f->diretor, valor, sizeof(f->diretor));
                else if (strcmp(token, "genero") == 0) strncpy(f->genero, valor, sizeof(f->genero));
                else if (strcmp(token, "ano") == 0) f->ano = atoi(valor);
                else if (strcmp(token, "avaliacao") == 0) f->avaliacao = atoi(valor);
            }
            token = strtok(NULL, ";"); // Avança para o próximo campo
        }
        totalFilmes++; // Incrementa o total de filmes carregados
    }
    fclose(file); // Fecha o arquivo
}
/**
 * @brief Salva a lista de filmes no arquivo definido por ARQUIVO_FILMES.
 *
 * Abre o arquivo em modo escrita e grava os dados dos filmes no formato
 * chave:valor separados por ponto e vírgula. Caso não consiga abrir o arquivo,
 * imprime mensagem de erro no stderr.
 */
void salvarFilmes() {
    FILE *file = fopen(ARQUIVO_FILMES, "w");  // Abre o arquivo para escrita
    if (!file) {
        perror("Erro ao salvar filmes");
        return;
    }

    // Salva cada filme no formato "chave:valor;"
    for (int i = 0; i < totalFilmes; i++) {
        Filme *f = &filmes[i];
        fprintf(file, "id:%d;titulo:%s;diretor:%s;genero:%s;ano:%d;avaliacao:%d;\n",
                f->id, f->titulo, f->diretor, f->genero, f->ano, f->avaliacao);
    }

    fclose(file); // Fecha o arquivo
}

/**
 * @brief lista de filmes no arquivo definido por ARQUIVO_FILMES.
 *
 * Abre o arquivo em modo escrita e mostra no terminal
 */
int listFilmes() {
    exibirListaFilmes();
    return 1;
}
/**
 * @brief Buscar de filmes com base no paramento diretor no arquivo definido por ARQUIVO_FILMES.
 *
 */
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
/**
 * @brief Busca e exibe filmes pelo gênero informado pelo usuário.
 *
 * Solicita ao usuário a entrada do gênero e procura todos os filmes cujo
 * campo 'genero' contenha a string informada. Exibe os filmes encontrados.
*/
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
/**
 * @brief Adiciona um novo filme ao catálogo.
 *
 * Solicita dados do usuário para criar um novo filme e adiciona ao array global
 * 'filmes', atualizando o arquivo com salvarFilmes(). Verifica se o limite máximo
 * de filmes foi atingido antes de adicionar.
 */
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
/**
 * @brief Edita os dados de um filme existente.
 *
 * Solicita o ID do filme, verifica validade, e permite editar título, diretor,
 * gênero, ano e avaliação. Campos podem ser mantidos se o usuário apertar ENTER
 * sem digitar novos dados.
 *
 */
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
/**
 * @brief Atualiza apenas a avaliação de um filme pelo seu ID.
 *
 * Solicita o ID do filme, valida e permite atualizar a avaliação com valor entre
 * 0 e 10. Após atualização, salva os dados no arquivo.
*/
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
/**
 * @brief Função de comparação para ordenar filmes por ano (crescente).
 *
 * Se os anos forem iguais, ordena por título em ordem alfabética.
 *
 * @param a Ponteiro para o primeiro filme.
 * @param b Ponteiro para o segundo filme.
 * @return int Valor negativo se a < b, positivo se a > b, zero se iguais.
 */
int compararAno(const void *a, const void *b) {
    Filme *fa = (Filme *)a;
    Filme *fb = (Filme *)b;
    if (fa->ano != fb->ano)
        return fa->ano - fb->ano;
    return strcmp(fa->titulo, fb->titulo);
}
/**
 * @brief Função de comparação para ordenar filmes por título (ordem alfabética).
 *
 * @param a Ponteiro para o primeiro filme.
 * @param b Ponteiro para o segundo filme.
 */
int compararTitulo(const void *a, const void *b) {
    Filme *fa = (Filme *)a;
    Filme *fb = (Filme *)b;
    return strcmp(fa->titulo, fb->titulo);
}
/**
 * @brief Lista os filmes ordenados por ano.
 *
 * Cria uma cópia do array de filmes, ordena por ano usando qsort e exibe a lista.
 * Se não houver filmes cadastrados, exibe mensagem informativa.
 *
 */
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
/**
 * @brief Lista os filmes ordenados por título.
 *
 * Cria uma cópia do array de filmes, ordena por título usando qsort e exibe a lista.
 * Se não houver filmes cadastrados, exibe mensagem informativa.
  */
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
