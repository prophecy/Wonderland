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

#include <iostream>
using namespace std;

//--------------------------------------------
#include "GenericPool.h"

//--------------------------------------------
void* GenericPool::s_pPool	= 0;
int GenericPool::s_sliceCount	= 0;
int GenericPool::s_sliceSize	= 0;
int GenericPool::s_sliceArraySize	= 0;
int GenericPool::s_poolSize	= 0;

#ifdef MEM_POOL_DEBUG
void* GenericPool::s_nextSectionData	= 0;
#endif // #ifdef MEM_POOL_DEBUG
//--------------------------------------------

//--------------------------------------------
void* GenericPool::operator new(size_t size, int sliceSize, int sliceCount)
{
	// calculate the size which is must be allocate
	addr classSize		= size;
	s_sliceArraySize	= sizeof(bool) * sliceCount;
	s_poolSize			= sliceSize * sliceCount;

	int totalSize	= classSize + s_sliceArraySize
		+ s_sliceArraySize + s_poolSize;

#ifdef MEM_POOL_DEBUG
	int wastMemsSize	= sizeof(addr) * sliceCount;
	totalSize += wastMemsSize;
#endif // #ifdef MEM_POOL_DEBUG
	
	// allocate pool
	s_sliceCount	= sliceCount;
	s_sliceSize		= sliceSize;
	s_pPool			= malloc(totalSize);

#ifdef MEM_POOL_DEBUG
	s_nextSectionData	= (void*)( (addr)s_pPool + totalSize );
#endif // #ifdef MEM_POOL_DEBUG

	// return allocated pointer
	return s_pPool;
}
//--------------------------------------------
void GenericPool::operator delete(void* pObj)
{
	free(pObj);
}
//--------------------------------------------
GenericPool::GenericPool()
{
	// set variables from class scope (static) to object scope
	_sliceCount		= s_sliceCount;
	_sliceSize		= s_sliceSize;
	_hasInit		= false;

	int slicesArraySize			= s_sliceArraySize;
	int isPointerSliceArraySize	= s_sliceArraySize;
	int poolSize				= s_poolSize;

	// set pointer offsets
	_slices_ptr	= (bool*)(this+1);
	addr memPos	= (addr)_slices_ptr;
	memPos += slicesArraySize;
	_isPointerSlice_ptr	= (bool*)(memPos);
	memPos		= (addr)_isPointerSlice_ptr;
	memPos += isPointerSliceArraySize;
	_pool_ptr	= (void*)memPos;

#ifdef MEM_POOL_DEBUG
	// set pointer of debug offsets
	memPos	= (addr)_pool_ptr;
	memPos += poolSize;
	_wastMems_ptr	= (int*)memPos;

	for (int i=0; i<_sliceCount; ++i)
	{
		// initial value
		_wastMems_ptr[i]	= 0;
	}

	// because we use dynamic arrays to be used in the class ^
	// and dynamic arrays lack of compiler's debug features ^
	// so, we use static array to debug it...
	for (int i=0; i<_sliceCount; ++i)
	{
		_slices_debug[i]		= _slices_ptr[i];
		_isPointerSlice_debug[i]= _isPointerSlice_ptr[i];
		_wastMems_debug[i]		= _wastMems_ptr[i];
	}

	// assign value to _nextSectionData (the address of memory after the last allocated ones)
	// we need to copy value of pointer position so
	addr nextSectionDataInt	= (addr)s_nextSectionData;
	_nextSectionData	= (void*)nextSectionDataInt;

	addr lastPointer	= (addr)(&_wastMems_ptr[_sliceCount-1]);
	addr lastPosition	= lastPointer + (sizeof(addr) - 1);

	if (lastPosition >= (addr)_nextSectionData)
	{
		cout << "Code Bugs!! memory outbound" << endl;
	}
#endif
	_DeleteAllData();
}
//--------------------------------------------
GenericPool::~GenericPool()
{
	// does nothing
}
//--------------------------------------------
void* GenericPool::Request(size_t size)
{
	void* ptr	= NULL;
	
	int sliceNeeded		= _CalcNeededSlice(size);
	int sliceId			= _SearchFreeSlice(size);

	if (sliceId == INCOMPLETE)
	{
		ptr	= NULL;
		return NULL;
	}

	// set flags
	// flag to determine where is the pointer of each data
	_isPointerSlice_ptr[sliceId]	= true;
#ifdef MEM_POOL_DEBUG
	_isPointerSlice_debug[sliceId]	= _isPointerSlice_ptr[sliceId];
#endif
	for (int i=0; i<sliceNeeded; ++i)
	{
		// flag to determine where are used data
		_slices_ptr[sliceId+i]	= false;
#ifdef MEM_POOL_DEBUG
		_slices_debug[sliceId+i]= _slices_ptr[sliceId+i];
#endif
	}

	// calculate pointer position
	addr offsetMemPos	= (addr)_pool_ptr;
	addr ptrMemPos		= offsetMemPos + (sliceId * _sliceSize);

	// set memory position to the pointer
	ptr	= (void*)ptrMemPos;

	// (debug) calculate wasted-memory in pool
#ifdef MEM_POOL_DEBUG
	for (int i=0; i<sliceNeeded; ++i)
	{
		int index	= sliceId+i;
		_wastMems_ptr[index]	= 0; // debugging for pool performance purpose
		_wastMems_debug[index]	= _wastMems_ptr[index]; // debugging for compiler purpose

		if (i == (sliceNeeded-1)) // last slice of the allocation
		{
			int totalSliceSpaces	= sliceNeeded * _sliceSize;
			_wastMems_ptr[index]	= totalSliceSpaces - size;
			_wastMems_debug[index]	= _wastMems_ptr[index];
		}
	}
#endif // #ifdef MEM_POOL_DEBUG

	// return the successful value
	return ptr;
}
//--------------------------------------------
void* GenericPool::Return(void* ptr)
{
	addr ptrMemPos		= (addr)ptr;
	addr offsetMemPos	= (addr)_pool_ptr;

	bool hasFound			= false;
	int allocatedSliceId	= INCOMPLETE;

	// search for the request slice
	for (int i=0; i<_sliceCount; ++i)
	{
		int currentSliceMemPos	= offsetMemPos + (i*_sliceSize);

		if (offsetMemPos == currentSliceMemPos)
		{
			allocatedSliceId	= i;
			hasFound			= true;
			_isPointerSlice_ptr[i]	= false;
#ifdef MEM_POOL_DEBUG
			_isPointerSlice_debug[i]= _isPointerSlice_ptr[i];
#endif
			break;
		}
	}

	// if not found return the same pointer
	if (hasFound == false)
		return ptr;

	// calculate allocated memory for this variable
	int sliceNeeded	= 0;
	for (int i=allocatedSliceId; i<_sliceCount; ++i)
	{
		if (_slices_ptr[i] == false)
		{
			_slices_ptr[i]	= true;
#ifdef MEM_POOL_DEBUG
			_slices_debug[i]= _slices_ptr[i];
			_wastMems_ptr[i]	= 0;
			_wastMems_debug[i]	= _wastMems_ptr[i];
#endif
			sliceNeeded++;
		}
		else
		{
			break;
		}
	}

	// clear slice data
	ptr	= NULL;
	_ClearSliceData(allocatedSliceId, sliceNeeded);
	return ptr;
}
//--------------------------------------------
void GenericPool::DeleteAllData()
{
	_DeleteAllData();
}
//--------------------------------------------
int GenericPool::GetTotalSize()
{
	// calculate the size which is must be allocate
	int classSize		= sizeof(this);
	int slicesArraySize	= sizeof(bool) * _sliceCount;
	int isPointerSliceArraySize	= sizeof(bool) * _sliceCount;
	int poolSize		= _sliceCount * _sliceSize;

	int totalSize	= classSize + slicesArraySize
		+ isPointerSliceArraySize + poolSize;

#ifdef MEM_POOL_DEBUG
	totalSize += sizeof(addr) * _sliceCount; // _wastMems_ptr offset
#endif // #ifdef MEM_POOL_DEBUG

	return totalSize;
}
//--------------------------------------------
int GenericPool::GetSliceCount()
{
	return _sliceCount;
}
//--------------------------------------------
int GenericPool::GetSliceSize()
{
	return _sliceSize;
}
//--------------------------------------------
void* GenericPool::GetPoolPtr()
{
	return _pool_ptr;
}
//--------------------------------------------
void GenericPool::PrintReport(ReportFlags flag)
{
#ifdef MEM_POOL_DEBUG
	int totalMemWested	= 0;
	int totalMemFreed	= 0;

	for (int i=0; i<_sliceCount; ++i)
	{
		// Calc wast memory
		int wastedMem	= _wastMems_ptr[i];
		totalMemWested += wastedMem;

		if (wastedMem)
		{
			cout << "Memory @ [" << i << "]" << "is wasted by "
				<< wastedMem << "bytes" << endl;
		}

		// Calc free memory
		if (_slices_ptr[i] == true)
			totalMemFreed++;
	}
#endif // MEM_POOL_DEBUG

	switch(flag)
	{
	case PRINT_CONSOLE:
#ifdef MEM_POOL_DEBUG
		cout << "Total wested memory: " << totalMemWested << "bytes" << endl;
		cout << "Total slice: " << _sliceCount << endl;
		cout << "Free slice: " << totalMemFreed << endl;
#endif // MEM_POOL_DEBUG
		break;
	case PRINT_LOG_FILE:
		{

		}break;
	default:
		{
			// just default, this case will never be proceed theoretically
		}break;
	}
}
//--------------------------------------------
void GenericPool::_DeleteAllData()
{
	_ClearSliceData(0, (_sliceCount));

	// clear all flag in pool
	for (int i=0; i<_sliceCount; ++i)
	{
		_slices_ptr[i]			= true;
		_isPointerSlice_ptr[i]	= false;
#ifdef MEM_POOL_DEBUG
		_wastMems_ptr[i]	= 0;

		_slices_debug[i]			= _slices_ptr[i];
		_isPointerSlice_debug[i]	= _isPointerSlice_ptr[i];
		_wastMems_debug[i]			= _wastMems_ptr[i];
#endif
	}
}
//--------------------------------------------
int GenericPool::_SearchFreeSlice(size_t size)
{
	int sliceNeeded	= _CalcNeededSlice(size);
	bool hasFound	= false;
	int sliceId		= INCOMPLETE;

	for (int i=0; i<_sliceCount; ++i)
	{
		if (_slices_ptr[i] == true)
		{
			int availableSlice	= 0;
			for (int j=i; j<_sliceCount; ++j)
			{
				if (_slices_ptr[i] == true)
					availableSlice++;
				if (availableSlice >= sliceNeeded)
				{
					hasFound	= true;
					sliceId	= i;
					break;
				}
			}
		}
		if (hasFound)
			break;
	}
	return sliceId;
}
//--------------------------------------------
addr GenericPool::_CalcNeededSlice(size_t size)
{
	addr sliceCount	= size / _sliceSize;
	if ((size%_sliceSize) > 0)
		sliceCount++;
	return sliceCount;
};
//--------------------------------------------
void GenericPool::_ClearSliceData(int firstId, int sliceCount)
{
	// calculate pointer position
	addr offsetMemPos	= (addr)_pool_ptr;
	addr ptrFirstMemPos	= offsetMemPos + (firstId*_sliceSize);
	addr ptrLastMemPos	= ptrFirstMemPos + (sliceCount*_sliceSize);

	// set first memory position to the pointer
	void* ptr	= (void*)ptrFirstMemPos;

	// KAK data destroyer
	int dataSize	= sizeof(addr);

	while ( (((addr)ptr)+dataSize) < ptrLastMemPos)
	{
		addr* value	= (addr*)ptr;
		*value	&= 0x0;
		ptr	= (void*)(((addr)ptr)+1);
	}
}
//--------------------------------------------