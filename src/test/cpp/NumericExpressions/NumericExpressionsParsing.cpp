#include "datap.h"
#include "NumericExpressionsParsing.h"


TEST(NumExpParsingTests, ParsesNumExp) {
	NumericExpression* numExp = newNumericExpression();
	char* expression = (char*)"= ref4 + 4";
	numExp->expressionAlloc = expression;
	parseNumExpression(numExp);
	fprintf(stdout, "\nnumExp flag: %d\n", (int)numExp->numericConditionFlag);
	EXPECT_EQ(0, numExp->numericConditionFlag);
}

TEST(NumExpParsingTests, ParsesCondExp) {
	NumericExpression* numExp = newNumericExpression();
	char* expression = (char*)"ref1 same 3";
	numExp->expressionAlloc = expression;
	parseNumExpression(numExp);
	fprintf(stdout, "\nnumExp flag: %d\n", (int)numExp->numericConditionFlag);
	EXPECT_EQ(1, numExp->numericConditionFlag);
}

TEST(NumExpParsingTests, ParsesDefExp) {
	NumericExpression* numExp = newNumericExpression();
	char* expression = (char*)"= ref3";
	numExp->expressionAlloc = expression;
	parseNumExpression(numExp);
	fprintf(stdout, "\nnumExp flag: %d\n", (int)numExp->numericConditionFlag);
	EXPECT_EQ(0, numExp->numericConditionFlag);
}

TEST(NumExpParsingTests, ParsedExpInFlags) {
	NumericExpression* numExp = newNumericExpression();
	char* expression = (char*)"= ref3";
	numExp->expressionAlloc = expression;
	parseNumExpression(numExp);
	fprintf(stdout, "\nnumExp flag: %d\n", (int)numExp->evalFlags);
	EXPECT_EQ(1, numExp->evalFlags);
}