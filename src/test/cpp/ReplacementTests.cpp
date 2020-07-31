#include "datap.h"
#include "ReplacementTests.h"



TEST(ReplacementTest, ReplaceEveryOccurence) {
	Matches* matches = newMatches();
	matches->flags = (MATCH_START | MATCH_END | MATCH_EVERY | MATCH_TRANSFORM);
	matches->transformFlags = TRANSFORM_CONTAINS;

	char* contains1 = (char*)"Ma";
	newLastItem(matches->containsRangeList, contains1);
	newLastItem(matches->containsRangeList, contains1);

	char* letters = (char*)"HAS a Match SomwMaehere";

	List* matchResults = getMatches(matches, letters);

	List* replacementVals = newList();
	char* replaceVal = (char*)"RV8U";
	newLastItem(replacementVals, replaceVal);

	
	fprintf(stdout,"\nList length: %d\n",matchResults->itemsCount);

	
	char* newLetters = replaceLettersWithList(REPLACE_BETWEEN,letters, replacementVals, matchResults);

	fprintf(stdout, "\nDebugReplaced letters: %d\n", (int)newLetters);
	fprintf(stdout, "\nReplaced letters: %s\n", newLetters);

	EXPECT_STREQ("HAS a RV8Utch SomwRV8Uehere",newLetters);



}



TEST(ReplacementTest, ReplaceOccurrencesWithDifferentVals) {
	Matches* matches = newMatches();
	matches->flags = (MATCH_START | MATCH_END | MATCH_EVERY | MATCH_TRANSFORM);
	matches->transformFlags = TRANSFORM_CONTAINS;

	char* contains1 = (char*)"Ma";
	newLastItem(matches->containsRangeList, contains1);
	
	char* letters = (char*)"HAS a Match SomwMaehere";

	List* matchResults = getMatches(matches, letters);

	List* replacementVals = newList();
	char* replaceVal = (char*)"RV8U";
	char* replaceVal2 = (char*)"888d8U";

	newLastItem(replacementVals, replaceVal);
	newLastItem(replacementVals, replaceVal2);


	fprintf(stdout, "\nList length: %d\n", matchResults->itemsCount);


	char* newLetters = replaceLettersWithList(REPLACE_BETWEEN, letters, replacementVals, matchResults);

	fprintf(stdout, "\nDebugReplaced letters: %d\n", (int)newLetters);
	fprintf(stdout, "\nReplaced letters: %s\n", newLetters);



	EXPECT_STREQ("HAS a RV8Utch Somw888d8Uehere", newLetters);


}


TEST(ReplacementTest, ReplaceOccurrencesWithDifferentValsUsingWrapper) {
	char* contains1 = (char*)"Ma";

	char* letters = (char*)"HAS a Match SomwMaehere";

	List* replacementVals = newList();
	char* replaceVal = (char*)"RV8U";
	char* replaceVal2 = (char*)"888d8U";

	newLastItem(replacementVals, replaceVal);
	newLastItem(replacementVals, replaceVal2);

	fprintf(stdout, "\nOriginal letters: %d\n", letters);


	char* newLetters = replaceContainsLettersWithList(letters, replacementVals, contains1);

	fprintf(stdout, "\nDebugReplaced letters: %d\n", (int)newLetters);
	fprintf(stdout, "\nReplaced letters: %s\n", newLetters);



	EXPECT_STREQ("HAS a RV8Utch Somw888d8Uehere", newLetters);


}



TEST(ReplacementTest, ReplaceOccurrencesWithFlowRows) {
	char* contains1 = (char*)"Ma";

	char* letters = (char*)"HAS a Match SomwMaehere";

	Flow* flow = newFlow();
	increaseFlowWidth(flow, 2);

	List* replacementVals1 = newList();
	char* replaceVal = (char*)"RV8U";
	char* replaceVal2 = (char*)"888d8U";


	newLastItem(replacementVals1, replaceVal);
	newLastItem(replacementVals1, replaceVal2);


	List* replacementVals2 = newList();
	char* replaceVal3 = (char*)"Rz8U";
	char* replaceVal4 = (char*)"88108d8U";


	newLastItem(replacementVals2, replaceVal3);
	newLastItem(replacementVals2, replaceVal4);
	
	newLastFlowIVals(flow, replacementVals1);
	newLastFlowIVals(flow, replacementVals2);



	fprintf(stdout, "\nOriginal letters: %s\n", letters);


	List* replacedLettersList = replaceContainsLettersWithFlow(letters, flow, contains1);
	fprintf(stdout, "\nReplaced\n");
	resetIndex(replacedLettersList);

	while (replacedLettersList->index < replacedLettersList->itemsCount) {
		char* replacedVal = (char*)getNextItem(replacedLettersList);
		fprintf(stdout, "\nReplaced letters: %s\n", replacedVal);
		if (replacedLettersList->index == 1) {					// getNextItem increments indices implicitly
			EXPECT_STREQ("HAS a RV8Utch Somw888d8Uehere", replacedVal);
		}
		else if (replacedLettersList->index == 2) {		// getNextItem increments indices implicitly
			EXPECT_STREQ("HAS a Rz8Utch Somw88108d8Uehere", replacedVal);
		}

	}
	EXPECT_EQ(2, replacedLettersList->itemsCount);







}