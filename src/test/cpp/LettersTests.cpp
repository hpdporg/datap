#include "AsmIncludes.h"
#include "LettersTests.h"

TEST(LettersTests, NumberReturnedAsLetters) {
	char* letters = numAsLetters(428);
	fprintf(stdout, "\nOutput: %s\n", letters);
	EXPECT_STREQ("428",letters);
}

TEST(LettersTests, LetterLengthAsExpected) {
	_int64 length = letterLength((char*)"abcd123");
	fprintf(stdout, "\nOutput: %d\n", length);
	EXPECT_EQ(length,7);
}


TEST(LettersTests, ReturnsAppendedAllocation) {
	char* letters = numAsLetters(428);
	fprintf(stdout, "\nOutput: %s\n", letters);
	char* appendingLetters = numAsLetters(731);
	fprintf(stdout, "\nOutput: %s\n", appendingLetters);
	char* appendedLetters = appendLetters(letters,appendingLetters);
	fprintf(stdout, "\nOutput: %s\n", appendedLetters);
	EXPECT_STREQ("428731",appendedLetters);
}

TEST(LettersTests, ReturnsBuiltPath) {	
	char* pathSepLettersChar = (char*)"\\";
	char* letters = numAsLetters(428);
	fprintf(stdout, "\nOutput: %s\n", letters);
	fprintf(stdout, "\nOutput: %s\n", pathSepLettersChar);
	char* appendedLetters = appendLetters(letters,pathSepLettersChar);
	fprintf(stdout, "\nOutput: %s\n", appendedLetters);
	EXPECT_STREQ("428\\",appendedLetters);
}

TEST(LettersTests, ReturnsLettersBetweenListsIndices) {	

	char* letters = (char*)"Letters123";
	List* indicesList = newList();
	_int64 index1 = 4;
	_int64 index2 = 7;
	newLastItem(indicesList, (void*)index1);
	newLastItem(indicesList, (void*)index2);

	char* lettersBetween = lettersBetweenListsIndices(letters,indicesList);
	fprintf(stdout, "\nLetters between: %s\n", lettersBetween);
	EXPECT_STREQ("ers1",lettersBetween);
}

TEST(LettersTests, ReturnsLettersBetweenIndices) {	

	char* letters = (char*)"Letters123";
	
	_int64 index1 = 4;
	_int64 index2 = 7;

	char* lettersBetween = lettersBetweenIndices(letters,index1,index2);
	fprintf(stdout, "\nLetters between: %s\n", lettersBetween);
	EXPECT_STREQ("ers1",lettersBetween);
}
