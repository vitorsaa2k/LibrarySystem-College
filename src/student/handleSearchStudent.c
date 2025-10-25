#include "structs.h"
#include "utils.h"
#include <time.h>
#include <stdio.h>

int handleStudentIdSearch(Student *students, int *globalStudentsCounter);

void handleSearchStudent(Student *students, int *globalStudentsCounter)
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
      int studentIndex = handleStudentIdSearch(students, globalStudentsCounter);
      if (studentIndex == -1)
      {
        printf("\nEstudante nao encontrado\n");
        printf("\nPressione enter pra continuar...");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
          printf("failed to get user input");
          return;
        }
        break;
      }
      Student student = students[studentIndex];

      struct tm *info = localtime(&student.registrationDate);
      char timeBuffer[80];
      strftime(timeBuffer, sizeof(timeBuffer), "%A, %d de %B, %Y. %H:%M:%S.", info);
      printf("\nEstudante encontrado:\n"
             "Matricula: %d\n"
             "Nome: %s\n"
             "Curso: %s\n"
             "Numero de telefone: %s\n"
             "Data de registro: %s\n",
             student.registration, student.name, student.course, student.phoneNumber, timeBuffer);
      printf("\nPressione enter pra continuar...");
      if (fgets(buffer, sizeof(buffer), stdin) == NULL)
      {
        printf("failed to get user input");
        return;
      }
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

int handleStudentIdSearch(Student *students, int *globalStudentsCounter)
{
  char buffer[512];
  int studentId;
  printf(
      "\nDigite a matricula do estudante:\n");
  if (fgets(buffer, sizeof(buffer), stdin) == NULL)
  {
    printf("failed to get user input");
    return -1;
  }
  sscanf(buffer, "%d", &studentId);
  int studentIndex = studentLinearSearch(students, *globalStudentsCounter, studentId);
  return studentIndex;
}