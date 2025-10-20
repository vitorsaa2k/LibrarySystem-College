#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

const char *STUDENT_FORMAT_OUT = "%d,%s,%s,%s,%lld\n";
const char *STUDENT_FORMAT_IN = "%d,%[^,],%[^,],%[^,],%lld\n";

Student *getStudents(int *globalCounter)
{
  char buffer[512];
  Student *students = NULL;
  int count = 0;
  FILE *usersFile;
  usersFile = fopen("usuarios.txt", "r");

  if (usersFile == NULL)
  {
    printf("Failed to open file");
  }

  Student student;
  while (fgets(buffer, sizeof(buffer), usersFile) != NULL)
  {
    sscanf(buffer, STUDENT_FORMAT_IN, &student.registration, student.name, student.course, student.phoneNumber, &student.registrationDate);
    // printf(STUDENT_FORMAT_OUT, student.registration, student.name, student.course, student.phoneNumber, student.registrationDate);

    Student *temp = (Student *)realloc(students, (count + 1) * sizeof(Student));

    if (temp == NULL)
    {
      perror("Failed to resize memory for students array");
    }
    else
    {
      students = temp;
      students[count] = student;
      count++;
    }
  };
  fclose(usersFile);
  *globalCounter = count;
  return students;
}

bool addStudentToFile(Student student)
{
  FILE *usersFile;
  usersFile = fopen("usuarios.txt", "a");
  if (usersFile == NULL)
  {
    printf("Error opening the file");
    return false;
  }

  fprintf(usersFile, STUDENT_FORMAT_OUT, student.registration, student.name, student.course, student.phoneNumber, student.registrationDate);
  fclose(usersFile);
  return true;
}