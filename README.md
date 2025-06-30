# Projeto: Catálogo de Filmes Pessoais

## 1. Contexto

Este projeto foi desenvolvido para a disciplina de Linguagem de Programação em C, na Fatec Arthur de Azevedo - Mogi Mirim, sob a orientação do Prof. Me. Marcos Roberto de Moraes. O objetivo é aplicar conceitos de estruturas de dados, manipulação de arquivos e práticas de desenvolvimento de software.

## 2. Tema Escolhido

Sistema de gerenciamento de catálogo de filmes pessoais, permitindo controlar filmes por informações como ID, título, diretor, ano de lançamento, gênero e avaliação (0-10).

## 3. Funcionalidades Implementadas

* **Inserção de Filmes**: Adiciona novos filmes à coleção com todos os campos obrigatórios.
* **Busca por Diretor**: Localiza filmes pelo nome do diretor.
* **Filtrar por Gênero**: Exibe todos os filmes de um gênero específico.
* **Atualização de Informações**: Permite editar dados de filmes existentes (título, diretor, gênero, ano e avaliação).
* **Remoção de Filmes**: Remove um filme cadastrado pelo seu ID.
* **Listagem de Filmes**: Mostra todos os filmes ordenados por ano ou por título.
* **Persistência em Arquivo Texto**: Salva e carrega dados em formato `campo:valor;`, garantindo que a coleção seja mantida entre execuções.

## 4. Estrutura de Dados

* Utiliza um vetor global de structs `Filme`, com alocação estática até `MAX_FILMES`.
* Cada `Filme` possui campos:

  ```c
  typedef struct {
      int id;
      char titulo[100];
      char diretor[50];
      char genero[30];
      int ano;
      int avaliacao; // 0 a 10
  } Filme;
  ```
* Variáveis globais:

  ```c
  extern Filme filmes[MAX_FILMES];
  extern int totalFilmes;
  ```

## 5. Instalação e Compilação

1. **Clone o repositório:**

   ```bash
   git clone [LINK_DO_REPOSITORIO]
   cd [PASTA_DO_PROJETO]
   ```
2. **Compile o projeto:**

   ```bash
   gcc -o catalogo_filmes main.c filmeController.c filmeView.c filmeModel.c -Wall
   ```

## 6. Execução e Testes

1. **Execute o programa:**

   ```bash
   ./catalogo_filmes
   ```
2. **Uso interativo:**

   * Siga as instruções do menu para inserir, buscar, atualizar, remover ou listar filmes.
   * Os dados serão persistidos no arquivo `filmes.txt` em formato `campo:valor;`.

## 7. Autores

* Jemison Da silva
