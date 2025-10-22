#include <stdbool.h>
Student *getStudents(int *globalCounter);
Book *getBooks(int *globalCounter);
BookRent *getRents(int *globalCounter);

bool addStudentToFile(Student student);
bool addBookToFile(Book book);
bool addRentToFile(BookRent rent);

extern const char *BOOK_FORMAT_OUT;
extern const char *BOOK_FORMAT_IN;