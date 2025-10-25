#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

int comp(const void *elem1, const void *elem2)
{
  Book f = *((Book *)elem1);
  Book s = *((Book *)elem2);
  if (f.timesRent > s.timesRent)
    return -1;
  if (f.timesRent < s.timesRent)
    return 1;
  return 0;
}

void handleListMostRentedBooks(Book *books, int *globalBooksCounter)
{
  Book *mostRentedBooks;
  Book *booksToSort = NULL;
  int count;
  for (int i = 0; i < *globalBooksCounter; i++)
  {
    Book currentBook = books[i];
    if (currentBook.timesRent > 0)
    {
      Book *temp = realloc(booksToSort, (count + 1) * sizeof(Book));
      temp[count] = currentBook;
      booksToSort = temp;
      count++;
    }
  }

  qsort(booksToSort, count, sizeof(Book), comp);
  printf("\nLivros mais emprestados:\n\n");
  int numberOfBooksToPrint = count < 10 ? count : 10;
  for (int i = 0; i < numberOfBooksToPrint; i++)
  {
    printf("%d. Titulo: %s\n"
           "Numero de vezes emprestado: %d\n",
           i + 1, booksToSort[i].title, booksToSort[i].timesRent);
  }
  // TODO add an util function for pausing the printing.
  printf("Pressione enter para continuar...");
  char tempBuffer[32];
  if (fgets(tempBuffer, sizeof(tempBuffer), stdin) == NULL)
  {
    printf("failed to get user input");
  }
}