#ifndef UTILS_HEADER // Check if UTILS_HEADER is NOT defined
#define UTILS_HEADER // Define UTILS_HEADER if it wasn't already

#include "structs.h"

int studentLinearSearch(Student *arr, int n, int key);
int bookLinearSearch(Book *arr, int n, int key);
int rentLinearSearch(BookRent *arr, int n, int key);
void incrementBookAvaliableCopies(int bookId, int amount);
void waitUntilUserInput();
#endif