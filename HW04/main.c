#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pe04.h"

/* 
	1. `argc`: 
		1. If `argc` is less than 3, you should return `EXIT_FAILURE` and print "Insufficient arguments\n".
		2. When argc is 3, `argv[2]` should be "-a" and you should print all the students in database using `PrintDatabase()` function and return `EXIT_SUCCESS`. Otherwise, you should print "Wrong arguments\n" to screen and return `EXIT_FAILURE`.
		3. When argc is 4, `argv[2]` should be "-s" and you should  enter the name of the student in `argv[3]` and print information of that student and return `EXIT_SUCCESS`. If there is no such student, you should print "No this student\n" to screen and return `EXIT_SUCCESS`. Otherwise, you should print "Wrong arguments\n" to screen and return `EXIT_FAILURE`.
		4. When argc is larger than 4, you should print "Too many arguments\n" to screen and return `EXIT_FAILURE`.
	2. `argv[1]`: name of the input file (i.e., database.txt).
*/
int main(int argc, char ** argv) {
	if (argc < 3) {
		printf("Insufficient arguments\n");
		return EXIT_FAILURE;
	}
	StudentDatabase *db = Connect(argv[1]);
	if (!db) {
		printf("Load database failed\n");
		Close(db);
		return EXIT_FAILURE;
	}
	if (!strcmp(argv[2], "-a")) {
		PrintDatabase(db);
		Close(db);
		return EXIT_SUCCESS;
	} else if (!strcmp(argv[2], "-s")) {
		if (argc == 3) {
			printf("Wrong arguments\n");
            Close(db);
			return EXIT_FAILURE;
		}
		Student *s = SearchByName(db, argv[3]);
		if (s) {
			PrintStudent(s);
			Close(db);
		} else {
			printf("No this student\n");
			Close(db);
		}
		return EXIT_SUCCESS;
	} else {	
		printf("Wrong arguments\n");
        Close(db);
		return EXIT_FAILURE;
	}
}

