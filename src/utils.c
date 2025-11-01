#include "structs.h"
#include <stdio.h>

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

int rentLinearSearch(BookRent *arr, int n, int key)
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

void waitUntilUserInput()
{
  printf("Pressione enter para continuar...");
  char tempBuffer[32];
  if (fgets(tempBuffer, sizeof(tempBuffer), stdin) == NULL)
  {
    printf("failed to get user input");
  }
}