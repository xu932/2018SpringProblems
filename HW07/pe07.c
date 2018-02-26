#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pe07.h"




#ifndef INT
bool IsInteger(char* str, int index)
{
	if (str[index] == '\0') {
		return true;
	} else { 
		if (isdigit(str[index])) {
			return IsInteger(str, index + 1);
		} else {
			return false;
		}
	}
}
#endif

#ifndef DOUBLE
bool IsDouble(char* str, int index, bool dot)
{
	if (index == 0 && str[index] == '.') {
		return false;
	} else if (str[index] == '\0') {
		return true;
	} else {
		if (str[index] == '.' && !dot) {
			return IsDouble(str, index + 1, true);
		} else if (isdigit(str[index])) {
			return IsDouble(str, index + 1, dot);
		} else {
			return false;
		}
	}
}
#endif

#ifndef VALIDID
bool IsValidIdentifier(char* str, int index)
{
	if (str[index] == '\0') {
		return true;
	} else if (index == 0 && !(isalpha(str[index]) || str[index] == '_')) {
		return false;
	} else {
		if (isalpha(str[index]) || isdigit(str[index]) || str[index] == '_') {
			return IsValidIdentifier(str, index + 1);
		} else {
			return false;
		}
	}
}
#endif
