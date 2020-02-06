#include "datap.h"
#include <stdio.h>
#include "Examples.h"


void runAllocateExample(){
	
	fprintf(stdout, "Allocate example\n");
	fprintf(stdout, "================\n");
	void* memAddress = linearAllocate(4);
	fprintf(stdout, "Allocated a block of memory, 4 bytes in length. Memory address(handle): %d\n", (_int64)memAddress);
	_int64 val = 222;
	*((_int64*)memAddress) = val;
	fprintf(stdout, "Allocated block stores a 64-bit val of 222: %d\n", (_int64)(*(_int64*)memAddress));
	fprintf(stdout, "You can store any value of any length just like heapalloc or malloc. Returns void* which can be cast.\n");
	fprintf(stdout, "================\n");
}