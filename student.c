#include "student.h"

struct Student_ {
	char* name;
	int age, ID;
	char* faculty;
};

PStudent StudentCreate(char* n_name, int n_age, int n_ID, char* n_faculty) {
	PStudent new_student;
	new_student = (PStudent)malloc(sizeof(Student));
	if (!new_student) {
		return NULL;
	}
	new_student->name = (char*)malloc(strlen(n_name) + 1);
	new_student->faculty = (char*)malloc(strlen(n_faculty) + 1);
	if (!new_student->name || !new_student->faculty) {
		free(new_student);
		return NULL;
	}
	strcpy(new_student->name, n_name);
	strcat(new_student->name, "\0");
	strcpy(new_student->faculty, n_faculty);
	strcat(new_student->faculty, "\0");
	new_student->age = n_age;
	new_student->ID = n_ID;

	return new_student;
}

void printStudent(PStudent pStudent) {
	printf("Name: %s, Age: %d, ID: %d, Faculty: %s\n", pStudent->name,
		pStudent->age, pStudent->ID, pStudent->faculty);
}

PStudent cloneStudent(PStudent pStudent) {
	return StudentCreate(pStudent->name, pStudent->age, pStudent->ID, pStudent->faculty);
}

void destroyStudent(PStudent pStudent) {
	free(pStudent->name);
	free(pStudent->faculty);
	free(pStudent);
}

BOOL compareStudents(PStudent student1, PStudent student2) {
	if (student1->ID == student2->ID)
		return TRUE;
	else
		return FALSE;
}
