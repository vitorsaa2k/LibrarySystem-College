#include "structs.h"
Student *handleAddStudent(Student *students, int *globalStudentsCounter);
Book *handleAddBook(Book *books, int *booksGlobalCounter);
BookRent *handleRentBook(Book *books, Student *students, BookRent *rents, int *studentsCounterGlobal, int *booksCounterGlobal, int *rentsCounterGlobal);
/* void handleBookDevolution();
void handleSearchBook();
void handleSearchStudent();
void handleListActiveRents(); */