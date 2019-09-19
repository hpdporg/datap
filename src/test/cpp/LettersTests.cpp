#include "AsmIncludes.h"
#include "LettersTests.h"

TEST(LettersTests, NumberReturnedAsLetters) {
	char* letters = numAsLetters(428);
	fprintf(stdout, "\nOutput: %s\n", letters);
	EXPECT_STREQ("428",letters);
}
