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

#include "ImageSpriteEntity.h"

void ImageSpriteEntity::SetSpriteGrid(s32 gridCountHorizontal, s32 gridCountVertical)
{
	// Set vars
	this->gridCountHorizontal	= gridCountHorizontal;
	this->gridCountVertical		= gridCountVertical;
	this->spriteFrameCode		= 0;
	this->spriteFrameCount		= gridCountHorizontal * gridCountVertical;
	
	// Set size
	this->size.data()[0]	= (f32)(sprite.w / gridCountHorizontal);
	this->size.data()[1]	= (f32)(sprite.h / gridCountVertical);

	// Set pivot
	this->pivot	= this->size / 2;

	// Calc frame size
	frameSize.data()[0]	= (f32)(sprite.w / gridCountHorizontal);
	frameSize.data()[1]	= (f32)(sprite.h / gridCountVertical);

	// Calc every sprite rects
	
	for (s32 j = 0; j < gridCountVertical; ++j)
	{
		for (s32 i = 0; i < gridCountHorizontal; ++i)
		{
			// Set
			rect2f spriteRect;
			spriteRect.origin.data()[0] = i * frameSize.data()[0];
			spriteRect.origin.data()[1] = j * frameSize.data()[1];
			spriteRect.size = frameSize;
			// Add
			spriteRects.push_back(spriteRect);
		}
	}
}

bool ImageSpriteEntity::SetSpriteCurrentFrameCode(s32 frameCode)
{
	// Check
	s32 frameCountMax	= this->gridCountHorizontal * this->gridCountVertical;
	if (frameCountMax <= frameCode)
		return false;
	// Set
	this->spriteFrameCode		= frameCode;
	spriteRectCurrent			= spriteRects[frameCode];
	return true;
}
