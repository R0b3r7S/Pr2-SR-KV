#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createBinaryFile(const char* const fileName) {
	FILE* file = fopen(fileName, "rb");
	if (file == NULL) {
		perror("Error no such binary file");

		file = fopen(fileName, "wb");
		if (file == NULL) {
			perror("Error creating binary file");
			exit(EXIT_FAILURE);
		}

		printf("Binary file created successfully.\n");
	}
	else {
		printf("Binary file exists.\n");
	}

	fclose(file);	
}

void deleteBinaryFile(const char* const fileName) {
	char confirmation[4]; // Buffer to store user confirmation, extra space for null character

	printf("Are you sure you want to delete the binary file? (Yes/No): ");
	scanf("%3s", confirmation); // Read up to two characters to prevent buffer overflow

	// Convert the input to uppercase to handle 'yes' or 'no' in any case
	if (strcmp(_strupr(confirmation), "YES") == 0) {													//riješi alternativu strupr()
		if (remove(fileName) == 0) {
			printf("Binary file deleted successfully.\n");
		}
		else {
			perror("Error deleting binary file");
		}
	}
	else {
		printf("File deletion cancelled.\n");
	}
}


void renameBinaryFile(const char* const fileName) {
	char newFileName[100]; // Buffer for the new file name
	char confirmation[4]; // Buffer to store user confirmation, including space for null character

	printf("Enter the new name for the binary file (include .bin extension): ");
	scanf("%99s", newFileName); // Read up to 99 characters to prevent buffer overflow

	printf("Are you sure you want to rename the binary file to %s? (Yes/No): ", newFileName);
	scanf("%3s", confirmation); // Read up to three characters to prevent buffer overflow

	// Convert the input to uppercase to handle 'yes' or 'no' in any case
	if (strcmp(_strupr(confirmation), "YES") == 0) {													//riješi alternativu strupr()
		if (rename(fileName, newFileName) == 0) {
			printf("Binary file renamed successfully to %s.\n", newFileName);
		}
		else {
			perror("Error renaming binary file");
		}
	}
	else {
		printf("File renaming cancelled.\n");
	}
}
