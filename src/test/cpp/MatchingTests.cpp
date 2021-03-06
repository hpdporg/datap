#include "datap.h"
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
	char* letters = (char*)"ABDAJL221";
	char* comparisonLetters = (char*)"ABDAJL221";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	List* matchResults = lettersSame(letters, comparisonLetters);
	fprintf(stdout, "\nItems count: %d\n", matchResults->itemsCount);
	EXPECT_EQ(1,matchResults->itemsCount);

}

TEST(MatchingTest, DoesNotMatchSameLetters) {
	char* letters = (char*)"ABDAJL221";
	char* comparisonLetters = (char*)"ABD29AJL221";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	List* matchResults = lettersSame(letters, comparisonLetters);
	fprintf(stdout, "\nItems count: %d\n", matchResults->itemsCount);
	EXPECT_EQ(0,matchResults->itemsCount);

}

TEST(MatchingTest, ReturnsExactMatchResult) {
	char* letters = (char*)"ABDAJL221";
	char* comparisonLetters = (char*)"ABDAJL221";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	_int64 matchResult = lettersSameExact(letters, comparisonLetters);
	fprintf(stdout, "\nMatch result: %d\n", matchResult);
	EXPECT_EQ(1,matchResult);

}

TEST(MatchingTest, ReturnsNoExactMatchResultWithSmallerComparisonLetters) {
	char* letters = (char*)"storeFile";
	char* comparisonLetters = (char*)"ref2";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	_int64 matchResult = lettersSameExact(letters, comparisonLetters);
	fprintf(stdout, "\nMatch result: %d\n", matchResult);
	EXPECT_EQ(0,matchResult);

}


TEST(MatchingTest, DoesNotReturnExactMatchResult) {
	char* letters = (char*)"ABDAJL221";
	char* comparisonLetters = (char*)"ABDAJL2219";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	_int64 matchResult = lettersSameExact(letters, comparisonLetters);
	fprintf(stdout, "\nMatch result: %d\n", matchResult);
	EXPECT_EQ(0,matchResult);

}

TEST(MatchingTest, ReturnsNextMatchIndex) {
	char* letters = (char*)"fffABDAJL221119";
	char* comparisonLetters = (char*)"ABDAJL221";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	_int64 matchIndex = getNextMatchIndex(letters, comparisonLetters);
	fprintf(stdout, "\nMatch index: %d\n", matchIndex);
	EXPECT_EQ(3,matchIndex);

}

TEST(MatchingTest, ReturnsNoMatchPresence) {
	char* letters = (char*)"ABDdjAJL2219";
	char* comparisonLetters = (char*)"ABDAJL221";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	_int64 matchExists = hasMatch(letters, comparisonLetters);
	fprintf(stdout, "\nMatch result: %d\n", matchExists);
	EXPECT_EQ(0,matchExists);

}

TEST(MatchingTest, ReturnsMatchPresence) {
	char* letters = (char*)"fffABDAJL221119";
	char* comparisonLetters = (char*)"ABDAJL221";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	_int64 matchExists = hasMatch(letters, comparisonLetters);
	fprintf(stdout, "\nMatch result: %d\n", matchExists);
	EXPECT_EQ(1,matchExists);

}


TEST(MatchingTest, ListReturnsNoMatchPresence) {
	char* letters1 = (char*)"AB99JL221";
	char* letters2 = (char*)"ADAJL221";
	char* letters3 = (char*)"ff441119";
	char* comparisonLetters = (char*)"ABDAJL221";

	List* list = newList();
	newLastItem(list, letters1);
	newLastItem(list, letters2);
	newLastItem(list, letters3);

	//fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	_int64 matchExists = listHasMatch(list, comparisonLetters);
	fprintf(stdout, "\nMatch result: %d\n", matchExists);
	EXPECT_EQ(0, matchExists);

}

TEST(MatchingTest, ListReturnsMatchPresence) {
	char* letters1 = (char*)"AB99JL221";
	char* letters2 = (char*)"ABDAJL221";
	char* letters3 = (char*)"gf441119";
	char* comparisonLetters = (char*)"ABDAJL221";

	List* list = newList();
	newLastItem(list, letters1);
	newLastItem(list, letters2);
	newLastItem(list, letters3);

	//fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nComparison Letters: %s\n", comparisonLetters);
	_int64 matchExists = listHasMatch(list, comparisonLetters);
	fprintf(stdout, "\nMatch result: %d\n", matchExists);
	EXPECT_EQ(1, matchExists);

}

TEST(MatchingTest, ReturnsExtractsBetweenDelimiters) {
	char* letters = (char*)"val1,val2,val3,val4";
	char* delimiter = (char*)",";
	
	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nDelimiter Letters: %s\n", delimiter);
	List* extractList = extractBetween(letters, delimiter);
	fprintf(stdout, "\nMatch count: %d\n", extractList->itemsCount);

	resetIndex(extractList);
	while (extractList->index < extractList->itemsCount){
		char* extractVal = (char*)getNextItem(extractList);
		fprintf(stdout, "\nNext extract val: %s",extractVal);
	}
	EXPECT_EQ(4, extractList->itemsCount);

}

TEST(MatchingTest, ReturnsExtractsBetweenDelimitersWithtrailingDelimiter) {
	char* letters = (char*)"val1,val2,val3,val4,";
	char* delimiter = (char*)",";

	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\nDelimiter Letters: %s\n", delimiter);
	List* extractList = extractBetween(letters, delimiter);
	fprintf(stdout, "\nMatch count: %d\n", extractList->itemsCount);

	resetIndex(extractList);
	while (extractList->index < extractList->itemsCount) {
		char* extractVal = (char*)getNextItem(extractList);
		fprintf(stdout, "\nNext extract val: %s", extractVal);
	}
	EXPECT_EQ(4,extractList->itemsCount);

}

TEST(MatchingTest, ReturnsFlowExtractedBetweenDelimiters) {
	char* letters = (char*)"val1,val2,val3,val4\nval5,val6,val7,val8\n";
	char* iDelimiter = (char*)",";
	char* jDelimiter = (char*)"\n";

	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\niDelimiter Letters: %s\n", iDelimiter);
	fprintf(stdout, "\njDelimiter Letters: %s\n", jDelimiter);
	Flow* flow = extractFlowBetween(letters, iDelimiter, jDelimiter);
	fprintf(stdout, "\nMatch count: %d\n", (flow->length*flow->width));

	resetFlowIJ(flow);
	while (flow->j < flow->length) {
		char* extractVal = (char*)getNextFlowItem(flow);
		fprintf(stdout, "\nNext extract val: %s", extractVal);
	}
	EXPECT_EQ(8, (flow->length*flow->width));

}
TEST(MatchingTest, ReturnsFlowExtractedBetweenDelimitersWithoutTrailingNewline) {
	char* letters = (char*)"val1,val2,val3,val4\nval5,val6,val7,val8";
	char* iDelimiter = (char*)",";
	char* jDelimiter = (char*)"\n";

	fprintf(stdout, "\nLetters: %s\n", letters);
	fprintf(stdout, "\niDelimiter Letters: %s\n", iDelimiter);
	fprintf(stdout, "\njDelimiter Letters: %s\n", jDelimiter);
	Flow* flow = extractFlowBetween(letters, iDelimiter, jDelimiter);
	fprintf(stdout, "\nMatch count: %d\n", (flow->length*flow->width));

	resetFlowIJ(flow);
	while (flow->j < flow->length) {
		char* extractVal = (char*)getNextFlowItem(flow);
		fprintf(stdout, "\nNext extract val: %s", extractVal);
	}
	EXPECT_EQ(8, (flow->length*flow->width));

}