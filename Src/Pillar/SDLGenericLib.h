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

#ifndef __SDL_GENERIC_LIB_H__
#define __SDL_GENERIC_LIB_H__

#include "SDL.h"
#include "SDL_image.h"
#include <string>

typedef struct Sprite
{
	SDL_Texture* texture;
	Uint16 w;
	Uint16 h;
	std::string path;

	Sprite()
	{
		texture = NULL;
		w = 0;
		h = 0;
		path.empty();
	}
} Sprite;

class SDLGenericLib
{
public:

	// Renderer
	static void SetRenderer(SDL_Renderer* renderer);
	static SDL_Renderer* GetRenderer();

	// Image loader
	// Adapted from SDL's testspriteminimal.c
	static Sprite LoadSprite(const char* file);
	static void UnloadSprite(Sprite sprite);
};

#endif // __SDL_GENERIC_LIB_H__