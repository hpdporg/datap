#ifndef ASM_INCLUDES_H
#define ASM_INCLUDES_H



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


extern "C" {

	// Letters
	char* numAsLetters(_int64 num);

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
}


#endif