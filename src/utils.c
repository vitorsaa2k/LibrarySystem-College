#include "structs.h"

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