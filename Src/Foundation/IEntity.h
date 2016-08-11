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

#ifndef __I_ENTITY_H__
#define __I_ENTITY_H__

#include "IElement.h"
#include "ITask.h"

class IEntity : public IElement
{
public:
	static RTTI rtti;
public:
	IEntity()
	{
		isVisible = true;
	}

	void BindTask(WonderPtr<ITask> task)
	{
		WonderPtr<IEntity> ent = Memory::GetPtr()->GetHandle<IEntity>((addr)this);
		task->entities.push_back(ent);
		tasks.push_back(task);
	}
	
	std::vector<WonderPtr<IEntity>>		entities;
	std::vector<WonderPtr<ITask>>		tasks;

	point2f		position;
	point2f		pivot;
	f32			radian;
	f32			scale;
	size2f		size;
	bool		isVisible;
};

#endif // __I_ENTITY_H__