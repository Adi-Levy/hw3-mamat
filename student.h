#ifndef _STUDENT_H_
#define _STUDENT_H_
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student_ Student, *PStudent;

PStudent StudentCreate(char*, int, int, char*);
void printStudent(PStudent);
PStudent cloneStudent(PStudent);
void destroyStudent(PStudent);
BOOL compareStudents(PStudent, PStudent);

#endif
