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

#ifndef __IMAGE_SPRITE_ENTITY_H__
#define __IMAGE_SPRITE_ENTITY_H__

#include "ImageEntity.h"

class ImageSpriteEntity : public ImageEntity
{
public:
	static RTTI		rtti;
	RTTI*			rttiPtr;

	ImageSpriteEntity()	
	{ 
		ImageEntity::rttiPtr		= &ImageSpriteEntity::rtti;
		ImageSpriteEntity::rttiPtr	= &ImageSpriteEntity::rtti;

		gridCountHorizontal = 0;
		gridCountVertical	= 0;
		spriteFrameCode		= 0;
		spriteFrameCount	= 0;
	}

	~ImageSpriteEntity()
	{
		UnloadImage();
	}

	void SetSpriteGrid(s32 gridCountHorizontal, s32 gridCountVertical);
	bool SetSpriteCurrentFrameCode(s32 frameCode);

public:
	s32					gridCountHorizontal;
	s32					gridCountVertical;
	size2f				frameSize;
	std::vector<rect2f>	spriteRects;
	rect2f				spriteRectCurrent;
	s32					spriteFrameCode;
	s32					spriteFrameCount;
};

#endif // __IMAGE_SPRITE_ENTITY_H__