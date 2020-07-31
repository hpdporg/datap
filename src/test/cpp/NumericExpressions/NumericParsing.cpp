#include "datap.h"
#include "NumericParsing.h"


TEST(NumExpNumParsingTests, ParsesNumExp) {
	NumericParsing* numParsing = newNumericParsing();
	fprintf(stdout, "\nHandle: %d\n", (int)numParsing);
	EXPECT_TRUE((numParsing != 0));
}
