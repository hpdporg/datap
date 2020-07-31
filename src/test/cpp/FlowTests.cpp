#include "datap.h"
#include "FlowTests.h"

TEST(FlowTests, NewFlowReturnsHandle) {
	Flow* flow = newFlow();
	fprintf(stdout, "\nHandle: %d\n", (int)flow);
	EXPECT_TRUE((flow !=0));
}

TEST(FlowTests, NewFlowIsInitializedToDefaults) {
	Flow* flow = newFlow();
	fprintf(stdout, "\nHandle: %d\n", (int)flow);
	EXPECT_EQ(flow->lists->itemsCount,0);
	EXPECT_EQ(flow->width,0);
	EXPECT_EQ(flow->i,0);
	EXPECT_EQ(flow->j,0);
	EXPECT_EQ(flow->length,0);
	EXPECT_EQ(flow->paddingValue,0);
}


TEST(FlowTests, IncreasesWidth) {
	Flow* flow = newFlow();
	fprintf(stdout, "\nHandle: %d\n", (int)flow);
	EXPECT_EQ(flow->lists->itemsCount,0);
	EXPECT_EQ(flow->width,0);
	EXPECT_EQ(flow->length,0);
	increaseFlowWidth(flow,4);
	EXPECT_EQ(flow->lists->itemsCount,4);
	EXPECT_EQ(flow->width,4);
	EXPECT_EQ(flow->length,0);
	fprintf(stdout, "\nWidth: %d\n", (int)flow->width);

}