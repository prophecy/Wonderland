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

#include "ImageFontEntity.h"
#include <map>

std::map<s8, s32> scecialCharMap;

void ImageFontEntity::Create()
{
	Create("Resource/Shared/SpriteFont.png", 8, 12);
}

void ImageFontEntity::Create(std::string path, s32 horzCount, s32 vertCount)
{
	// Set image
	LoadImage(path);
	position = point2f(0, 0);
	SetSpriteGrid(horzCount, vertCount);
	SetSpriteCurrentFrameCode(0);

	s8 charSet[] = {
		'.', ',', ';', ':', '?',
		'!', '-', '_', '~', '#',
		'"', '\'', '&', '(', ')',
		'[', ']', '|', '`', '\\',
		'/', '@', ' ', '+', '=', 
		'*', '$', '<', '>' };

	s32 index[] = {
		62, 63, 64, 65, 66, 
		67, 68, 69, 70, 71, 
		72, 73, 74, 75, 76, 
		77, 78, 79, 80, 81, 
		82, 83, 84, 85, 86, 
		87, 88, 91, 92 };

	for (int i = 0; i <= 29; ++i)
		scecialCharMap.insert(std::pair<s8, s32>(charSet[i], index[i]));
}

void ImageFontEntity::SetText(s8 ch)
{
	if (ch >= 65 && ch <= 90)
		SetSpriteCurrentFrameCode(ch - 'A');
	else if (ch >= 97 && ch <= 122)
		SetSpriteCurrentFrameCode(ch - 'a');
	else if (ch == ' ')
		SetSpriteCurrentFrameCode(94);
	else
	{
		if (scecialCharMap.count(ch))
			SetSpriteCurrentFrameCode(scecialCharMap[ch]);
		else
			SetSpriteCurrentFrameCode(93);
	}
}