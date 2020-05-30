#ifndef _STUDENT_H_
#define _STUDENT_H_
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student_ Student, *PStudent;

PStudent StudentCreate(char*, int, int, char*);
void printStudent(void*);
void* cloneStudent(void*);
void destroyStudent(void*);
BOOL compareStudents(void*, void*);

#endif
