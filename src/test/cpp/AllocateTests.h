#ifndef ALLOCATE_TESTS_H
#define ALLOCATE_TESTS_H

#include "gtest\gtest.h"



extern "C" {
	extern void* linearAllocate(int size);
}


#endif