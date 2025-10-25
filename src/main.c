#include <stdio.h>
#include "structs.h"
#include "fileHandling.h"
#include "firstMenuMethods.h"
#include <locale.h>

int main()
{
  // Initialization of the files in case they are not created yet.
  /*   FILE *booksFile = fopen("livros.txt", "w");
    FILE *usersFile = fopen("usuarios.txt", "w");
    fcloseall(); */
  setlocale(LC_TIME, "pt_BR.UTF-8");
  int studentsCounter_global = 0;
  Student *students_global = getStudents(&studentsCounter_global);

  int booksCounter_global = 0;
  Book *books_global = getBooks(&booksCounter_global);

  int rentsCounter_global = 0;
  BookRent *rents_global = getRents(&rentsCounter_global);
  char buffer[128];
  int num;
  int shouldExit;
  while (shouldExit != 1)
  {
    printf(
        "\nEscolha um numero para continuar:\n"
        "1. Adicionar estudante.\n"
        "2. Adicionar livro.\n"
        "3. Alugar livro para estudante.\n"
        "4. Devolver livro alugado\n"
        "5. Pesquisar livro\n"
        "6. Pesquisar estudante\n"
        "7. Listar emprestimos ativos\n"
        "0. Sair.\n");
    if (fgets(buffer, 128, stdin) == NULL)
    {
      printf("Error getting user input in main menu");
      return 1;
    }
    sscanf(buffer, "%d", &num);
    switch (num)
    {
    case 1:
      students_global = handleAddStudent(students_global, &studentsCounter_global);
      break;
    case 2:
      books_global = handleAddBook(books_global, &booksCounter_global);
      break;
    case 3:
      rents_global = handleRentBook(books_global, students_global, rents_global, &studentsCounter_global, &booksCounter_global, &rentsCounter_global);
      books_global = getBooks(&booksCounter_global);
      break;
    case 4:
      handleBookDevolution(books_global, &booksCounter_global, rents_global, &rentsCounter_global);
      books_global = getBooks(&booksCounter_global);
      rents_global = getRents(&rentsCounter_global);
      break;
    case 5:
      handleSearchBook(books_global, &booksCounter_global);
      break;
    case 6:
      handleSearchStudent(students_global, &studentsCounter_global);
      break;
    case 7:
      handleListActiveRents(rents_global, &rentsCounter_global);
      break;
    case 0:
      shouldExit = 1;
      printf("Saindo...");
      break;

    default:
      printf("\nOpcao invalida\n");
      break;
    }
  }
  return 0;
}