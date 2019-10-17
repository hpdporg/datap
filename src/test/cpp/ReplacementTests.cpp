#include "AsmIncludes.h"
#include "ReplacementTests.h"



TEST(ReplacementTest, ReplaceEveryOccurence) {
	Matches* matches = newMatches();
	matches->flags = (MATCH_START | MATCH_END | MATCH_EVERY | MATCH_TRANSFORM);
	matches->transformFlags = TRANSFORM_CONTAINS;

	char* contains1 = (char*)"Ma";
	newLastItem(matches->containsRangeList, contains1);

	char* letters = (char*)"HAS a Match SomwMaehere";

	List* matchResults = getMatches(matches, letters);

	List* replacementVals = newList();
	char* replaceVal = (char*)"RV8U";
	newLastItem(replacementVals, replaceVal);

	char* newLetters = replaceLettersWithList(REPLACE_BETWEEN,letters, replacementVals, matchResults);

		//fprintf(stdout, "\nDebugReplaced letters: %d\n", (int)newLetters);
	fprintf(stdout, "\nReplaced letters: %s\n", newLetters);

	



}