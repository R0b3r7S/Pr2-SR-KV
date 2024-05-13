#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "file.h"
#include "menu.h"

int main(void) {

    char fileName[30] = { 0 };

    printf("Inpute file name with extension.\n");
    scanf("%29[^\n]", fileName);
    
    createBinaryFile(fileName);
    displayMenu(fileName);

    return 0;
}