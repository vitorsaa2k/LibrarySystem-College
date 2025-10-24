#include "structs.h"
Student *handleAddStudent(Student *students, int *globalStudentsCounter);
Book *handleAddBook(Book *books, int *booksGlobalCounter);
BookRent *handleRentBook(Book *books, Student *students, BookRent *rents, int *studentsCounterGlobal, int *booksCounterGlobal, int *rentsCounterGlobal);
void handleBookDevolution(Book *books, int *booksGlobalCounter, BookRent *rents, int *rentsGlobalCounter);
void handleSearchBook(Book *books, int *globalBooksCounter);
void handleSearchStudent(Student *students, int *globalStudentsCounter);
// void handleListActiveRents()