#include "AsmIncludes.h"
#include "MatchingTests.h"


TEST(MatchingTest, ReturnsMatchAllocation) {
	Match* match = newMatch();
	fprintf(stdout, "\nOutput: %d\n", (int)match);
	EXPECT_TRUE((match !=NULL));
}
