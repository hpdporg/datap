#include "datap.h"
#include "StorageFlowTests.h"
#include "StorageTest.cpp"



TEST_F(StorageTest, RetrievesFlow) {
	Record* record = newStorage();
	fprintf(stdout, "\nOutput: %d\n", (int)record);
	defineRecordPath(record, (char*)"TestCSV.csv", (char*)"..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nOutput: %s\n", (record->builtLocation));
	record->allocFlags = STORAGE_ALLOC_LETTERS | STORAGE_ALLOC_FLOW;
	record->jDelimiter = (char*)"\r\n";
	record->iDelimiter = (char*)",";
	retrieve(record);
	fprintf(stdout, "\nHandle: %d\n", (record->handle));
	EXPECT_TRUE(record->handle != 0);
	fprintf(stdout, "\nSize: %d\n", (record->allocSize));
	EXPECT_TRUE(record->allocSize != 0);
	fprintf(stdout, "\nFlow length: %d\n", ((Flow*)record->allocAddr)->length);
	EXPECT_EQ(3,((Flow*)record->allocAddr)->length);
	fprintf(stdout, "\nFlow width: %d\n", ((Flow*)record->allocAddr)->width);
	EXPECT_EQ(4, ((Flow*)record->allocAddr)->width);

	Flow* flow = (Flow*)record->allocAddr;
	resetFlowIJ(flow);
	while (flow->j < flow->length) {
		char* item =(char*)getNextFlowItem(flow);
		fprintf(stdout, "\nNextItem: %s.\n", item);
	}

}


