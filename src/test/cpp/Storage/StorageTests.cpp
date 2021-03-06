#include "datap.h"
#include "StorageTests.h"
#include "StorageTest.cpp"



TEST_F(StorageTest, ReturnsRecord) {
	Record* record = newStorage();
	fprintf(stdout, "\nOutput: %d\n", (int)record);
	EXPECT_TRUE((record !=NULL));
}

TEST_F(StorageTest, BuildsRecordPath) {
	Record* record = newStorage();
	fprintf(stdout, "\nOutput: %d\n", (int)record);
	defineRecordPath(record,(char*)"TestCSV.csv", (char*)"..\\..\\..\\src\\resources");
	fprintf(stdout, "\nOutput: %s\n", (record->builtLocation));
	EXPECT_STREQ("..\\..\\..\\src\\resources\\TestCSV.csv",(record->builtLocation));
	
}

TEST_F(StorageTest, RetrievesRecordFromFilesystem) {
	Record* record = newStorage();
	fprintf(stdout, "\nOutput: %d\n", (int)record);
	defineRecordPath(record, (char*)"TestCSV.csv", (char*)"..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nOutput: %s\n", (record->builtLocation));	
	retrieve(record);
	fprintf(stdout, "\nHandle: %d\n", (record->handle));	
	EXPECT_TRUE(record->handle!= 0);
	fprintf(stdout, "\nSize: %d\n", (record->allocSize));	
	EXPECT_TRUE(record->allocSize!= 0);
}


TEST_F(StorageTest, LettersAppended) {
	Record* record = newStorage();
	fprintf(stdout, "\nOutput: %d\n", (int)record);
	defineRecordPath(record, (char*)"TestCSV.csv", (char*)"..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nOutput: %s\n", (record->builtLocation));	
	storeLetters(record, (char*)"ABC8291");
	fprintf(stdout, "\nHandle: %d\n", (record->handle));	
	EXPECT_TRUE(record->handle!= 0);
	fprintf(stdout, "\nSize: %d\n", (record->allocSize));	
	EXPECT_TRUE(record->allocSize!= 0);
}

TEST_F(StorageTest, LettersAppendedWithoutDefiningPathSeparately) {
	Record* record = newStorage();
	fprintf(stdout, "\nOutput: %d\n", (int)record);
	record->builtLocation = (char*)"..\\..\\..\\..\\src\\resources\\TestCSV.csv";
	fprintf(stdout, "\nOutput: %s\n", (record->builtLocation));
	storeLetters(record, (char*)"ABC8291");
	fprintf(stdout, "\nHandle: %d\n", (record->handle));
	EXPECT_TRUE(record->handle != 0);
	fprintf(stdout, "\nSize: %d\n", (record->allocSize));
	EXPECT_TRUE(record->allocSize != 0);
}

TEST_F(StorageTest, LettersReplaced) {
	Record* backupRecord = newStorage();
	fprintf(stdout, "\nOutput: %d\n", (int)backupRecord);
	defineRecordPath(backupRecord, (char*)"TestCSV_Backup.csv", (char*)"..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nOutput: %s\n", (backupRecord->builtLocation));	
	fprintf(stdout,"\nRetrieve: %d \n",retrieve(backupRecord));
	fprintf(stdout, "\nHandle: %d\n", (backupRecord->handle));	
	EXPECT_TRUE(backupRecord->handle!= 0);
	fprintf(stdout, "\nBackup Size: %d\n", (backupRecord->allocSize));	
	EXPECT_TRUE(backupRecord->allocSize!= 0);

	Record* record = newStorage();
	fprintf(stdout, "\nOutput: %d\n", (int)record);
	defineRecordPath(record, (char*)"TestCSV_Modify.csv", (char*)"..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nOutput: %s\n", (record->builtLocation));	
	restoreLetters(record,(char*)backupRecord->allocAddr);
	fprintf(stdout,"\nBackup record contents: %s\n",(char*)backupRecord->allocAddr);
	fprintf(stdout, "\nHandle: %d\n", (record->handle));	
	EXPECT_TRUE(record->handle!= 0);
	fprintf(stdout, "\nSize: %d\n", (record->allocSize));	
	EXPECT_TRUE(record->allocSize!= 0);
}

TEST_F(StorageTest, RetrievesRecordNames) {
	Record* recordDir = newStorage();
	recordDir->location = (char*)"..\\..\\..\\..\\src\\resources";
	//fprintf(stdout, "\nABC %d\n",sizeof(LPWIN32_FIND_DATAA));
	//w32FindData
//		FindNextFileA();

	fprintf(stdout,"\nRetrieving: \n");
	List* recordNames = retrieveRecordNames(recordDir);

	fprintf(stdout,"\nRecords retrieved: %d\n",recordNames->itemsCount);
	while (recordNames->index < recordNames->itemsCount){
		char* nextRecord = (char*)getNextItem(recordNames);
		fprintf(stdout,"\nNext record: %s\n",nextRecord);
		if (recordNames->index == 1) {	// getNextItem increments index implicitly following call
			EXPECT_STREQ("resources_backup", nextRecord);
		}
		if (recordNames->index == 2) {	// getNextItem increments index implicitly following call
			EXPECT_STREQ("TestCSV.csv", nextRecord);
		}
		if (recordNames->index == 3) {	// getNextItem increments index implicitly following call
			EXPECT_STREQ("TestCSV_Backup.csv", nextRecord);
		}
		if (recordNames->index == 4) {	// getNextItem increments index implicitly following call
			EXPECT_STREQ("TestCSV_Modify.csv", nextRecord);
		}
		
	}
	EXPECT_EQ(4, recordNames->itemsCount);
	
	
}

TEST_F(StorageTest, StoresDebugNum) {
	debugNum(819891);

	Record* record = newStorage();

	defineRecordPath(record, (char*)"DebugRec.txt", (char*)".\\");
	retrieve(record);
	EXPECT_TRUE(record->handle!= 0);
	fprintf(stdout, "\nContents: %s\n", (record->allocAddr));	
	EXPECT_STREQ("819891",(char*)record->allocAddr);
	removeRecord(record);
	
}

TEST_F(StorageTest, StoresDebugLetters) {
	const char* letters = "dfalj2ij";
	debugLetters((char*)letters);

	Record* record = newStorage();

	defineRecordPath(record, (char*)"DebugRec.txt", (char*)".\\");
	retrieve(record);
	EXPECT_TRUE(record->handle!= 0);
	fprintf(stdout, "\nContents: %s\n", (char*)(record->allocAddr));	
	char* contents = (char*)record->allocAddr;
	EXPECT_STREQ("dfalj2ij",(char*)contents);
	removeRecord(record);
	
}

TEST_F(StorageTest, StoresDebugNumMsg) {
	debugNumMsg(819891);

	Record* record = newStorage();

	defineRecordPath(record, (char*)"DebugRec.txt", (char*)".\\");
	retrieve(record);
	EXPECT_TRUE(record->handle != 0);
	fprintf(stdout, "\nContents: %s\n", (record->allocAddr));
	EXPECT_STREQ("819891\r\n", (char*)record->allocAddr);
	removeRecord(record);

}

TEST_F(StorageTest, StoresDebugLettersMsg) {
	const char* letters = "dfalj2ij";
	debugLettersMsg((char*)letters);

	Record* record = newStorage();

	defineRecordPath(record, (char*)"DebugRec.txt", (char*)".\\");
	retrieve(record);
	EXPECT_TRUE(record->handle != 0);
	fprintf(stdout, "\nContents: %s\n", (char*)(record->allocAddr));
	char* contents = (char*)record->allocAddr;
	EXPECT_STREQ("dfalj2ij\r\n", (char*)contents);
	removeRecord(record);

}


//Store List contents? As CSV?
//Insert in File after match?
//Replace sequences with other letters
//Find sequences, put offsets in list?