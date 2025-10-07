#include <stdio.h>
#include <string.h>
#include "firstMenuMethods.h"
#include "fileHandling.h"
#include "structs.h"
#include "utils.h"

int main()
{
  int studentsCounter_global = 0;
  Student *students_global = getStudents(&studentsCounter_global);
  /* Student student = {
      .course = "Egenharia",
      .name = "Vitor",
      .phoneNumber = "0990",
      .registration = 1,
      .registrationDate = 12345,
  };
  addStudentToFile(student); */
  char buffer[128];
  int num;
  while (num != 0)
  {
    printf(
        "\nEscolha um numero para continuar:\n"
        "1. Adicionar estudante.\n"
        "2. Adicionar livro.\n"
        "3. Alugar livro para estudante.\n"
        "4. Sair.\n");

    if (fgets(buffer, 128, stdin) == NULL)
      return 1;
    sscanf(buffer, "%d", &num);
    switch (num)
    {
    case 1:
      handleAddStudent(students_global, &studentsCounter_global);
      break;
    case 2:
      printf("voce escolheu o numero 2");
      break;
    case 3:
      printf("voce escolheu o numero 3");
      break;
    case 4:
      printf("Saindo...");
      num = 0;
      break;

    default:
      printf("\nOpcao invalida\n");
      break;
    }
  }
  return 0;
}