#include "AsmIncludes.h"
#include "StorageTests.h"

TEST(StorageTest, ReturnsRecord) {
	Record* record = newStorage();
	fprintf(stdout, "\nOutput: %d\n", (int)record);
	EXPECT_TRUE((record !=NULL));
}

TEST(StorageTest, BuildsRecordPath) {
	Record* record = newStorage();
	fprintf(stdout, "\nOutput: %d\n", (int)record);
	defineRecordPath(record,"TestCSV.csv","..\\..\\..\\src\\resources");
	fprintf(stdout, "\nOutput: %s\n", (record->builtLocation));
	EXPECT_STREQ("..\\..\\..\\src\\resources\\TestCSV.csv",(record->builtLocation));
	
}

TEST(StorageTest, RetrievesRecordFromFilesystem) {
	Record* record = newStorage();
	fprintf(stdout, "\nOutput: %d\n", (int)record);
	defineRecordPath(record,"TestCSV.csv","..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nOutput: %s\n", (record->builtLocation));	
	retrieve(record);
	fprintf(stdout, "\nHandle: %d\n", (record->handle));	
	EXPECT_TRUE(record->handle!= 0);
	fprintf(stdout, "\nSize: %d\n", (record->allocSize));	
	EXPECT_TRUE(record->allocSize!= 0);
}


