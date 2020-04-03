#include "datap.h"
#include "NumericExpressions.h"

TEST(NumExpTests, NewNumExpReturnsHandle) {
	NumericExpression* numExp = newNumericExpression();
	fprintf(stdout, "\nHandle: %d\n", (int)numExp);
	EXPECT_TRUE((numExp !=0));
}


TEST(NumExpTests, FirstNumExpTermListItem) {
	List* numExpList = getNumExpTermList();

	char* firstItem = (char*)getNextItem(numExpList);
	fprintf(stdout, "\nItem: %s\n", firstItem);
	EXPECT_STREQ(firstItem, (char*)"+");
	EXPECT_EQ(numExpList->itemsCount,4);
}

TEST(NumExpTests, FirstCondExpTermListItem) {
	List*  condExpList = getCondExpTermList();

	char* firstItem = (char*)getNextItem(condExpList);
	fprintf(stdout, "\nItem: %s\n", firstItem);
	EXPECT_STREQ(firstItem, (char*)">");
	EXPECT_EQ(condExpList->itemsCount, 5);
}

TEST(NumExpTests, FirstDefExpTermListItem) {
	List*  defExpList = getDefExpTermList();

	char* firstItem = (char*)getNextItem(defExpList);
	fprintf(stdout, "\nItem: %s\n", firstItem);
	EXPECT_STREQ(firstItem, (char*)"=");
	EXPECT_EQ(defExpList->itemsCount, 1);
}