#include "structs.h"
#include <time.h>
#include <stdio.h>

void handleListActiveRents(BookRent *rents, int *rentsCounterGlobal)
{
  printf("Emprestimos ativos:\n");
  for (int i = 0; i < *rentsCounterGlobal; i++)
  {
    BookRent rent = rents[i];
    struct tm *rentDate = localtime(&rent.rentDate);
    char rentDateBuffer[128];
    strftime(rentDateBuffer, sizeof(rentDateBuffer), "%A, %d de %B, %Y. %H:%M:%S.", rentDate);

    struct tm *devolutionDate = localtime(&rent.devolutionDate);
    char devolutionDateBuffer[128];
    strftime(devolutionDateBuffer, sizeof(devolutionDateBuffer), "%A, %d de %B, %Y. %H:%M:%S.", devolutionDate);

    if (rent.isActive)
    {
      printf("\nId: %d\n"
             "Id do livro: %d\n"
             "Matricula do aluno: %d\n"
             "Data do emprestimo: %s\n"
             "Data prevista de devolucao do livro: %s\n",
             rent.id, rent.bookId, rent.userRegistration, rentDateBuffer, devolutionDateBuffer);
    }
  }
  printf("Pressione enter para continuar...");
  char tempBuffer[32];
  if (fgets(tempBuffer, sizeof(tempBuffer), stdin) == NULL)
  {
    printf("failed to get user input");
  }
}