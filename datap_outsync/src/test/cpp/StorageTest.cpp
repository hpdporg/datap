#include "AsmIncludes.h"
#include "StorageTests.h"


class StorageTest : public ::testing::Test {
 protected:
  void SetUp() override {
    Record* record = newStorage();
	defineRecordPath(record, (char*)"TestCSV.csv", (char*)"..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nRestoring test data: %s\n", (record->builtLocation));	
	restoreLetters(record,(char*)"Header1,Header2,Header3,Header4\r\nVal1_1,Val2_1,Val3_1,Val4_1\r\nVal1_2,Val2_2,Val3_2,Val4_2");
	
	Record* record2 = newStorage();
	defineRecordPath(record2, (char*)"TestCSV_Backup.csv", (char*)"..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nRestoring test data: %s\n", (record2->builtLocation));		
	restoreLetters(record2,(char*)"Header1,Header2,Header3,Header4\r\nVal1_1,Val2_1,Val3_1,Val4_1\r\nVal1_2,Val2_2,Val3_2,Val4_2");
	
	Record* record3 = newStorage();
	defineRecordPath(record3, (char*)"TestCSV_Modify.csv", (char*)"..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nRestoring test data: %s\n", (record3->builtLocation));	
	restoreLetters(record3,(char*)"Header1,Header2,Header3,Header4\r\nVal1_1,Val2_1,Val3_1,Val4_1\r\nVal1_2,Val2_2,Val3_2,Val4_2");



  }

   void TearDown() override {
	  Record* record = newStorage();
	defineRecordPath(record, (char*)"TestCSV.csv", (char*)"..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nRestoring test data: %s\n", (record->builtLocation));	
	restoreLetters(record,(char*)"Header1,Header2,Header3,Header4\r\nVal1_1,Val2_1,Val3_1,Val4_1\r\nVal1_2,Val2_2,Val3_2,Val4_2");

	Record* record2 = newStorage();
	defineRecordPath(record2, (char*)"TestCSV_Backup.csv", (char*)"..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nRestoring test data: %s\n", (record2->builtLocation));	
	restoreLetters(record2,(char*)"Header1,Header2,Header3,Header4\r\nVal1_1,Val2_1,Val3_1,Val4_1\r\nVal1_2,Val2_2,Val3_2,Val4_2");
	
	Record* record3 = newStorage();
	defineRecordPath(record3, (char*)"TestCSV_Modify.csv", (char*)"..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nRestoring test data: %s\n", (record3->builtLocation));	
	restoreLetters(record3,(char*)"Header1,Header2,Header3,Header4\r\nVal1_1,Val2_1,Val3_1,Val4_1\r\nVal1_2,Val2_2,Val3_2,Val4_2");


   }


};