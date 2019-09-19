#include "AsmIncludes.h"
#include "ListTests.h"

TEST(ListTests, NewListReturnsAllocation) {
	List* list1 = newList();
	fprintf(stdout, "\nOutput: %d\n", (int)list1);
	EXPECT_TRUE((list1 !=0));
}

TEST(ListTests, ItemCountIncreases) {
	List* list1 = newList();
	fprintf(stdout, "\nOutput: %d\n", (int)list1);
	EXPECT_TRUE((list1 !=0));
	void* item1 = linearAllocate(4);
	fprintf(stdout, "\nOutput: %d\n", (int)item1);
	_int64 item1Val = 445;
	(*(_int64*)item1) = item1Val;
	newLastItem(list1,item1);
	
	fprintf(stdout, "\nItems Count: %d\n",list1->itemsCount);
	EXPECT_TRUE((list1->itemsCount !=0));

}