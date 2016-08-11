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

#ifndef __RTTI_H__
#define __RTTI_H__

#include "Utility/Utility.h"

/*	Runtime Type Identifier is to specify the the type of any object
	In the Wonderland, use RTTI as a static member
*/

class RTTI
{
public:
	
	RTTI()	{}

	RTTI(u32 code, std::string codeName, std::string description)
	{
		this->code			= code;
		this->codeName		= codeName;
		this->description	= description;
	}

	u32			code;
	std::string	codeName;
	std::string	description;
};

#endif // __RTTI_H__