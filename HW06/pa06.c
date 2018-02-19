#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pa06.h"
#define MAX_LEN 80

#ifndef TEST_CONSRUCT
/* 
	Construct SelectedField.
	1. This function returns a pointer to SelectedField object.
	2. Allocate memory for SelectedField object.
	3. Initialize all the fields in this object to "false".
	4. return NULL if you fail to allocate memory for SelectedField object.
*/
SelectedField * ConstructField() {
    SelectedField *sf = malloc(sizeof(SelectedField));
    if (!sf) {
        return NULL;
    } else {
        sf -> id = false;
        sf -> name = false;
        sf -> major = false;
        sf -> year = false;
        sf -> enrollment = false;
        sf -> age = false;
        return sf;
    }
}
#endif

#ifndef TEST_PARSE
/* 
	Parse the query and store the information into ParseResult object.
	1. This function returns a pointer to ParseResult object.
	2. The ParseResult object has four fields.
		1. Pointer to SelectedField object. The SelectedField  object stores the informations of which fields are selected in the query. For example, if field id is selected, you should update that field to "true".
		2. Number of condition. 
		3. Array of pointers to Condition object. 
		4. What logic does this query specify. It should be eigther AND or OR.
	3. In this function, you should parse the qeury and store the information to ParseResult object. Similar to `Connect()` function in HW04, you should allocate memory for the required objects and then update the fields in the objects. 
*/
ParseResult * ParseQuery(int num, char ** query) {
    ParseResult *pr = malloc(sizeof(ParseResult));
    if (!pr) {
        return NULL;
    }
    pr -> field = ConstructField();
    if (!(pr -> field)) {
        return NULL;
    }
    for (int i = 2; i < num; i++) {
        if (!strcmp(query[i], "WHERE")) {
            int count = 1;
            for (int j = i; j < num; j++) {
                if (!strcmp(query[j], "AND") || !strcmp(query[j], "OR")) {
                    count++;
                }
            }
            pr -> conditions = malloc(sizeof(Condition*) * count);
            for (int j = 0; j < count; j++) {
                pr -> conditions[j] = malloc(sizeof(Condition));
                strcpy(pr -> condition)
            }
        } else {
            pr -> field -> id = !strcmp(query[i], "id");
            pr -> field -> name = !strcmp(query[i], "name");
            pr -> field -> major = !strcmp(query[i], "major");
            pr -> field -> year = !strcmp(query[i], "year");
            pr -> field -> enrollment = !strcmp(query[i], "enrollment");
            pr -> field -> age = !strcmp(query[i], "age");
        }
    }
}
#endif


#ifndef TEST_COMPARE
/*
	This is a helper function we provide in this assignment.
	It checks whether a stduent meets the condition.
	You can choose not to use this function.
	Do not modify this function. If you change it, you will get zero.
*/
bool Compare(Student * stu, Condition * condition) {
	if (strcmp(condition -> field, "id") == 0) {
		int id_val = atoi(condition -> val);
		if (strcmp(condition -> optr, "<") == 0) {
			return (stu -> id < id_val);
		} else if (strcmp(condition -> optr, ">") == 0) {
			return (stu -> id > id_val);
		} else if (strcmp(condition -> optr, "=") == 0) {
			return stu -> id == id_val;
		} else if (strcmp(condition -> optr, ">=") == 0) {
			return (stu -> id >= id_val);
		} else if (strcmp(condition -> optr, "<=") == 0) {
			return (stu -> id <= id_val);
		}
	} else if (strcmp(condition -> field, "age") == 0) {
		int age_val = atoi(condition -> val);
		if (strcmp(condition -> optr, "<") == 0) {
			return (stu -> age < age_val);
		} else if (strcmp(condition -> optr, ">") == 0) {
			return (stu -> age > age_val);
		} else if (strcmp(condition -> optr, "=") == 0) {
			return (stu -> age == age_val);
		} else if (strcmp(condition -> optr, ">=") == 0) {
			return (stu -> age >= age_val);
		} else if (strcmp(condition -> optr, "<=") == 0) {
			return (stu -> age <= age_val);
		}
	} else {
		if (strcmp(condition -> field, "name") == 0	) {
			if (strcmp(stu -> name, condition -> val) == 0) {
				return true;	
			}
			return false;	
		} else if (strcmp(condition -> field, "major") == 0 ) {
			if (strcmp(stu -> major, condition -> val) == 0){
				return true;	
			}
			return false;	
		} else if (strcmp(condition -> field, "year") == 0 ) {
			if (strcmp(stu -> year, condition -> val) == 0){
				return true;	
			}
			return false;	
		} else if (strcmp(condition -> field, "enrollment") == 0 ) {
			if (strcmp(stu -> enrollment, condition -> val) == 0){
				return true;	
			}
			return false;	
		}
	} 
	return false;
}
#endif

#ifndef TEST_EXECUTE
/*
	1.This function takes two arguments:
		1. pointer to `StudentDatabase` object.
		2. pointer to `ParseResult` object.	
	2. This function returns a pointer to `ExecuteResult` object.
	3. The `ExecuteResult` object has two fields: First, an array of matched Student's index. Second, length of the array. 
*/
ExecuteResult * ExecuteQuery(StudentDatabase * db, ParseResult * res) {

}
#endif

#ifndef TEST_FREEPARSE
/*
	Free the allocated memory in ParseResult object.
*/
void FreeParseResult(ParseResult * res) {

}
#endif

#ifndef TEST_FREEEXECUTE
/*
	Free the allocated memory in ExecuteResult object.
*/
void FreeExecuteResult(ExecuteResult * res) {

}
#endif

#ifndef TEST_WRITE

/*
	1. Only write selected fields of students who meet specified conditions to output file.
	2. Print error message "Failed to open file\n" to monitor if the fopen fail. You should not have output file generated if fopen fail. 
	3. Follow this format "field:%s ", or "field:%d ". Add "\n" when you finish writing the selected fileds of a student. Please look at the files in `expected` folder to make sure you understand the format. We will use diff to test. Make sure your output format is correct.
	4. You should write the info of each student in the following order if that fields are selected. id -> name -> major -> year -> enrollment -> age.
	5. The order in selected fields does not affect the order you write to the file.  e.g., `SELECT id name WHERE ...` and `SELECT name id WHERE ...` should have the same output file.  
*/
void WriteDb(StudentDatabase * db, SelectedField * info, ExecuteResult * execute_res, char * filename) {

}

#endif
