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

TEST(MatchingTest, MatchStartEndLengthFlowParsedFromFlags) {
	Matches* matches = newMatches();
	matches->flags = (MATCH_START | MATCH_END | MATCH_TRANSFORM);
	matches->transformFlags = TRANSFORM_CONTAINS;


	MatchFlow* matchFlow = processMatchFlags(matches);
	fprintf(stdout, "\nOutput: %d\n", (int)matchFlow);
	EXPECT_EQ(1,matchFlow->start);
	EXPECT_EQ(1,matchFlow->end);
	EXPECT_EQ(1,matchFlow->startEndLength);
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
	//newLastItem(matches->containsRangeList, contains1);

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

TEST(MatchingTest, MatchesSameLetters) {
	char* letters = "ABDAJL221";
	char* comparisonLetters = "ABDAJL221";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	List* matchResults = lettersSame(letters, comparisonLetters);
	fprintf(stdout, "\nItems count: %d\n", matchResults->itemsCount);
	EXPECT_EQ(1,matchResults->itemsCount);

}

TEST(MatchingTest, DoesNotMatchSameLetters) {
	char* letters = "ABDAJL221";
	char* comparisonLetters = "ABD29AJL221";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	List* matchResults = lettersSame(letters, comparisonLetters);
	fprintf(stdout, "\nItems count: %d\n", matchResults->itemsCount);
	EXPECT_EQ(0,matchResults->itemsCount);

}

TEST(MatchingTest, ReturnsExactMatchResult) {
	char* letters = "ABDAJL221";
	char* comparisonLetters = "ABDAJL221";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	_int64 matchResult = lettersSameExact(letters, comparisonLetters);
	fprintf(stdout, "\nMatch result: %d\n", matchResult);
	EXPECT_EQ(1,matchResult);

}

TEST(MatchingTest, DoesNotReturnExactMatchResult) {
	char* letters = "ABDAJL221";
	char* comparisonLetters = "ABDAJL2219";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	_int64 matchResult = lettersSameExact(letters, comparisonLetters);
	fprintf(stdout, "\nMatch result: %d\n", matchResult);
	EXPECT_EQ(0,matchResult);

}

TEST(MatchingTest, ReturnsNextMatchIndex) {
	char* letters = "fffABDAJL221119";
	char* comparisonLetters = "ABDAJL221";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	_int64 matchIndex = getNextMatchIndex(letters, comparisonLetters);
	fprintf(stdout, "\nMatch index: %d\n", matchIndex);
	EXPECT_EQ(3,matchIndex);

}

TEST(MatchingTest, ReturnsNoMatchPresence) {
	char* letters = "ABDdjAJL2219";
	char* comparisonLetters = "ABDAJL221";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	_int64 matchExists = hasMatch(letters, comparisonLetters);
	fprintf(stdout, "\nMatch result: %d\n", matchExists);
	EXPECT_EQ(0,matchExists);

}

TEST(MatchingTest, ReturnsMatchPresence) {
	char* letters = "fffABDAJL221119";
	char* comparisonLetters = "ABDAJL221";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	_int64 matchExists = hasMatch(letters, comparisonLetters);
	fprintf(stdout, "\nMatch result: %d\n", matchExists);
	EXPECT_EQ(1,matchExists);

}