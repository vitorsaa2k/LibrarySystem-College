#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "fileHandling.h"
#include "utils.h"

int addStutend(Student student, Student *students, int *studentsGlobalCounter)
{
  Student *temp = (Student *)realloc(students, (*studentsGlobalCounter + 1) * sizeof(Student));

  if (temp == NULL)
  {
    perror("Failed to resize memory for students array");
  }
  else
  {
    students = temp;
    students[*studentsGlobalCounter] = student;
    *studentsGlobalCounter += 1;
  }
  if (addStudentToFile(student))
  {
    printf("\nEstudante: \"%s\" adicionado com sucesso\n", student.name);
    return 0;
  }
}

int handleAddStudent(Student *students, int *studentsGlobalCounter)
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
      return 1;
    name[strcspn(name, "\n")] = '\0';
    // TODO add verification if user wrote the exact name of the course, create an includes function as an util
    printf("Um curso entre Engenharia, Direito, Psicologia, Fisioterapia, Letras, Enfermagem e Arquitetura\n");
    if (fgets(course, 50, stdin) == NULL)
      return 1;
    course[strcspn(course, "\n")] = '\0';

    printf("Numero de telefone:\n");
    if (fgets(phoneNumber, 15, stdin) == NULL)
      return 1;
    phoneNumber[strcspn(phoneNumber, "\n")] = '\0';

    printf("\nEsses sao os dados especificados, confirmar?\n Nome: %s\n Curso: %s\n Numero de telefone: %s\n", name, course, phoneNumber);
    printf("1. Sim\n2. Nao\n");
    if (fgets(buffer, 128, stdin) == NULL)
      return 1;
    sscanf(buffer, "%d", &confirmation);
  }
  Student student = {
      .registration = *studentsGlobalCounter + 1,
      .registrationDate = getCurrentRawTime()};

  strncpy(student.name, name, sizeof(name));
  student.name[sizeof(name)] = '\0';

  strncpy(student.course, course, sizeof(student.course));
  student.course[sizeof(course)] = '\0';

  strncpy(student.phoneNumber, phoneNumber, sizeof(student.phoneNumber));
  student.phoneNumber[sizeof(phoneNumber)] = '\0';

  addStutend(student, students, studentsGlobalCounter);
};