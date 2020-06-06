#include "student.h"

struct Student_ {
	char* name;
	int age, ID;
	char* faculty;
};

/*
 Function: StudentCreate
 Abstract: creats a new student object with the givven parameters
 Parameters: n_name - string that is the name of the new student
			 n_age - integer that is the age of the new student
			 n_ID - integer that is the ID of the new student (unique)
			 n_faculty - string that is the name of the faculty of the new student
 Return: pointer to the new student object with the new information
 */
PStudent StudentCreate(char* n_name, int n_age, int n_ID, char* n_faculty) {
	if (!n_name)
		n_name = "";
	if (!n_faculty)
		n_faculty = "";
	PStudent new_student;
	new_student = (PStudent)malloc(sizeof(Student));
	if (!new_student) {
		return NULL;
	}
	new_student->name = (char*)malloc(strlen(n_name) + 1);
	if (!new_student->name) {
		free(new_student);
		return NULL;
	}
	new_student->faculty = (char*)malloc(strlen(n_faculty) + 1);
	if (!new_student->faculty) {
		free(new_student->name);
		free(new_student);
		return NULL;
	}
	strcpy(new_student->name, n_name);
	strcpy(new_student->faculty, n_faculty);
	new_student->age = n_age;
	new_student->ID = n_ID;

	return new_student;
}

/*
 Function: printStudent
 Abstract: prints the student information in the requested format
 Parameters: pStudent - a pointer to a student object to print
 Return: N/A
 */
void printStudent(void* pStudent) {
	PStudent student = (PStudent)pStudent;
	if(student != NULL)
		printf("Name: %s, Age: %d, ID: %d, Faculty: %s\n", student->name,
			student->age, student->ID, student->faculty);
}

/*
 Function: cloneStudent
 Abstract: creates a deep copy of a student object student
 Parameters: pStudent - a pointer to a student object to copy
 Return: a void pointer to the copied student that can be casted back to PStudent form
 */
void* cloneStudent(void* pStudent) {
	PStudent student = (PStudent)pStudent;
	if (!student)
		return NULL;
	return (void*)StudentCreate(student->name, student->age, student->ID, student->faculty);
}

/*
 Function: destroyStudent
 Abstract: deletes the student passed
 Parameters: pStudent - a pointer to a student object to delete
 Return: N/A
 */
void destroyStudent(void* pStudent) {
	PStudent student = (PStudent)pStudent;
	if (!student) {
		free(student->name);
		free(student->faculty);
		free(student);
	}
}

/*
 Function: compareStudents
 Abstract: compares 2 students by their ID
 Parameters: student2 - a pointer to the first student to compare
			 student1 - a pointer to the second student to compare
 Return: TRUE if the ID's are the same. FALSE otherwise.
 */
BOOL compareStudents(void* student1, void* student2) {
	PStudent pStudent1 = (PStudent)student1;
	PStudent pStudent2 = (PStudent)student2;
	if (!pStudent1 || !pStudent2)
		return FALSE;
	return (pStudent1->ID == pStudent2->ID) ? TRUE : FALSE;
}
