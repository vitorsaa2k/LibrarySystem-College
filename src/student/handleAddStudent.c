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
    *studentsGlobalCounter++;
  }
  if (addStudentToFile(student))
  {
    printf("\nEstudante: \"%s\" adicionado com sucesso\n", student.name);
    return 0;
  }
}

void handleAddStudent(Student *students, int *studentsGlobalCounter)
{
  char name[100];
  char course[50];
  char phoneNumber[15];
  int confirmation;

  while (confirmation != 1)
  {
    printf("\nDigite os dados do estudante um por um:\n");

    printf("Nome:\n");
    scanf("%s", name);

    printf("Um curso entre Engenharia, Direito, Psicologia, Fisioterapia, Letras, Enfermagem e Arquitetura\n");
    scanf("%s", course);

    printf("Numero de telefone:\n");
    scanf("%s", phoneNumber);

    printf("\nEsses sao os dados especificados, confirmar?\n Nome: %s\n Curso: %s\n Numero de telefone: %s\n", name, course, phoneNumber);
    printf("1. Sim\n2. Nao\n");
    scanf("%d", &confirmation);
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