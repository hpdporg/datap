#include "datap.h"
#include "NumExpRefValProcessingTests.h"






TEST(NumExpRefValTests, ProcessesNumExpRefVal) {
	char* ref1Label = (char*)"3898";
	NumExpRefVal* numExpRefVal = newNumExpRefVal();

	numExpRefVal->labelAlloc = ref1Label;
	numExpRefVal->flags = NUM_EXP_REF_VAL_INTEGER;

	processNumExpRefVal(numExpRefVal);


	fprintf(stdout, "\nnumExp val: %d\n", (int)numExpRefVal->val);
	EXPECT_EQ(3898, numExpRefVal->val);
}
