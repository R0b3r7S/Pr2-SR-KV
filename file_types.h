#ifndef FILE_TYPES_H
#define FILE_TYPES_H

typedef struct {
    char name[50];
    int id;
    float grade;
}student_t;

typedef enum {
    EXIT,
    INSERT_STUDENT,
    UPDATE_STUDENT,
    DELETE_STUDENT,
    FIND_STUDENT,
    READ_STUDENTS,
    DELETE_BINARY_FILE,
    RENAME_BINARY_FILE,
    SORT_STUDENTS_MENU,
    SEARCH_STUDENTS_MENU
} menuOption_t;

typedef enum {
    NAME_ASC = 1,
    NAME_DES,
    GRADE_ASC,
    GRADE_DES
}sortMenu_t;

typedef enum {
    NAME_SRC = 1,
    GRADE_SRC
}searchMenu_t;

#endif //FILE_TYPES 

