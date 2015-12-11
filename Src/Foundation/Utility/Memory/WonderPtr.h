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

#ifndef __WONDER_PTR_H__
#define __WONDER_PTR_H__

#include "MemoryHandle.h"
#include "Utility/Utility.h"
#include "Utility/Types.h"

template <typename T>
class WonderPtr
{
private:
	MemoryHandle<T>* handle; // The handle can be set by operator overloading "="

public:
	WonderPtr<T>()
	{
		// Set handle to NULL
		s32 data;
		data = 0x0;
		memcpy((u8*)this, (u8*)&data, sizeof WonderPtr);
	}

	WonderPtr<T>(MemoryHandle<T>* handle)
	{
		this->handle = handle;
	}

	template <typename From>
	WonderPtr<T>(From& from)
	{
		memcpy((u8*)this, (u8*)&from, sizeof WonderPtr);
	}

	void Alloc()
	{
		handle = ALLOC(T);
	}

	void Free()
	{
		FREE(handle);
	}

	bool IsValid()
	{
		return this->handle != NULL;
	}

	T* Ptr()
	{
		return handle->ptr;
	}

	template <typename To>
	WonderPtr<To> To()
	{
		WonderPtr<To> to;
		to = handle;
		return to;
	}

	// --------------------------------------------------------------------------
	// Overloaded operators

	// Access to handle
	T* operator->()
	{
		return handle->ptr;
	}

	template <typename From>
	WonderPtr<T> operator= (From& from)
	{
		memcpy((u8*)this, (u8*)&from, sizeof WonderPtr);
		return *((WonderPtr<T>*)&from);
	}

	template <typename From>
	inline bool operator==(const From& from)
	{
		WonderPtr<T> ptr;
		ptr = from;
		return (s32)this->handle == (s32)ptr.handle;
	}

	template <typename From>
	inline bool operator!=(const From& from)	
	{ 
		WonderPtr<T> ptr;
		ptr = from;
		return (s32)this->handle != (s32)ptr.handle;
	}

};

#endif // __WONDER_PTR_H__