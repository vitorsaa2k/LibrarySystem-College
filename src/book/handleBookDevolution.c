#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "fileHandling.h"
#include "utils.h"

void parseRent(BookRent *rent, char *rentToParse);
void printRentToFile(BookRent rent, FILE *file);
void updateRentOnDevolution(int rentId);

void handleBookDevolution(Book *books, int *booksGlobalCounter, BookRent *rents, int *rentsGlobalCounter)
{
  char buffer[128];
  int confirmation;
  int rentId;
  BookRent rentToUpdate;
  while (confirmation != 1)
  {
    printf("\nDigite o id do emprestimo:\n");
    if (fgets(buffer, 100, stdin) == NULL)
      return;
    sscanf(buffer, "%d", &rentId);

    int rentIndex = rentLinearSearch(rents, *rentsGlobalCounter, rentId);
    rentToUpdate = rents[rentIndex];

    printf("\nEmprestimo encontrado:\n Id do emprestimo: %d\n Matricula do aluno: %d\n Id do livro: %d\n Data do emprestimo: %s\n", rentToUpdate.id, rentToUpdate.userRegistration, rentToUpdate.bookId, ctime(&rentToUpdate.rentDate));
    printf("Confirmar devolucao do livro?\n");
    printf("1. Sim\n2. Nao\n");
    if (fgets(buffer, 128, stdin) == NULL)
      return;
    sscanf(buffer, "%d", &confirmation);
  }
  updateRentOnDevolution(rentId);
  incrementBookAvaliableCopies(rentToUpdate.bookId, 1);
  printf("Devolucao do emprestimo \"%d\" feita com sucesso.", rentId);
};

void updateRentOnDevolution(int rentId)
{
  FILE *originalFile = fopen("emprestimos.txt", "r");
  FILE *tempFile = fopen("temp.txt", "w");

  if (originalFile == NULL || tempFile == NULL)
  {
    perror("Error opening the files");
    return;
  }
  char buffer[512];
  BookRent rent;
  int found = 0;

  while (fgets(buffer, sizeof(buffer), originalFile) != NULL)
  {
    parseRent(&rent, buffer);
    if (rent.id == rentId)
    {
      rent.isActive = 0;
      printRentToFile(rent, tempFile);
      found = 1;
    }
    else
    {
      printRentToFile(rent, tempFile);
    }
  }

  fclose(tempFile);
  fclose(originalFile);

  if (!found)
  {
    printf("Rent not found\n");
  }

  if (remove("emprestimos.txt") == 0)
  {
    if (rename("temp.txt", "emprestimos.txt") == 0)
    {
      printf("Successfully changed rent to inactive\n");
    }
  }
  else
  {
    perror("Error removing original file");
  }
}