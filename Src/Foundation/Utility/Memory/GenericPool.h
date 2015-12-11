/*
 * This source file is part of Pillar, the C++ Cross-platform middleware for game
 *
 * For the latest information, see https://github.com/prophecy/Pillar
 *
 * The MIT License (MIT)
 * Copyright (c) 2015 Adawat Chanchua
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef __GENERIC_POOL_H__
#define __GENERIC_POOL_H__

#include "PoolLib.h"

class GenericPool
{
public:
	enum ReportFlags
	{
		PRINT_CONSOLE	= 0,
		PRINT_LOG_FILE,
	};

	void* operator new(size_t size, int sliceSize, int sliceCount);
	void operator delete(void* pObj);
	void operator delete(void* pObj, int param1, int param2)	{}

	GenericPool();
	~GenericPool();

	void* Request(size_t size);
	void* Return(void* ptr);
	void DeleteAllData();

	int GetTotalSize();
	int GetSliceCount();
	int GetSliceSize();
	void* GetPoolPtr();

	void PrintReport(ReportFlags flag);
private:
	void _DeleteAllData();

	int _SearchFreeSlice(size_t size);
	int _CalcNeededSlice(size_t size);
	int _SetFlagToVariableSlice(void* pObj);
	void _ClearSliceData(int firstId, int sliceCount);

	enum
	{
		// any of incompletion
		// 1. no available slice in _SearchFreeSlice();
		INCOMPLETE		= -1,
	};

	// static variable
	static void* s_pPool;
	static int s_sliceCount;
	static int s_sliceSize;
	static int s_sliceArraySize;
	static int s_poolSize;

	/*--------------------------------------------
	Memory order
		1. GenericPool	<< class >>
		2. _slices		<< dynamic array >>
		3. _isPointerSlice	<< dynamic array >>
		4. Pool			<< my pool is here!! >>
		5. _wastMems	<< dynamic array >>
	--------------------------------------------*/

	void* _pool_ptr;	// pool data position
	int _sliceSize;		// size of each slice
	int _sliceCount;	// number of slices

	// pool flag
	bool _hasInit;
	bool* _slices_ptr;
	bool* _isPointerSlice_ptr;

#ifdef MEM_POOL_DEBUG
private:
	enum
	{
		DEBUG_ARRAY_SIZE	= 512,
	};
	int* _wastMems_ptr;

	bool _slices_debug[DEBUG_ARRAY_SIZE];
	bool _isPointerSlice_debug[DEBUG_ARRAY_SIZE];
	int _wastMems_debug[DEBUG_ARRAY_SIZE];

	// determine the last memory we allocated + 1
	// so the [last allocated memory] = nextSectionData - 1;
	static void* s_nextSectionData;
	void* _nextSectionData;
#endif // #ifdef MEM_POOL_DEBUG
};

#endif // #ifndef __GENERIC_POOL_H__