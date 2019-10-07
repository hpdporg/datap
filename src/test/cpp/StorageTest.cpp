#include "AsmIncludes.h"
#include "StorageTests.h"


class StorageTest : public ::testing::Test {
 protected:
  void SetUp() override {
    Record* record = newStorage();
	fprintf(stdout, "\Restoring test data: %d\n", (int)record);
	defineRecordPath(record,"TestCSV.csv","..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nLoc: %s\n", (record->builtLocation));	
	restoreLetters(record,(char*)"Header1,Header2,Header3,Header4\r\nVal1_1,Val2_1,Val3_1,Val4_1\r\nVal1_2,Val2_2,Val3_2,Val4_2");
	fprintf(stdout,"\nBackup record contents: %s\n",(char*)record->allocAddr);
	fprintf(stdout, "\nHandle: %d\n", (record->handle));	
	fprintf(stdout, "\nSize: %d\n", (record->allocSize));	

	Record* record2 = newStorage();
	fprintf(stdout, "\Restoring test data: %d\n", (int)record2);
	defineRecordPath(record2,"TestCSV_Backup.csv","..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nLoc: %s\n", (record2->builtLocation));	
	restoreLetters(record2,(char*)"Header1,Header2,Header3,Header4\r\nVal1_1,Val2_1,Val3_1,Val4_1\r\nVal1_2,Val2_2,Val3_2,Val4_2");
	fprintf(stdout,"\nBackup record2 contents: %s\n",(char*)record2->allocAddr);
	fprintf(stdout, "\nHandle: %d\n", (record2->handle));	
	fprintf(stdout, "\nSize: %d\n", (record2->allocSize));	

	Record* record3 = newStorage();
	fprintf(stdout, "\Restoring test data: %d\n", (int)record3);
	defineRecordPath(record3,"TestCSV_Modify.csv","..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nLoc: %s\n", (record3->builtLocation));	
	restoreLetters(record3,(char*)"Header1,Header2,Header3,Header4\r\nVal1_1,Val2_1,Val3_1,Val4_1\r\nVal1_2,Val2_2,Val3_2,Val4_2");
	fprintf(stdout,"\nBackup record3 contents: %s\n",(char*)record3->allocAddr);
	fprintf(stdout, "\nHandle: %d\n", (record3->handle));	
	fprintf(stdout, "\nSize: %d\n", (record3->allocSize));	



  }

   void TearDown() override {
	  Record* record = newStorage();
	fprintf(stdout, "\Restoring test data: %d\n", (int)record);
	defineRecordPath(record,"TestCSV.csv","..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nLoc: %s\n", (record->builtLocation));	
	restoreLetters(record,(char*)"Header1,Header2,Header3,Header4\r\nVal1_1,Val2_1,Val3_1,Val4_1\r\nVal1_2,Val2_2,Val3_2,Val4_2");
	fprintf(stdout,"\nBackup record contents: %s\n",(char*)record->allocAddr);
	fprintf(stdout, "\nHandle: %d\n", (record->handle));	
	fprintf(stdout, "\nSize: %d\n", (record->allocSize));	

	Record* record2 = newStorage();
	fprintf(stdout, "\Restoring test data: %d\n", (int)record2);
	defineRecordPath(record2,"TestCSV_Backup.csv","..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nLoc: %s\n", (record2->builtLocation));	
	restoreLetters(record2,(char*)"Header1,Header2,Header3,Header4\r\nVal1_1,Val2_1,Val3_1,Val4_1\r\nVal1_2,Val2_2,Val3_2,Val4_2");
	fprintf(stdout,"\nBackup record2 contents: %s\n",(char*)record2->allocAddr);
	fprintf(stdout, "\nHandle: %d\n", (record2->handle));	
	fprintf(stdout, "\nSize: %d\n", (record2->allocSize));	

	Record* record3 = newStorage();
	fprintf(stdout, "\Restoring test data: %d\n", (int)record3);
	defineRecordPath(record3,"TestCSV_Modify.csv","..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nLoc: %s\n", (record3->builtLocation));	
	restoreLetters(record3,(char*)"Header1,Header2,Header3,Header4\r\nVal1_1,Val2_1,Val3_1,Val4_1\r\nVal1_2,Val2_2,Val3_2,Val4_2");
	fprintf(stdout,"\nBackup record3 contents: %s\n",(char*)record3->allocAddr);
	fprintf(stdout, "\nHandle: %d\n", (record3->handle));	
	fprintf(stdout, "\nSize: %d\n", (record3->allocSize));	

   }


};