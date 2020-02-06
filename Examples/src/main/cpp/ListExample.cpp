#include "datap.h"
#include <stdio.h>
#include "Examples.h"


void runListExample(){
	
	fprintf(stdout, "List example\n");
	fprintf(stdout, "================\n");
	List* list1 = newList();
	fprintf(stdout, "First, get handle of new list: %d. Items count: %d\n", (_int64)list1, list1->itemsCount);
	_int64 val1 = 2891;
	_int64 val2 = 124;
	_int64 val3 = 552;
	char* val4 = (char*)"val4";
	newLastItem(list1,(void*)val1);
	newLastItem(list1,(void*)val2);
	newLastItem(list1,(void*)val3);
	newLastItem(list1,(void*)val4);
	fprintf(stdout, "Put any type of value or pointer in the List. Items count is now: %d\n", list1->itemsCount);
	fprintf(stdout, "The list implicitly tracks its index. We start at 0: %d\n", list1->index);
	void* nextItem = getNextItem(list1);
	fprintf(stdout, "Next Item: %d\n", (_int64)nextItem);
	fprintf(stdout, "List index implicitly increments, so we are now at 1: %d\n", list1->index);
	nextItem = getNextItem(list1);
	fprintf(stdout, "Next Item: %d. Index: %d\n", (_int64)nextItem, list1->index);
	list1->index = 3;
	nextItem = getNextItem(list1);
	fprintf(stdout, "List handle is just a struct. We can manually set the index: %d. Item: %s\n", list1->index,(char*)nextItem );
	resetIndex(list1);
	nextItem = getNextItem(list1);
	fprintf(stdout, "Or use the reset call: %d. Item: %d\n", list1->index, (_int64)nextItem);
	fprintf(stdout, "================\n");

}