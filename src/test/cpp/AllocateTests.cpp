#include "datap.h"
#include "AllocateTests.h"

TEST(AllocateTest, ReturnsLinearAllocation) {
	int res = (int)linearAllocate(4);
	fprintf(stdout, "\nOutput: %d\n", res);
	EXPECT_NE(res,0);
}


TEST(AllocateTest, ReturnsNewStrucAllocation) {
	void* res = allocateNew(24);
	fprintf(stdout, "\nOutput: %d\n", *((_int64*)(res)));
	fprintf(stdout, "\nOutput offset 1: %d\n", *((_int64*)(res)+1));
	fprintf(stdout, "\nOutput offset 2: %d\n", *((_int64*)(res)+2));
	EXPECT_EQ(*((_int64*)(res)),0);
	EXPECT_EQ(*((_int64*)(res)+1), 0);
	EXPECT_EQ(*((_int64*)(res)+2), 0);
}