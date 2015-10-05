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

#include "ImageEntity.h"
#include "../SDLGenericLib.h"
#include "../Wonderlang.h"
#include "../Foundation/Portal/Portal.h"

void ImageEntity::LoadImage(std::string name)
{
	//Portal::GetPtr()->GetLog()->LogMessage("LoadImage: " + name);

	// load image
	sprite = SDLGenericLib::LoadSprite(name.c_str());

	// set properties
	position.set(0, 0);
	pivot.set((f32)sprite.w * 0.5f, (f32)sprite.h * 0.5f);
	size.set(sprite.w, sprite.h);

	radian	= 0.0f;
	scale	= 1.0f;

	// add to wonder lang
	Wonderlang::renderBatch.push_back(this);

	/*
	Portal::GetPtr()->GetLog()->LogMessage("Position: " + 
												TO_STR(position.data()[0]) + ", " +
												TO_STR(position.data()[1]) +
											" Pivot: " +
												TO_STR(pivot.data()[0]) + ", " +
												TO_STR(pivot.data()[1]) +
											" Size: " + 
												TO_STR(sprite.w) + ", " +
												TO_STR(sprite.h));
												*/
}

void ImageEntity::UnloadImage()
{
	// unload image
	SDLGenericLib::UnloadSprite(sprite);

	// clear sprite var
	sprite.texture = NULL;
	sprite.h = 0;
	sprite.w = 0;

	// Search and erase from the render batch
	std::vector<ImageEntity*>::iterator it = Wonderlang::renderBatch.begin();

	int size01 = Wonderlang::renderBatch.size();

	for (;it != Wonderlang::renderBatch.end(); ++it)
	{
		if (*it == this)
		{
			Wonderlang::renderBatch.erase(it);
			break;
		}
	}
	
	int size02 = Wonderlang::renderBatch.size();
}