#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "fileHandling.h"

Student *addStutend(Student student, Student *students, int *studentsGlobalCounter)
{
  Student *temp = (Student *)realloc(students, (*studentsGlobalCounter + 1) * sizeof(Student));

  if (temp == NULL)
  {
    perror("Failed to resize memory for students array");
  }
  else
  {
    temp[*studentsGlobalCounter] = student;
    students = temp;
    *studentsGlobalCounter += 1;
  }
  if (addStudentToFile(student))
  {
    printf("\nEstudante: \"%s\" adicionado com sucesso\n", student.name);
    return temp;
  }
  return students;
}

Student *handleAddStudent(Student *students, int *studentsGlobalCounter)
{
  char name[100];
  char course[50];
  char phoneNumber[15];
  char buffer[128];
  int confirmation;

  while (confirmation != 1)
  {
    printf("\nDigite os dados do estudante um por um:\n");

    printf("Nome:\n");
    if (fgets(name, 100, stdin) == NULL)
      return students;
    name[strcspn(name, "\n")] = '\0';
    // TODO add verification if user wrote the exact name of the course, create an includes function as an util
    printf("Um curso entre Engenharia, Direito, Psicologia, Fisioterapia, Letras, Enfermagem e Arquitetura\n");
    if (fgets(course, 50, stdin) == NULL)
      return students;
    course[strcspn(course, "\n")] = '\0';

    printf("Numero de telefone:\n");
    if (fgets(phoneNumber, 15, stdin) == NULL)
      return students;
    phoneNumber[strcspn(phoneNumber, "\n")] = '\0';

    printf("\nEsses sao os dados especificados, confirmar?\n Nome: %s\n Curso: %s\n Numero de telefone: %s\n", name, course, phoneNumber);
    printf("1. Sim\n2. Nao\n");
    if (fgets(buffer, 128, stdin) == NULL)
      return students;
    sscanf(buffer, "%d", &confirmation);
  }
  Student student = {
      .registration = *studentsGlobalCounter + 1,
      .registrationDate = 182937612908};

  strncpy(student.name, name, sizeof(name));
  student.name[sizeof(name)] = '\0';

  strncpy(student.course, course, sizeof(student.course));
  student.course[sizeof(course)] = '\0';

  strncpy(student.phoneNumber, phoneNumber, sizeof(student.phoneNumber));
  student.phoneNumber[sizeof(phoneNumber)] = '\0';

  Student *newStudents = addStutend(student, students, studentsGlobalCounter);
  return newStudents;
};