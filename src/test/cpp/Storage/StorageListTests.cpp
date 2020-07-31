#include "datap.h"
#include "StorageListTests.h"
#include "StorageTest.cpp"



TEST_F(StorageTest, RetrievesList) {
	Record* record = newStorage();
	fprintf(stdout, "\nOutput: %d\n", (int)record);
	defineRecordPath(record, (char*)"TestCSV.csv", (char*)"..\\..\\..\\..\\src\\resources");
	//record->builtLocation = (char*)"..\\..\\..\\..\\src\\resources\\TestCSV.csv";
	fprintf(stdout, "\nOutput: %s\n", (record->builtLocation));
	record->allocFlags = STORAGE_ALLOC_LETTERS | STORAGE_ALLOC_LIST;
	record->jDelimiter = (char*)"\r\n";
	retrieve(record);
	fprintf(stdout, "\nHandle: %d\n", (record->handle));
	EXPECT_TRUE(record->handle != 0);
	fprintf(stdout, "\nSize: %d\n", (record->allocSize));
	EXPECT_TRUE(record->allocSize != 0);
	fprintf(stdout, "\nList Size: %d\n", ((List*)record->allocAddr)->itemsCount);
	EXPECT_EQ(3, ((List*)record->allocAddr)->itemsCount);

	List* list = (List*)record->allocAddr;
	resetIndex(list);
	while (list->index < list->itemsCount) {
		char* item = (char*)getNextItem(list);
		fprintf(stdout, "\nNextItem: %s.\n", item);
	}

}


TEST_F(StorageTest, StoresList) {


	List* vals1 = newList();
	char* val1 = (char*)"RV8U";
	char* val2 = (char*)"888d8U";


	newLastItem(vals1, val1);
	newLastItem(vals1, val2);




	Record* record = newStorage();
	record->allocFlags = STORAGE_ALLOC_LETTERS | STORAGE_ALLOC_LIST;
	record->jDelimiter = (char*)"\r\n";


	defineRecordPath(record, (char*)"TestCSVList3.txt", (char*)".\\");
	storeList(record, vals1);

	fprintf(stdout, "\nSize: %d\n", (record->allocSize));
	EXPECT_EQ(14,record->allocSize);


	fprintf(stdout, "Written\n");
	//Sleep(100000);
	removeRecord(record);


}