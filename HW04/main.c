#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pe04.h"

/* 
	Complete the main function and meet the following specifications of argc and argv.
	1. argc: If argc is less than 3, you should return EXIT_FAILURE and print "Insufficient arguments\n".
	2. argv[1]: name of the input file.
	3. argv[2]: should be either "-a", or "-s".
	  	When argv[2] is "-a", you should print all the students in database using PrintDatabase() function and return EXIT_SUCCESS.
	  	When argv[2] is "-s', you should  enter the name of the student in argv[3] and print information of that student, if there is no input in argv[3] you should print "Wrong arguments\n" and return EXIT_FAILURE.
	  	If argv[2] is neither "-a" nor "-s", you should print "Wrong arguments\n" and return EXIT_FAILURE
	4. argv[3]: We only need input in argv[3] when argv[2] is equal to "-s". argv[3] is the name of the student you are looking for. If there is no such student, you should print "No this student\n". Otherwise, use PrintStudent() function to print the information of the student.
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
		return EXIT_FAILURE;
	}
}

