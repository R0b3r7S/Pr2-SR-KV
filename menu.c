#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "file_types.h"
#include "student.h"
#include "file.h"

void displayMenu(const char* const fileName) {
	int choice;

	do {
		//system("cls");
		printf("\nBinary File Operations Menu:\n");
		printf("%d. Exit\n", EXIT);
		printf("%d. Insert Student\n", INSERT_STUDENT);
		printf("%d. Update Student\n", UPDATE_STUDENT);
		printf("%d. Delete Student\n", DELETE_STUDENT);
		printf("%d. Find Student\n", FIND_STUDENT);
		printf("%d. Read Students\n", READ_STUDENTS);
		printf("%d. Delete Binary File\n", DELETE_BINARY_FILE);
		printf("%d. Rename Binary File\n", RENAME_BINARY_FILE);
		printf("%d. Sort Students Menu\n", SORT_STUDENTS_MENU);
		printf("%d. Search Students Menu\n", SEARCH_STUDENTS_MENU);

		printf("Enter your choice: ");
		getchar();
		scanf("%d", &choice);

		switch (choice) {
		case INSERT_STUDENT:
			insertStudent(fileName);
			break;
		case UPDATE_STUDENT:
			updateStudent(fileName);
			break;
		case DELETE_STUDENT:
			deleteStudent(fileName);
			break;
		case FIND_STUDENT:
			findStudent(fileName);
			break;
		case READ_STUDENTS:
			readStudents(fileName);
			break;
		case DELETE_BINARY_FILE:
			deleteBinaryFile(fileName);
			break;
		case RENAME_BINARY_FILE:
			renameBinaryFile(fileName);
			break;
		case SORT_STUDENTS_MENU:
			sortStudentsMenu(fileName);
			break;
		case SEARCH_STUDENTS_MENU:
			searchStudentsMenu(fileName);
			break;
		case EXIT:
			printf("Exiting program.\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
		}

	} while (choice != EXIT);
}