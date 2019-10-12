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