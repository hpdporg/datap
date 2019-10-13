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
		if (matchResults->index ==1){	// getNextItem increments index implicitly following call
			EXPECT_EQ(6,matchResult);
		}
	}

	

}

TEST(MatchingTest, TextContainsFirstMatchOnly) {
	Matches* matches = newMatches();
	matches->flags = (MATCH_START|MATCH_FIRST|MATCH_TRANSFORM);
	matches->transformFlags = TRANSFORM_CONTAINS;

	char* contains1 = (char*)"Ma";
	newLastItem(matches->containsRangeList, contains1);

	char* letters = (char*)"HAS a Match SomwMaehere";

	List* matchResults = getMatches( matches, letters);

	while (matchResults->index < matchResults->itemsCount){
		int matchResult = (int)getNextItem(matchResults);
		fprintf(stdout,"\nNext result: %d\n",matchResult);
		if (matchResults->index ==1){	// getNextItem increments index implicitly following call
			EXPECT_EQ(6,matchResult);
		}
	}

	EXPECT_EQ(1,matchResults->itemsCount);

}

TEST(MatchingTest, TextContainsFirstSecondMatch) {
	Matches* matches = newMatches();
	matches->flags = (MATCH_START|MATCH_EVERY|MATCH_TRANSFORM);
	matches->transformFlags = TRANSFORM_CONTAINS;

	char* contains1 = (char*)"Ma";
	newLastItem(matches->containsRangeList, contains1);

	char* letters = (char*)"HAS a Match SomwMaehere";

	List* matchResults = getMatches( matches, letters);

	while (matchResults->index < matchResults->itemsCount){
		int matchResult = (int)getNextItem(matchResults);
		fprintf(stdout,"\nNext result: %d\n",matchResult);
		if (matchResults->index ==1){	// getNextItem increments index implicitly following call
			EXPECT_EQ(6,matchResult);
		}
		if (matchResults->index ==2){	// getNextItem increments index implicitly following call
			EXPECT_EQ(16,matchResult);
		}
	}

	EXPECT_EQ(2,matchResults->itemsCount);

}

TEST(MatchingTest, TextContainsEveryStartEndMatch) {
	Matches* matches = newMatches();
	matches->flags = (MATCH_START | MATCH_END | MATCH_EVERY | MATCH_TRANSFORM);
	matches->transformFlags = TRANSFORM_CONTAINS;

	char* contains1 = (char*)"Ma";
	newLastItem(matches->containsRangeList, contains1);

	char* letters = (char*)"HAS a Match SomwMaehere";

	List* matchResults = getMatches(matches, letters);

	while (matchResults->index < matchResults->itemsCount) {
		int matchResult = (int)getNextItem(matchResults);
		fprintf(stdout, "\nNext result: %d\n", matchResult);
		if (matchResults->index == 1) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(6, matchResult);
		}
		if (matchResults->index == 2) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(7, matchResult);
		}
		if (matchResults->index == 3) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(16, matchResult);
		}
		if (matchResults->index == 4) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(17, matchResult);
		}
	}

	EXPECT_EQ(4, matchResults->itemsCount);

}