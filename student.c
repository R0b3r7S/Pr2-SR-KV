#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_types.h"

void insertStudent(const char* const fileName) {
	FILE* file = fopen(fileName, "ab");
	if (file == NULL) {
		perror("Error opening binary file for appending");
		exit(EXIT_FAILURE); //razmisliti o ubacivanju samo return;
	}

	student_t newStudent = { 0 };

	getchar();
	printf("Enter student name: ");
	scanf("%49[^\n]", newStudent.name);

	printf("Enter student ID: ");
	scanf("%d", &newStudent.id);

	printf("Enter student grade: ");
	scanf("%f", &newStudent.grade);

	if (fwrite(&newStudent, sizeof(student_t), 1, file) == 1) {
		printf("Student inserted successfully.\n");
	}
	else {
		fprintf(stderr, "Error inserting student.\n");
	}

	fclose(file);
}

int findStudent(const char* const fileName) {
	FILE* file = fopen(fileName, "rb");
	if (file == NULL) {
		perror("Error opening binary file for searching");
		exit(EXIT_FAILURE); //razmisliti o ubacivanju samo return;
	}

	int targetID;
	printf("Enter the ID of the student to find: ");
	scanf("%d", &targetID);

	student_t foundStudent = { 0 };
	int found = 0;

	while (fread(&foundStudent, sizeof(student_t), 1, file) == 1) {
		if (foundStudent.id == targetID) {
			found = 1;
			printf("Student found:\n");
			printf("Name: %s\n", foundStudent.name);
			printf("ID: %d\n", foundStudent.id);
			printf("Grade: %.2f\n", foundStudent.grade);
			break;
		}
	}

	fclose(file);

	if (!found) {
		printf("Student not found.\n");
		return -1;
	}

	return targetID;
}

void updateStudent(const char* const fileName) {
	FILE* file = fopen(fileName, "rb+");
	if (file == NULL) {
		perror("Error opening binary file for updating");
		exit(EXIT_FAILURE); //razmisliti o ubacivanju samo return;
	}

	int targetID = findStudent(fileName);

	if (targetID == -1) {
		return;
	}

	student_t updatedStudent = { 0 };
	//int found = 0;

	while (fread(&updatedStudent, sizeof(student_t), 1, file) == 1) {
		if (updatedStudent.id == targetID) {
			//found = 1;
			printf("Enter updated information for %s: ", updatedStudent.name);

			getchar();
			printf("Enter student name: ");
			scanf("%49[^\n]", updatedStudent.name);

			printf("Enter student grade: ");
			scanf("%f", &updatedStudent.grade);

			fseek(file, -(signed)sizeof(student_t), SEEK_CUR);
			if (fwrite(&updatedStudent, sizeof(student_t), 1, file) == 1) {
				printf("Student updated successfully.\n");
			}
			break;
		}
	}

	fclose(file);

	//if (!found) {
	//	printf("Student not found.\n");
	//}
}

void deleteStudent(const char* const fileName) {

	int targetID = findStudent(fileName);

	if (targetID == -1) {
		return;
	}

	FILE* file = fopen(fileName, "rb");
	if (file == NULL) {
		perror("Error opening binary file for deletion");
		exit(EXIT_FAILURE); //razmisliti o ubacivanju samo return;
	}

	FILE* tempFile = fopen("temp.bin", "wb");
	if (tempFile == NULL) {
		perror("Error creating temporary file");
		fclose(file);
		exit(EXIT_FAILURE); //razmisliti o ubacivanju samo return;
	}

	student_t currentStudent = { 0 };

	while (fread(&currentStudent, sizeof(student_t), 1, file) == 1) {
		if (currentStudent.id != targetID) {
			fwrite(&currentStudent, sizeof(student_t), 1, tempFile);
		}
	}

	fclose(file);
	fclose(tempFile);

	remove(fileName);
	rename("temp.bin", fileName);

	printf("Student deleted successfully.\n");
}

void readStudents(const char* const fileName) {
	FILE* file = fopen(fileName, "rb");
	if (file == NULL) {
		perror("Error opening binary file for reading");
		exit(EXIT_FAILURE); //razmisliti o ubacivanju samo return;
	}

	student_t currentStudent = { 0 };
	int status = 0;
	int read = 0;

	printf("Students in the binary file:\n");

	while ((status = fread(&currentStudent, sizeof(student_t), 1, file)) == 1) {
		printf("Name: %s, ID: %d, Grade: %.2f\n", currentStudent.name, currentStudent.id, currentStudent.grade);
		read = 1;
	}

	if (status == 0 && read == 0) {
		printf("No students in %s file.\n", fileName);
		return;
	}

	fclose(file);
}

//void readStudents() {
//	FILE* file = fopen("students.bin", "rb");
//	if (file == NULL) {
//		perror("Error opening binary file for reading");
//		exit(EXIT_FAILURE);
//	}
//
//	// Move to the end of the file
//	fseek(file, 0, SEEK_END);
//	// Get the size of the file
//	long fileSize = ftell(file);
//	// Calculate the number of students
//	int numStudents = fileSize / sizeof(student_t);
//	// Move back to the beginning of the file
//	fseek(file, 0, SEEK_SET);
//
//	// Dynamically allocate memory for students
//	student_t* students = (student_t*)malloc(numStudents * sizeof(student_t));
//	if (students == NULL) {
//		fprintf(stderr, "Memory allocation failed\n");
//		fclose(file);
//		exit(EXIT_FAILURE);
//	}
//
//	// Read students from file into the array
//	fread(students, sizeof(student_t), numStudents, file);
//	fclose(file);
//
//	// Print student details
//	printf("Students in the binary file:\n");
//	for (int i = 0; i < numStudents; i++) {
//		printf("Name: %s, ID: %d, Grade: %.2f\n", students[i].name, students[i].id, students[i].grade);
//	}
//
//	// Free the allocated memory
//	free(students);
//}


static void printStudent(const student_t* const students, const int numStudents) {

	int i;

	for (i = 0; i < numStudents; i++)
	{
		printf("Name: %s, ID: %d, Grade: %.2f\n", (students + i)->name, (students + i)->id, (students + i)->grade);
	}
	printf("\n");
}

// Comparison function for sorting by name in ascending order
int compareByNameAsc(const void* a, const void* b) {
	const student_t* studentA = (const student_t*)a;
	const student_t* studentB = (const student_t*)b;
	return strcmp(studentA->name, studentB->name);
}

// Comparison function for sorting by name in descending order
int compareByNameDesc(const void* a, const void* b) {
	const student_t* studentA = (const student_t*)a;
	const student_t* studentB = (const student_t*)b;
	return strcmp(studentB->name, studentA->name);
}

// Comparison function for sorting by grade in ascending order
int compareByGradeAsc(const void* a, const void* b) {
	const student_t* studentA = (const student_t*)a;
	const student_t* studentB = (const student_t*)b;
	if (studentA->grade < studentB->grade) return -1;
	if (studentA->grade > studentB->grade) return 1;
	return 0;
}

// Comparison function for sorting by grade in descending order
int compareByGradeDesc(const void* a, const void* b) {
	const student_t* studentA = (const student_t*)a;
	const student_t* studentB = (const student_t*)b;
	if (studentA->grade > studentB->grade) return -1;
	if (studentA->grade < studentB->grade) return 1;
	return 0;
}

void sortStudentsMenu(const char* const fileName) {
	FILE* file = fopen(fileName, "rb");
	if (file == NULL) {
		perror("Error opening binary file for reading");
		exit(EXIT_FAILURE); //razmisliti o ubacivanju samo return;
	}

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	int numStudents = fileSize / sizeof(student_t);

	if (numStudents == 0) {
		printf("No students in %s file.\n", fileName);
		return;
	}

	fseek(file, 0, SEEK_SET);

	student_t* students = (student_t*)malloc(numStudents * sizeof(student_t));
	if (students == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		fclose(file);
		exit(EXIT_FAILURE); 
	}

	fread(students, sizeof(student_t), numStudents, file);
	fclose(file);

	int choice;
	printf("Choose sorting option:\n");
	printf("%d. By Name Ascending\n", NAME_ASC);
	printf("%d. By Name Descending\n", NAME_DES);
	printf("%d. By Grade Ascending\n", GRADE_ASC);
	printf("%d. By Grade Descending\n", GRADE_DES);
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice) {
	case NAME_ASC:
		qsort(students, numStudents, sizeof(student_t), compareByNameAsc);
		printStudent(students, numStudents);
		break;
	case NAME_DES:
		qsort(students, numStudents, sizeof(student_t), compareByNameDesc);
		printStudent(students, numStudents);
		break;
	case GRADE_ASC:
		qsort(students, numStudents, sizeof(student_t), compareByGradeAsc);
		printStudent(students, numStudents);
		break;
	case GRADE_DES:
		qsort(students, numStudents, sizeof(student_t), compareByGradeDesc);
		printStudent(students, numStudents);
		break;
	default:
		printf("Invalid choice. No sorting performed.\n");
		free(students);
		return;
	}

	// Optionally print the sorted students
	printf("Sorted Students:\n");
	for (int i = 0; i < numStudents; i++) {
		printf("Name: %s, ID: %d, Grade: %.2f\n", students[i].name, students[i].id, students[i].grade);
	}

	free(students);
}

//// Comparison functions for sorting and searching by name
//int compareByName(const void* a, const void* b) {
//	const student_t* studentA = (const student_t*)a;
//	const student_t* studentB = (const student_t*)b;
//	return strcmp(studentA->name, studentB->name);
//}
//
//// Comparison functions for sorting and searching by grade
//int compareByGrade(const void* a, const void* b) {
//	const student_t* studentA = (const student_t*)a;
//	const student_t* studentB = (const student_t*)b;
//	if (studentA->grade < studentB->grade) return -1;
//	if (studentA->grade > studentB->grade) return 1;
//	return 0;
//}

void searchStudentsMenu(const char* const fileName) {
	FILE* file = fopen(fileName, "rb");
	if (file == NULL) {
		perror("Error opening binary file for reading");
		exit(EXIT_FAILURE); //razmisliti o ubacivanju samo return;
	}

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	int numStudents = fileSize / sizeof(student_t);

	if (numStudents == 0) {
		printf("No students in %s file.\n", fileName);
		return;
	}

	fseek(file, 0, SEEK_SET);

	student_t* students = (student_t*)malloc(numStudents * sizeof(student_t));
	if (students == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		fclose(file);
		exit(EXIT_FAILURE);
	}

	fread(students, sizeof(student_t), numStudents, file);
	fclose(file);

	int choice;
	printf("Search for a student by:\n%d. Name\n%d. Grade\nEnter your choice: ", NAME_SRC, GRADE_SRC);
	scanf("%d", &choice);

	student_t key;
	student_t* foundStudent;

	switch (choice) {
	case NAME_SRC:
		printf("Enter name to search: ");
		scanf("%49s", key.name); // Use buffer size minus one to prevent overflow
		qsort(students, numStudents, sizeof(student_t), compareByNameAsc);
		foundStudent = (student_t*)bsearch(&key, students, numStudents, sizeof(student_t), compareByNameAsc);
		break;
	case GRADE_SRC:
		printf("Enter grade to search: ");
		scanf("%f", &key.grade);
		qsort(students, numStudents, sizeof(student_t), compareByGradeAsc);
		foundStudent = (student_t*)bsearch(&key, students, numStudents, sizeof(student_t), compareByGradeAsc);
		break;
	default:
		printf("Invalid choice.\n");
		free(students);
		return;
	}

	if (foundStudent != NULL) {
		printf("Student found: Name: %s, ID: %d, Grade: %.2f\n", foundStudent->name, foundStudent->id, foundStudent->grade);
	}
	else {
		printf("Student not found.\n");
	}

	free(students);
}