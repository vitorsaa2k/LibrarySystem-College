
typedef struct Book
{
  int id;
  int releaseYear;
  int avaliableCopies;
  int timesRent;
  int isAvaliable;
  char title[100];
  char author[80];
  char publisher[60];
} Book;

typedef struct Student
{
  int registration;
  char name[100];
  char course[50];
  char phoneNumber[15];
  // Decided to store the date in rawtime so i can present it the way i need for the user. thats why it is long long type.
  long long registrationDate;
} Student;

typedef struct RentInfo
{
  int id;
  int userRegistration;
  int bookId;
  // already explained why dates are being represented as long long.
  long long rentDate;
  // should be 7 days after the rentDate
  long long devolutionDate;
  // if 0, means the student does not have the book, either because it was lost or given back.
  int isActive;
} RentInfo;