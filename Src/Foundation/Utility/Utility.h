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

#ifndef	__UTILITY_H__
#define __UTILITY_H__

// Math
#include <cml/cml.h>

typedef cml::vector2i	vector2s;
typedef cml::vector2i	point2s;
typedef cml::vector2i	size2s;
struct rect2s	{	point2s	origin;		size2s	size;	};
typedef cml::vector3i	vector3s;
typedef cml::vector3i	point3s;
typedef cml::vector3i	size3s;
struct rect3s	{	point3s	origin;		size3s	size;	};
typedef cml::vector2f	vector2f;
typedef cml::vector2f	point2f;
typedef cml::vector2f	size2f;
struct rect2f	{	point2f	origin;		size2f	size;	};
typedef cml::vector3f	vector3f;
typedef cml::vector3f	point3f;
typedef cml::vector3f	size3f;
struct rect3f	{	point3f	origin;		size3f	size;	};

// Types
#include "Types.h"

// Memory
#define ALLOC(T)	Memory::GetPtr()->Alloc<T>()
#define FREE(h)		Memory::GetPtr()->Free(h)

#include "Memory/Memory.h"
#include "Memory/WonderPtr.h"

// Log
#include "Log/Log.h"

template<class T>
std::string ToStdString(T i)
{
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();

    return s;
}

#define ToString(var) ToStdString(var)
#define APPEND_STR(str)		+ std::string(str)

// String concat
#define CONCAT(a,b)				a ## b
#define CONCAT_SPACE(str1,str2) #str1 " " #str2
#define MACRO_STR(str)			#str

#endif // __UTILITY_H__