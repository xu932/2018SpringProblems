#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TEST_STRUCT
#include "pe04.h"
#else
#include "pe04_ans.h"
#endif

#ifndef TEST_CONNECT
/*  
	Complete this function. 
	In this function, you should:
	1. Allocate appripriate memory for database using malloc.
	2. Read the content of file and store it to the StudentDatabase object.
		To read the file, you may want to use the following functions:
			fopen(), fclose(), fgetc(), fscanf(), feof().
		You can use fseek(fptr, 0, SEEK_SET) to go to the beginning of a file. 
	3. You should return a pointer to StudentDatabase object.
*/
StudentDatabase * Connect(char * filename) {
	FILE * fpt = fopen(filename, "r");
	if (!fpt) {
		fclose(fpt);
		return NULL;
	}
	StudentDatabase * db = malloc(sizeof(StudentDatabase));
	if (!db) {
		free(db);
		return NULL;
	}
	char read = fgetc(fpt);
	int count = 0;
	while (read != EOF) {
		if (read == '\n') {
			count++;
		}
		read = fgetc(fpt);
	}
	fseek(fpt, 0, SEEK_SET);
	db -> students = malloc(sizeof(Student*) * count);
	if (!(db -> students)) {
		free(db -> students);
		free(db);
	}
	db -> number = count;
	for (int i = 0; i < count; i++) {
		db -> students[i] = malloc(sizeof(Student));
		if (!(db -> students[i])) {
			for (int j = 0; j <= i; j++) {
				free(db -> students[j]);
			}
			free(db -> students);
			free(db);
			fclose(fpt);
			return NULL;
		}

		if (fscanf(fpt, "%d,%[^,],%[^,],%[^,],%[^,],%d", &(db -> students[i] -> id), db -> students[i] -> name, db -> students[i] -> major, db -> students[i] -> year, db -> students[i] -> enroll, &(db -> students[i] -> age)) != 6) {
			printf("Reading student information error\n");
			for (int j = 0; j <= i; j++) {
				free(db -> students[j]);
			}
			free(db -> students);
			free(db);
			fclose(fpt);
			return NULL;
		}
	}
	return db;
}
#endif

#ifndef TEST_CLOSE
/* 
	You have to complete this function
	Free the memory you allocated in Connect() using free()
	studb is a pointer to the database. 
*/
void Close(StudentDatabase * studb) {
	if (studb) {
		if (studb -> students) {
			for (int i = 0; i < studb -> number; i++) {
				if (studb -> students[i]) {
					free(studb -> students[i]);
				}
			}
			free(studb -> students);
		}
		free(studb);
	}
}
#endif

#ifndef TEST_SEARCH
/* 
	You have to complete this function.
	1. studb is a pointer to StudentDatbase object.
	2. name is the name of the student you are looking for.
	3. If the "name" is in the database, you should return a pointer 
	to the Student object of that student. Otherwise, you should return NULL. 
 */
Student * SearchByName(StudentDatabase * studb, char * name) {
	Student *s;
	if (!studb || !(studb -> students)) {
		return NULL;
	}
	for (int i = 0; i < studb -> number; i++) {
		if (studb -> students[i] && !strcmp(studb -> students[i] -> name, name)) {
			s = studb -> students[i];
			return s;
		}
	}	
	return NULL;
}
#endif

/* This function prints info of a student. */
void PrintStudent(Student * stu) {
	printf("ID:%d, Name:%s, Major:%s, Enrollment:%s, Year:%s, Age:%d\n",
		stu -> id, stu -> name, stu -> major, stu -> enroll, stu -> year, stu -> age);
}

/* This function prints all students' info in database. */
void PrintDatabase(StudentDatabase * studb) {
	int stu_num = studb -> number;
	for (int idx = 0; idx < stu_num; idx ++) {
		Student * stu = studb -> students[idx];
		PrintStudent(stu);
	}
}
