#include "datap.h"
#include "NumExpRefValTests.h"



TEST(NumExpRefValTests, AllocatesNewNumExpRefVal) {
	NumExpRefVal* numExpRefVal = newNumExpRefVal();
	
	fprintf(stdout, "\nnumExp ref val alloc: %d\n", (int)numExpRefVal);
	EXPECT_NE((int)numExpRefVal,0);
}


TEST(NumExpRefValTests, ParsesNewNumExpRefVal) {
	char* ref1Label = (char*)"ref1";
	NumExpRefVal* numExpRefVal = newNumExpRefVal();
	parseNumExpRefVal(numExpRefVal);


	/*fprintf(stdout, "\nnumExp flag: %d\n", (int)numExp->expressionFlags);
	EXPECT_EQ(NUM_EXP_LESS, numExp->expressionFlags);*/
}
