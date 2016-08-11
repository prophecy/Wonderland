/*
 * This source file is part of Wonderland, the C++ Cross-platform middleware for game
 *
 * For the latest information, see https://github.com/prophecy/Wonderland
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

#ifndef __MEMORY_H__
#define __MEMORY_H__

#define DEBUG_MEMORY

#include "Utility/Types.h"
#include "Utility/Singleton.h"
#include "MemoryHandle.h"

class Memory : public Singleton<Memory>
{
private:
	u32 _handleId;
	// This map is between code and handle
	std::map< u32, MemoryHandle<u32> > _codeHandleMap;
	// This is an additional map between pointer and handle
	std::map< u32*, MemoryHandle<u32> > _addressHandleMap;
public:

	template <typename T>
	MemoryHandle<T>* Alloc()
	{
		// Naive alloc mode1
		MemoryHandle<T>* handle	= new MemoryHandle<T>(); // <<< keep this in organized place
		T* ptr			= new T();
		handle->code	= _handleId;
		handle->ptr		= ptr;

		// Increment
		++_handleId;

		// Add to map
		// u32 is an address which is converted from T
		MemoryHandle<u32> hMap;
		hMap.code	= handle->code;
		hMap.ptr	= (u32*)handle->ptr;
		_codeHandleMap.insert(std::pair< u32, MemoryHandle<u32> >(hMap.code, hMap));

		// Create additional map for searching
		_addressHandleMap.insert(std::pair< u32*, MemoryHandle<u32> >(hMap.ptr, hMap));

		// Return handle
		return handle;
	}

	template <typename T>
	void Free(MemoryHandle<T>* handle)
	{	
		// Erase address handle
		_addressHandleMap.erase((u32*)handle->ptr);

		// Naive alloc mode
		delete handle->ptr;
		handle->ptr	= NULL;

		// Erase from map
		_codeHandleMap.erase(handle->code);
	}

	void FreeAll()
	{
		std::map< u32, MemoryHandle<u32> >::iterator	it	= _codeHandleMap.begin();

		while (it != _codeHandleMap.end())
		{	
			MemoryHandle<u32> handle	= (*it).second;

			// Naive alloc mode
			delete handle.ptr;
			handle.ptr	= NULL;

			// Erase from map
			_codeHandleMap.erase(it++);
		}

		// Clear all address handle
		_addressHandleMap.clear();
	}

	u64 GetMemoryCounter()
	{
		return _codeHandleMap.size();
	}

	template <typename T>
	MemoryHandle<T>* GetHandle(u64 address)
	{
		return (MemoryHandle<T>*)&_addressHandleMap[(u32*)address];
	}
};

#endif // __MEMORY_H__