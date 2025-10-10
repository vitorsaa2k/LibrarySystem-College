#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "fileHandling.h"
#include "utils.h"

int addBook(Book book, Book *books, int *booksGlobalCounter)
{
  Book *temp = (Book *)realloc(books, (*booksGlobalCounter + 1) * sizeof(Book));

  if (temp == NULL)
  {
    perror("Failed to resize memory for books array");
  }
  else
  {
    books = temp;
    books[*booksGlobalCounter] = book;
    *booksGlobalCounter += 1;
  }
  if (addBookToFile(book))
  {
    printf("\nLivro: \"%s\" adicionado com sucesso\n", book.title);
    return 0;
  }
}

void handleAddBook(Book *books, int *booksGlobalCounter)
{
  char title[100];
  char author[80];
  char publisher[60];
  int releaseYear;
  int totalCopies;
  char buffer[128];
  int confirmation;

  while (confirmation != 1)
  {
    printf("\nDigite os dados do livro um por um:\n");

    printf("Nome do livro:\n");
    if (fgets(title, 100, stdin) == NULL)
      return;
    title[strcspn(title, "\n")] = '\0';
    printf("Nome do autor\n");
    if (fgets(author, 80, stdin) == NULL)
      return;
    author[strcspn(author, "\n")] = '\0';

    printf("Nome da editora:\n");
    if (fgets(publisher, 60, stdin) == NULL)
      return;
    publisher[strcspn(publisher, "\n")] = '\0';

    printf("Ano de lancamento:\n");
    if (fgets(buffer, 128, stdin) == NULL)
      return;
    sscanf(buffer, "%d", &releaseYear);

    printf("Quantas copias deseja adicionar?\n");
    if (fgets(buffer, 128, stdin) == NULL)
      return;
    sscanf(buffer, "%d", &totalCopies);

    printf("\nEsses sao os dados especificados, confirmar?\n Nome do livro: %s\n Autor: %s\n Nome da editora: %s\n Ano de lancamento: %d\n", title, author, publisher, releaseYear);
    printf("1. Sim\n2. Nao\n");
    if (fgets(buffer, 128, stdin) == NULL)
      return;
    sscanf(buffer, "%d", &confirmation);
  }
  Book book = {
      .id = *booksGlobalCounter + 1,
      .releaseYear = releaseYear,
      .avaliableCopies = totalCopies,
      .timesRent = 0};

  strncpy(book.title, title, sizeof(title));
  book.title[sizeof(title)] = '\0';

  strncpy(book.author, author, sizeof(book.author));
  book.author[sizeof(author)] = '\0';

  strncpy(book.publisher, publisher, sizeof(book.publisher));
  book.publisher[sizeof(publisher)] = '\0';

  addBook(book, books, booksGlobalCounter);
};