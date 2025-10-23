#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

const char *BOOK_FORMAT_OUT = "%d,%s,%s,%s,%d,%d,%d,%d\n";
const char *BOOK_FORMAT_IN = "%d,%[^,],%[^,],%[^,],%d,%d,%d,%d\n";

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
  fclose(booksFile);
  return true;
}

void parseBook(Book *book, char *bookToParse)
{
  sscanf(bookToParse, BOOK_FORMAT_IN, &book->id, book->title, book->author, book->publisher, &book->releaseYear, &book->avaliableCopies, &book->isAvaliable, &book->timesRent);
}

void printBookToFile(Book book, FILE *file)
{
  fprintf(file, BOOK_FORMAT_OUT, book.id, book.title, book.author, book.publisher, book.releaseYear, book.avaliableCopies, book.isAvaliable, book.timesRent);
}

void incrementBookAvaliableCopies(int bookId, int amount)
{
  FILE *originalFile = fopen("livros.txt", "r");
  FILE *tempFile = fopen("temp.txt", "w");

  if (originalFile == NULL || tempFile == NULL)
  {
    perror("Error opening the files");
  }
  char buffer[512];
  Book currentBook;
  int found = 0;

  while (fgets(buffer, sizeof(buffer), originalFile) != NULL)
  {
    parseBook(&currentBook, buffer);
    if (currentBook.id == bookId)
    {
      currentBook.avaliableCopies += amount;
      printBookToFile(currentBook, tempFile);
      found = 1;
    }
    else
    {
      printBookToFile(currentBook, tempFile);
    }
  }

  fclose(originalFile);
  fclose(tempFile);

  if (!found)
  {
    printf("Book not found");
  }

  if (remove("livros.txt") == 0)
  {
    if (rename("temp.txt", "livros.txt") == 0)
    {
      printf("Changed the avaliable copies successfully");
    }
    else
    {
      perror("Error renaming temp.txt to livros.txt");
    }
  }
  else
  {
    perror("Error removing livros.txt");
  }
}