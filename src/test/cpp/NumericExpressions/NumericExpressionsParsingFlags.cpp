#include "datap.h"
#include "NumericExpressionsParsingFlags.h"



TEST(NumExpParsingFlagsTests, ParsesMoreCond) {
	NumericExpression* numExp = newNumericExpression();
	char* expression = (char*)"ref1 > 3";
	numExp->expressionAlloc = expression;
	parseNumExpression(numExp);
	fprintf(stdout, "\nnumExp flag: %d\n", (int)numExp->expressionFlags);
	EXPECT_EQ(NUM_EXP_MORE,numExp->expressionFlags);
}


TEST(NumExpParsingFlagsTests, ParsesLessCond) {
	NumericExpression* numExp = newNumericExpression();
	char* expression = (char*)"ref1 < 3";
	numExp->expressionAlloc = expression;
	parseNumExpression(numExp);
	fprintf(stdout, "\nnumExp flag: %d\n", (int)numExp->expressionFlags);
	EXPECT_EQ(NUM_EXP_LESS, numExp->expressionFlags);
}

TEST(NumExpParsingFlagsTests, ParsesSameCond) {
	NumericExpression* numExp = newNumericExpression();
	char* expression = (char*)"ref1 same 3";
	numExp->expressionAlloc = expression;
	parseNumExpression(numExp);
	fprintf(stdout, "\nnumExp flag: %d\n", (int)numExp->expressionFlags);
	EXPECT_EQ(NUM_EXP_SAME, numExp->expressionFlags);
}

TEST(NumExpParsingFlagsTests, ParsesContainsCond) {
	NumericExpression* numExp = newNumericExpression();
	char* expression = (char*)"ref1 contains 3";
	numExp->expressionAlloc = expression;
	parseNumExpression(numExp);
	fprintf(stdout, "\nnumExp flag: %d\n", (int)numExp->expressionFlags);
	EXPECT_EQ(NUM_EXP_CONTAINS, numExp->expressionFlags);
}

TEST(NumExpParsingFlagsTests, ParsesWithinCond) {
	NumericExpression* numExp = newNumericExpression();
	char* expression = (char*)"ref1 within 3";
	numExp->expressionAlloc = expression;
	parseNumExpression(numExp);
	fprintf(stdout, "\nnumExp flag: %d\n", (int)numExp->expressionFlags);
	EXPECT_EQ(NUM_EXP_WITHIN, numExp->expressionFlags);
}

TEST(NumExpParsingFlagsTests, ParsesDefFlag) {
	NumericExpression* numExp = newNumericExpression();
	char* expression = (char*)"= ref1";
	numExp->expressionAlloc = expression;
	parseNumExpression(numExp);
	fprintf(stdout, "\nnumExp flag: %d\n", (int)numExp->expressionFlags);
	EXPECT_EQ(NUM_EXP_DEF_ONLY, numExp->expressionFlags);
}

TEST(NumExpParsingFlagsTests, ParsesNumFlag) {
	NumericExpression* numExp = newNumericExpression();
	char* expression = (char*)"= ref1 - 3";
	numExp->expressionAlloc = expression;
	parseNumExpression(numExp);
	fprintf(stdout, "\nnumExp flag: %d\n", (int)numExp->expressionFlags);
	EXPECT_EQ(NUM_EXP_DEF_NUM, numExp->expressionFlags);
}