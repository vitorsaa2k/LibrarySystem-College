#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "fileHandling.h"

int bookLinearSearch(Book *arr, int n, int key);
long long addSevenDaysToRawTime(long long *rawtime);
long long getCurrentRawTime();
int studentLinearSearch(Student *arr, int n, int key);

BookRent *addRent(BookRent rent, BookRent *rents, int *rentsGlobalCounter)
{
  BookRent *temp = (BookRent *)realloc(rents, (*rentsGlobalCounter + 1) * sizeof(BookRent));

  if (temp == NULL)
  {
    perror("Failed to resize memory for books array");
  }
  else
  {
    temp[*rentsGlobalCounter] = rent;
    rents = temp;
    *rentsGlobalCounter += 1;
  };
  if (addRentToFile(rent) == 1)
  {
    printf("\nEmprestimo: \"%d\" adicionado com sucesso\n", rent.id);
    return temp;
  }
  printf("Failed to add rent");
  return rents;
}

BookRent *handleRentBook(Book *books, Student *students, BookRent *rents, int *studentsCounterGlobal, int *booksCounterGlobal, int *rentsCounterGlobal)
{
  char buffer[128];
  int studentIndex;
  int bookIndex;

  int registrationToSearch;
  int studentConfirmation;

  while (studentConfirmation != 1)
  {
    printf("Informe a matricula do estudante:\n");
    if (fgets(buffer, 128, stdin) == NULL)
    {
      printf("Error getting user input");
      return rents;
    }
    printf("%s", buffer);
    sscanf(buffer, "%d", &registrationToSearch);

    studentIndex = studentLinearSearch(students, *studentsCounterGlobal, registrationToSearch);

    if (studentIndex == -1)
    {
      printf("Estudante nao encontrado\n");
      return rents;
    }
    printf("\nEstudante encontrado:\nNome: %s\n", students[studentIndex].name);

    printf("\nConfirmar?\n1.Sim\n2.Nao\n");
    if (fgets(buffer, 128, stdin) == NULL)
    {
      printf("Error getting user input");
      return rents;
    }
    sscanf(buffer, "%d", &studentConfirmation);
  }

  int bookIdToSearch;
  int bookConfirmation;
  while (bookConfirmation != 1)
  {
    printf("Informe o id do livro:\n");
    if (fgets(buffer, 128, stdin) == NULL)
    {
      printf("Error getting user input");
      return rents;
    }
    sscanf(buffer, "%d", &bookIdToSearch);

    bookIndex = bookLinearSearch(books, *booksCounterGlobal, bookIdToSearch);

    if (bookIndex == -1)
    {
      printf("Livro nao encontrado\n");
      return rents;
    }

    const Book foundBook = books[bookIndex];
    /*  if (foundBook.avaliableCopies == 0)
     {
       printf("Este livro nao esta disponivel");
       return;
     } */
    printf("\nLivro encontrado:\nNome: %s\nAutor: %s\nCopias disponiveis: %d\n", books[bookIndex].title, books[bookIndex].author, books[bookIndex].avaliableCopies);

    printf("\nConfirmar?\n1.Sim\n2.Nao\n");
    if (fgets(buffer, 128, stdin) == NULL)
    {
      printf("Error getting user input");
      return rents;
    }
    sscanf(buffer, "%d", &bookConfirmation);
  }
  long long currentTime = getCurrentRawTime();
  long long timeAfterSevenDays = addSevenDaysToRawTime(&currentTime);
  BookRent rent = {
      .id = *rentsCounterGlobal + 1,
      .isActive = 1,
      .rentDate = currentTime,
      .devolutionDate = timeAfterSevenDays,
      .bookId = books[bookIndex].id,
      .userRegistration = students[studentIndex].registration};

  BookRent *newRents = addRent(rent, rents, rentsCounterGlobal);
  return newRents;
}

long long getCurrentRawTime()
{

  time_t rawtime;
  // struct tm *info;

  // Get current calendar time
  time(&rawtime);
  /*  info = localtime(&rawtime); // Convert to local time struct tm

   printf("Current local date and time: %s", asctime(info));

   // Using strftime for custom formatting
   char buffer[80];
   strftime(buffer, sizeof(buffer), "Today is %A, %B %d, %Y. The time is %H:%M:%S.", info);
   printf("%s\n", buffer); */
  return (long long)rawtime;
}

long long addSevenDaysToRawTime(long long *rawtime)
{
  time_t time;
  struct tm *info = localtime(rawtime);
  info->tm_mday += 7;
  time = mktime(info);
  return (long long)time;
}

int studentLinearSearch(Student *arr, int n, int key)
{
  for (int i = 0; i < n; i++)
  {
    if (arr[i].registration == key)
    {
      return i;
    }
  }
  return -1;
}

int bookLinearSearch(Book *arr, int n, int key)
{
  for (int i = 0; i < n; i++)
  {
    if (arr[i].id == key)
    {
      return i;
    }
  }
  return -1;
}