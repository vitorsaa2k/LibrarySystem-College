#include <stdio.h>
#include <stdbool.h>
#include "structs.h"
#include <string.h>
#include <stdlib.h>

const char *BOOK_FORMAT_OUT = "%d,%s,%s,%s,%d,%d,%d,%d\n";
const char *BOOK_FORMAT_IN = "%d,%[^,],%[^,],%[^,],%d,%d,%d\n";

Book *getBooks(int *globalCounter)
{
  char buffer[512];
  Book *books = NULL;
  int count = 0;
  FILE *booksFile;
  booksFile = fopen("livros.txt", "r");
  if (booksFile == NULL)
  {
    printf("Failed to open file");
    return NULL;
  }

  Book book;
  while (fgets(buffer, sizeof(buffer), booksFile) != NULL)
  {
    sscanf(buffer, BOOK_FORMAT_IN, &book.id, book.title, book.author, book.publisher, &book.releaseYear, &book.avaliableCopies, &book.isAvaliable, &book.timesRent);
    // printf(BOOK_FORMAT_OUT, student.registration, student.name, student.course, student.phoneNumber, student.registrationDate);

    Book *temp = (Book *)realloc(books, (count + 1) * sizeof(Book));

    if (temp == NULL)
    {
      perror("Failed to resize memory for books array");
    }
    else
    {
      books = temp;
      books[count] = book;
      count++;
    }
  };
  fclose(booksFile);
  *globalCounter = count;
  return books;
}

bool addBookToFile(Book book)
{
  FILE *booksFile;
  booksFile = fopen("livros.txt", "a");
  if (booksFile == NULL)
  {
    printf("Error opening the file");
    return false;
  }

  fprintf(booksFile, BOOK_FORMAT_OUT, book.id, book.title, book.author, book.publisher, book.releaseYear, book.avaliableCopies, book.isAvaliable, book.timesRent);
  return true;
}