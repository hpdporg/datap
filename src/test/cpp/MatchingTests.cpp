#include "AsmIncludes.h"
#include "MatchingTests.h"


TEST(MatchingTest, ReturnsMatchAllocation) {
	Matches* matches = newMatches();
	fprintf(stdout, "\nOutput: %d\n", (int)matches);
	EXPECT_TRUE((matches !=NULL));
}




TEST(MatchingTest, MatchStartEndFlowParsedFromFlags) {
	Matches* matches = newMatches();
	matches->flags = (MATCH_END|MATCH_START);

	MatchFlow* matchFlow = processMatchFlags(matches);
	fprintf(stdout, "\nmatchFlow->start: %d\n", (int)matchFlow->start);
	fprintf(stdout, "\nOutput: %d\n", (int)matchFlow);
	EXPECT_EQ(1,matchFlow->start);
	EXPECT_EQ(1,matchFlow->end);
	EXPECT_EQ(0,matchFlow->everyMatch);
	EXPECT_EQ(0,matchFlow->firstMatch);
	EXPECT_EQ(0,matchFlow->contains);
}

TEST(MatchingTest, MatchEveryFlowParsedFromFlags) {
	Matches* matches = newMatches();
	matches->flags = MATCH_EVERY;


	MatchFlow* matchFlow = processMatchFlags(matches);
	fprintf(stdout, "\nOutput: %d\n", (int)matchFlow);
	EXPECT_EQ(0,matchFlow->start);
	EXPECT_EQ(0,matchFlow->end);
	EXPECT_EQ(1,matchFlow->everyMatch);
	EXPECT_EQ(0,matchFlow->firstMatch);
	EXPECT_EQ(0,matchFlow->contains);
}

TEST(MatchingTest, MatchContainsFlowParsedFromFlags) {
	Matches* matches = newMatches();
	matches->flags = MATCH_TRANSFORM;
	matches->transformFlags = TRANSFORM_CONTAINS;


	MatchFlow* matchFlow = processMatchFlags(matches);
	fprintf(stdout, "\nOutput: %d\n", (int)matchFlow);
	EXPECT_EQ(0,matchFlow->start);
	EXPECT_EQ(0,matchFlow->end);
	EXPECT_EQ(0,matchFlow->everyMatch);
	EXPECT_EQ(0,matchFlow->firstMatch);
	EXPECT_EQ(1,matchFlow->contains);
}

TEST(MatchingTest, TextContainsFirstMatch) {
	Matches* matches = newMatches();
	matches->flags = (MATCH_START|MATCH_FIRST|MATCH_TRANSFORM);
	matches->transformFlags = TRANSFORM_CONTAINS;

	char* contains1 = (char*)"Ma";
	newLastItem(matches->containsRangeList, contains1);

	char* letters = (char*)"HAS a Match Somwehere";

	List* matchResults = getMatches( matches, letters);

	while (matchResults->index < matchResults->itemsCount){
		int matchResult = (int)getNextItem(matchResults);
		fprintf(stdout,"\nNext result: %d\n",matchResult);
	}

}
