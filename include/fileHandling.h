#include "structs.h"
#include <stdbool.h>
Student *getStudents(int *globalCounter);
Book *getBooks(int *globalCounter);

bool addStudentToFile(Student student);
bool addBookToFile(Book book);
