#include "structs.h"
#include "utils.h"
#include <stdio.h>

int handleIdSearch(Book *books, int *globalBooksCounter);

void handleSearchBook(Book *books, int *globalBooksCounter)
{
  int num;
  char buffer[512];

  while (num != 9)
  {
    printf(
        "\nEscolha uma opcao para fazer a pesquisa:\n"
        "1. Pesquisar por id\n"
        "2. Pesquisar por nome\n"
        "9. Voltar para o menu principal.\n");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
      printf("failed to get user input");
      return;
    }
    sscanf(buffer, "%d", &num);

    switch (num)
    {
    case 1:
      int bookIndex = handleIdSearch(books, globalBooksCounter);
      if (bookIndex == -1)
      {
        printf("\nLivro nao encontrado\n");
        return;
      }
      Book book = books[bookIndex];
      printf("Livro encontrado:\n"
             "Titulo: %s\n"
             "Autor: %s\n"
             "Editora: %s\n"
             "Ano de lancamento: %d\n",
             book.title, book.author, book.publisher, book.releaseYear);
      break;
    case 9:
      printf("\nVoltando para o menu principal.\n");
      break;
    default:
      printf("opcao invalida\n");
      break;
    }
  }
}

int handleIdSearch(Book *books, int *globalBooksCounter)
{
  char buffer[512];
  int bookId;
  printf(
      "\nDigite o id do livro:\n");
  if (fgets(buffer, sizeof(buffer), stdin) == NULL)
  {
    printf("failed to get user input");
    return -1;
  }
  sscanf(buffer, "%d", &bookId);
  int bookIndex = bookLinearSearch(books, *globalBooksCounter, bookId);
  return bookIndex;
}