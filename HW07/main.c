#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "pe07.h"
#define MAX_LENGTH 100 //The maximum length of string


int main(int argc, char *argv[]) 
{
	if (argc < 2) {
		return EXIT_SUCCESS;
	}
	if (argc == 3) {
		if (!strcmp(argv[2], "-I")) {
			FILE *fpt = fopen(argv[1], "r");
			char str[MAX_LENGTH];
			do {
				fscanf(fpt, "%s", str);
				if (IsInteger(str, 0)) {
					printf("Integer\n");
				} else {
					printf("Not integer\n");
				}
			} while (!feof(fpt));
		} else if (!strcmp(argv[2], "-D")) {

		} else if (!strcmp(argv[2], "-VID")) {
			
		}
	}

	return EXIT_SUCCESS;
}
