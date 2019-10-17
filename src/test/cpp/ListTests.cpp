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

TEST(ListTests, ItemNumbersInList) {
	List* list1 = newList();
	fprintf(stdout, "\nOutput: %d\n", (int)list1);
	EXPECT_TRUE((list1 !=0));
	int item1 = 2;
	int item2 = 41;
	int item3 = 80;
	fprintf(stdout, "\Item1: %d\n", (int)item1);
	fprintf(stdout, "\Item2: %d\n", (int)item2);
	fprintf(stdout, "\Item3: %d\n", (int)item3);
	newLastItem(list1,(void*)item1);
	newLastItem(list1,(void*)item2);
	newLastItem(list1,(void*)item3);

	fprintf(stdout, "\nItems Count: %d\n",list1->itemsCount);
	EXPECT_TRUE((list1->itemsCount ==3));

	resetIndex(list1);
	while (list1->index < list1->itemsCount){
		int numberItem = (int)getNextItem(list1);
		fprintf(stdout,"\nNext item: %d\n",numberItem);
		if (list1->index ==1){	// getNextItem increments index implicitly following call
			EXPECT_EQ(2,numberItem);
		}
		if (list1->index ==2){	// getNextItem increments index implicitly following call
			EXPECT_EQ(41,numberItem);
		}
		if (list1->index ==3){	// getNextItem increments index implicitly following call
			EXPECT_EQ(80,numberItem);
		}
	}

}


TEST(ListTests, ListIndexCanBeDecreasedToZero) {
	List* list = newList();
	_int64 item1 = 1;
	_int64 item2 = 2;
	_int64 item3 = 3;
	_int64 item4 = 4;
	newLastItem(list,(void*)item1);
	newLastItem(list,(void*)item2);
	newLastItem(list,(void*)item3);
	newLastItem(list,(void*)item4);

	_int64 result = 0;
	result = (_int64)getNextItem(list);
	result = (_int64)getNextItem(list);
	list->index = 0;	
	result = (_int64)getNextItem(list);
	result = (_int64)getNextItem(list);

	fprintf(stdout,"\nResult: %d\n",result);
	EXPECT_EQ(2,result);


}

TEST(ListTests, ListIndexCanBeDecreased) {
	List* list = newList();
	_int64 item1 = 1;
	_int64 item2 = 2;
	_int64 item3 = 3;
	_int64 item4 = 4;
	newLastItem(list,(void*)item1);
	newLastItem(list,(void*)item2);
	newLastItem(list,(void*)item3);
	newLastItem(list,(void*)item4);

	_int64 result = 0;
	result = (_int64)getNextItem(list);
	result = (_int64)getNextItem(list);
	list->index = 1;	
	result = (_int64)getNextItem(list);
	result = (_int64)getNextItem(list);

	fprintf(stdout,"\nResult: %d\n",result);
	EXPECT_EQ(3,result);


}