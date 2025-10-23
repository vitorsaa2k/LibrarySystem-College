#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

const char *RENT_FORMAT_OUT = "%d,%d,%d,%lld,%lld,%d\n";
const char *RENT_FORMAT_IN = "%d,%d,%d,%lld,%lld,%d\n";

BookRent *getRents(int *globalCounter)
{
  char buffer[512];
  BookRent *rents = malloc(sizeof(BookRent));
  int count = 0;
  FILE *rentsFile;
  rentsFile = fopen("emprestimos.txt", "r");
  if (rentsFile == NULL)
  {
    printf("Failed to open file");
    return NULL;
  }

  BookRent rent;
  while (fgets(buffer, sizeof(buffer), rentsFile) != NULL)
  {
    sscanf(buffer, RENT_FORMAT_IN, &rent.id, &rent.userRegistration, &rent.bookId, &rent.rentDate, &rent.devolutionDate, &rent.isActive);
    // printf(BOOK_FORMAT_OUT, student.registration, student.name, student.course, student.phoneNumber, student.registrationDate);

    BookRent *temp = (BookRent *)realloc(rents, (count + 1) * sizeof(BookRent));

    if (temp == NULL)
    {
      perror("Failed to resize memory for books array");
    }
    else
    {
      rents = temp;
      rents[count] = rent;
      count++;
    }
  };
  fclose(rentsFile);
  *globalCounter = count;
  return rents;
}

bool addRentToFile(BookRent rent)
{
  FILE *rentsFile;
  rentsFile = fopen("emprestimos.txt", "a");
  if (rentsFile == NULL)
  {
    printf("Error opening the file");
    return false;
  }

  fprintf(rentsFile, RENT_FORMAT_OUT, rent.id, rent.userRegistration, rent.bookId, rent.rentDate, rent.devolutionDate, rent.isActive);
  fclose(rentsFile);
  return true;
}

void parseRent(BookRent *rent, char *rentToParse)
{
  sscanf(rentToParse, RENT_FORMAT_IN, &rent->id, &rent->userRegistration, &rent->bookId, &rent->rentDate, &rent->devolutionDate, &rent->isActive);
}

void printRentToFile(BookRent rent, FILE *file)
{
  fprintf(file, RENT_FORMAT_OUT, rent.id, rent.userRegistration, rent.bookId, rent.rentDate, rent.devolutionDate, rent.isActive);
}