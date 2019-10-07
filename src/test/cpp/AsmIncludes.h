#ifndef ASM_INCLUDES_H
#define ASM_INCLUDES_H

#include <Windows.h>


typedef struct ListItem {
	void* item;
	void* previous;
	_int64 nesting;
	void* next;
} ListItem;

typedef struct ItemMatch {
	void* item;
	_int64 index;
	_int64 nesting;
} ItemMatch;

typedef struct List {
	void* firstItem;
	_int64	listSize;
	_int64	itemsCount;
	_int64	index;
	void* indexItem;
	_int64	indexedItemIndex;
	void* itemMatch;
} List;

typedef struct Record {
	void* allocAddr;
	_int64	allocSize;
	char* name;
	char* location;
	char* builtLocation;
	HANDLE handle;
} Record;

typedef struct Match {
	_int64	flags;
	_int64	transformFlags;
	List* containsRangeList;
	_int64 subRangeStartIndex;
	_int64 subRangeEndIndex;
} Match;


///extern char* pathSepLettersChar;
extern "C" {

	// Letters
	char* numAsLetters(_int64 num);
	char* appendLetters(char* letters1, char* appendingLetters);
	_int64 letterLength(char* letters);

	// Allocate
	void* linearAllocate(int size);

	// List
	List* newList();
	void newLastItem(List* list, void* item);
	void* getNextItem(List* list);
	void* getNextItemNesting(List* list);
	void* nextItemNesting(List* list, _int64 nesting);
	void resetIndex(List* list);
	void* newNextItem(List* list, void* item);
	void* getPriorItem(List* list);
	void* getNextItemMatch(List* list, void* itemMatch);
	void* getNextItemMatchComp(List* list, void* itemMatch, _int64 comp);

	//Storage
	Record* newStorage();
	Record* defineRecordPath(Record* record, char* name, char* location);
	Record* retrieve(Record* record);
	Record* storeLetters(Record* record, char* letters);
	Record* restoreLetters(Record* record, char* letters);

	//Match
	Match* newMatch();
}


#endif