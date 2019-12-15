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
	fprintf(stdout, "\nItem1: %d\n", (int)item1);
	fprintf(stdout, "\nItem2: %d\n", (int)item2);
	fprintf(stdout, "\nItem3: %d\n", (int)item3);
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


TEST(ListTests, ExtendsList) {
	List* list1 = newList();
	List* list2 = newList();

	int item1 = 2;
	int item2 = 41;
	int item3 = 80;
	int item4 = 130;
	int item5 = 87;

	fprintf(stdout, "\nItem1: %d\n", (int)item1);
	fprintf(stdout, "\nItem2: %d\n", (int)item2);
	fprintf(stdout, "\nItem3: %d\n", (int)item3);
	fprintf(stdout, "\nItem4: %d\n", (int)item4);
	fprintf(stdout, "\nItem5: %d\n", (int)item5);
	newLastItem(list1, (void*)item1);
	newLastItem(list1, (void*)item2);
	newLastItem(list1, (void*)item3);

	newLastItem(list2, (void*)item4);
	newLastItem(list2, (void*)item5);

	fprintf(stdout, "\nItems Count: %d\n", list1->itemsCount);
	EXPECT_TRUE((list1->itemsCount == 3));

	extendList(list1, list2);
	resetIndex(list1);
	while (list1->index < list1->itemsCount) {
		int numberItem = (int)getNextItem(list1);
		fprintf(stdout, "\nNext item: %d\n", numberItem);
		if (list1->index == 1) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(2, numberItem);
		}
		if (list1->index == 2) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(41, numberItem);
		}
		if (list1->index == 3) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(80, numberItem);
		}
		if (list1->index == 4) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(130, numberItem);
		}
		if (list1->index == 5) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(87, numberItem);
		}
	}
}

TEST(ListTests, LastItemNestingIsDefined) {
	List* list1 = newList();


	int item1 = 2;
	int item2 = 41;
	int item3 = 80;
	int item4 = 130;
	int item5 = 87;
	int item6 = 87;
	int item7 = 87;

	fprintf(stdout, "\nItem1: %d\n", (int)item1);
	fprintf(stdout, "\nItem2: %d\n", (int)item2);
	fprintf(stdout, "\nItem3: %d\n", (int)item3);
	fprintf(stdout, "\nItem4: %d\n", (int)item4);
	fprintf(stdout, "\nItem5: %d\n", (int)item5);
	newLastItem(list1, (void*)item1);
	lastItemNesting(list1, 0);
	newLastItem(list1, (void*)item2);
	lastItemNesting(list1, 1);
	newLastItem(list1, (void*)item3);
	lastItemNesting(list1, 2);
	newLastItem(list1, (void*)item4);
	lastItemNesting(list1, 0);
	newLastItem(list1, (void*)item5);
	lastItemNesting(list1, 1);
	newLastItem(list1, (void*)item6);
	lastItemNesting(list1, 0);
	newLastItem(list1, (void*)item7);
	lastItemNesting(list1, 1);

	fprintf(stdout, "\nItems Count: %d\n", list1->itemsCount);
	EXPECT_TRUE((list1->itemsCount == 7));


	resetIndex(list1);
	while (list1->index < list1->itemsCount) {
		int nestingNum = (int)getNextItemNesting(list1);
		int numberItem = (int)getNextItem(list1);
		fprintf(stdout, "\nNext item, nesting: %d %d\n", numberItem, nestingNum);
		if (list1->index == 1) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(2, numberItem);
			EXPECT_EQ(0, nestingNum);
		}
		if (list1->index == 2) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(41, numberItem);
			EXPECT_EQ(1, nestingNum);
		}
		if (list1->index == 3) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(80, numberItem);
			EXPECT_EQ(2, nestingNum);
		}
		if (list1->index == 4) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(130, numberItem);
			EXPECT_EQ(0, nestingNum);
		}
		if (list1->index == 5) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(87, numberItem);
			EXPECT_EQ(1, nestingNum);
		}
		if (list1->index == 6) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(87, numberItem);
			EXPECT_EQ(0, nestingNum);
		}
		if (list1->index == 7) {	// getNextItem increments index implicitly following call
			EXPECT_EQ(87, numberItem);
			EXPECT_EQ(1, nestingNum);
		}
	}
}