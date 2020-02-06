#include "datap.h"
#include <stdio.h>
#include "Examples.h"


void runLettersExample(){
	
	fprintf(stdout, "Letters example\n");
	fprintf(stdout, "================\n");
	char* letters = numAsLetters(428);
	fprintf(stdout, "Converts binary number (428) to 0-terminated characters: %s\n", letters);
	fprintf(stdout, "================\n");
	_int64 length = letterLength((char*)"abcd123");
	fprintf(stdout, "Returns length of characters abcd123: %d\n", length);
	fprintf(stdout, "================\n");
	char* firstLetters = (char*)"firstLetters12";
	char* lastLetters = (char*)"lastLetters88";
	char* appended = appendLetters(firstLetters, lastLetters);
	fprintf(stdout, "Appends Letters %s after %s: %s\n", lastLetters,firstLetters,appended);
	fprintf(stdout, "================\n");

}