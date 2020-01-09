#include "AsmIncludes.h"
#include "ListNestingTests.h"


TEST(ListNestingTests, ListItemsCanUseNesting) {
	List* list = newList();
	_int64 item1 = 1;
	_int64 item2 = 2;
	_int64 item3 = 3;
	_int64 item4 = 4;
	
	newLastItem(list,(void*)item1);	
	newLastItem(list,(void*)item2);
	lastItemNesting(list, 1);
	newLastItem(list,(void*)item3);	
	newLastItem(list,(void*)item4);


	_int64 result = 0;
	_int64 nesting = 0;
	resetIndex(list);
	fprintf(stdout,"\nList items count: %d\n",list->itemsCount);
	while(list->index < list->itemsCount){
		nesting = getNextItemNesting(list);
		result = (_int64)getNextItem(list);		
		fprintf(stdout,"\nNesting: %d\n",nesting);
		fprintf(stdout,"\nVal: %d\n",result);
		if (list->index == 1){									// List increments index implicitly following getNextItem call
			EXPECT_EQ(0,nesting);
		}
		if (list->index == 2){									// List increments index implicitly following getNextItem call
			EXPECT_EQ(1,nesting);
		}
		if (list->index == 3){									// List increments index implicitly following getNextItem call
			EXPECT_EQ(0,nesting);
		}
		if (list->index == 4){									// List increments index implicitly following getNextItem call
			EXPECT_EQ(0,nesting);
		}
	}

	


}

TEST(ListNestingTests, GetsDivergedItem) {
	List* list = newList();
	_int64 item1 = 1;
	_int64 item2 = 2;
	_int64 item3 = 3;
	_int64 item4 = 4;
	
	newLastItem(list,(void*)item1);	
	newLastItem(list,(void*)item2);
	lastItemNesting(list, 1);
	newLastItem(list,(void*)item3);	
	lastItemNesting(list, 1);
	newLastItem(list,(void*)item4);
	lastItemNesting(list, 1);

	_int64 result = 0;
	_int64 nesting = 0;
	resetIndex(list);
	fprintf(stdout,"\nList items count: %d\n",list->itemsCount);

	result = (_int64)getLastDivergedItem(list);
		
		//fprintf(stdout,"\nNesting: %d\n",nesting);
		fprintf(stdout,"\nVal: %d\n",result);

		EXPECT_EQ(1,result);
		

	


}

TEST(ListNestingTests, GetsDivergedItemNesting) {
	List* list = newList();
	_int64 item1 = 1;
	_int64 item2 = 2;
	_int64 item3 = 3;
	_int64 item4 = 4;
	
	newLastItem(list,(void*)item1);	
	newLastItem(list,(void*)item2);
	lastItemNesting(list, 1);
	newLastItem(list,(void*)item3);	
	lastItemNesting(list, 1);
	newLastItem(list,(void*)item4);
	lastItemNesting(list, 1);

	_int64 result = 0;
	_int64 nesting = 0;
	resetIndex(list);
	fprintf(stdout,"\nList items count: %d\n",list->itemsCount);

	nesting = (_int64)getLastDivergedItemNesting(list);
		
		fprintf(stdout,"\nNesting: %d\n",nesting);
		
		EXPECT_EQ(0,nesting);
		

	


}

TEST(ListNestingTests, GetsConvergedItemCount) {
	List* list = newList();
	_int64 item1 = 1;
	_int64 item2 = 2;
	_int64 item3 = 3;
	_int64 item4 = 4;
	
	newLastItem(list,(void*)item1);	
	newLastItem(list,(void*)item2);
	lastItemNesting(list, 1);
	newLastItem(list,(void*)item3);	
	lastItemNesting(list, 1);
	newLastItem(list,(void*)item4);
	lastItemNesting(list, 1);

	_int64 result = 0;
	_int64 nesting = 0;
	resetIndex(list);
	fprintf(stdout,"\nList items count: %d\n",list->itemsCount);

	result = (_int64)getConvergedItemCount(list);
		
		//fprintf(stdout,"\nNesting: %d\n",nesting);
		fprintf(stdout,"\nVal: %d\n",result);

		EXPECT_EQ(3,result);
		

	


}

TEST(ListNestingTests, GetsNextTangentItem) {
	List* list = newList();
	_int64 item1 = 1;
	_int64 item2 = 2;
	_int64 item3 = 3;
	_int64 item4 = 4;
	
	newLastItem(list,(void*)item1);	
	newLastItem(list,(void*)item2);
	lastItemNesting(list, 1);
	newLastItem(list,(void*)item3);	
	lastItemNesting(list, 1);
	newLastItem(list,(void*)item4);
	lastItemNesting(list, 1);

	_int64 result = 0;
	_int64 nesting = 0;
	resetIndex(list);
	fprintf(stdout,"\nList items count: %d\n",list->itemsCount);

	
	while(list->index < list->itemsCount){
		result = (_int64)getNextTangentItem(list,1);	
		fprintf(stdout,"\nVal: %d\n",result);
		if (list->index == 2){									// List increments index implicitly following getNextItem call
			EXPECT_EQ(2,result);
		}
		if (list->index == 3){									// List increments index implicitly following getNextItem call
			EXPECT_EQ(3,result);
		}
		if (list->index == 4){									// List increments index implicitly following getNextItem call
			EXPECT_EQ(4,result);
		}

	}

		

	


}