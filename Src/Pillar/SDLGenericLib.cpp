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

#include "SDLGenericLib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Foundation/Portal/Portal.h"
#include <map>
#include <string>

using namespace std;

struct SpriteInfo
{
	string path;
	Sprite sprite;
	s32 count;

	SpriteInfo()
	{
		path.empty();
		count = 0;
	}
};

static map<string, SpriteInfo> _s_spriteDictionary;

static SDL_Renderer* _s_renderer	= NULL;

void SDLGenericLib::SetRenderer(SDL_Renderer* renderer)
{
	_s_renderer = renderer;
}

SDL_Renderer* SDLGenericLib::GetRenderer()
{
	return _s_renderer;
}

Sprite CreateSprite(const char* path)
{
	Sprite result;
	result.texture = NULL;
	result.w = 0;
	result.h = 0;

	SDL_Surface* temp;

	/* Load the sprite image */
	temp = IMG_Load(path);

	if (temp == NULL)
	{
		Portal::GetPtr()->GetLog()->DebugLog("Couldn't load: " + TO_STR(path) + TO_STR(SDL_GetError()));
		return result;
	}

	result.w = temp->w;
	result.h = temp->h;

	/* Create texture from the image */
	result.texture = SDL_CreateTextureFromSurface(_s_renderer, temp);
	if (!result.texture) {
		Portal::GetPtr()->GetLog()->DebugLog("Couldn't create texture: " + TO_STR(SDL_GetError()));
		SDL_FreeSurface(temp);
		return result;
	}

	SDL_FreeSurface(temp);

	result.path = path;

	return result;
}

Sprite SDLGenericLib::LoadSprite(const char* path)
{
	Sprite sprite;

	if (_s_spriteDictionary.count(path) == 0)
	{
		SpriteInfo info;
		info.path = path;
		info.sprite = CreateSprite(path);
		info.count = 1;

		_s_spriteDictionary.insert(std::pair<string, SpriteInfo>(path, info));

		Portal::GetPtr()->GetLog()->DebugLog("CreateSprite: path" + string(path));
	}
	else
	{
		_s_spriteDictionary[path].count++;

		/*
		Portal::GetPtr()->GetLog()->LogMessage(
			"LoadSprite: path" + string(path) +
			" count: " + TO_STR(_s_spriteDictionary[path].count));
		*/
	}
	
	sprite = _s_spriteDictionary[path].sprite;

	return sprite;
}

void DestroySprite(Sprite sprite)
{
	SDL_DestroyTexture(sprite.texture);
}

void SDLGenericLib::UnloadSprite(Sprite sprite)
{
	if (_s_spriteDictionary.count(sprite.path) == 0)
	{
		Portal::GetPtr()->GetLog()->DebugLog("UnloadSprite error, sprite not found !");
	}
	else
	{
		_s_spriteDictionary[sprite.path].count--;

		Portal::GetPtr()->GetLog()->DebugLog(
			"sprite.path: " + sprite.path + 
			" count: " + TO_STR(_s_spriteDictionary[sprite.path].count));

		if (_s_spriteDictionary[sprite.path].count == 0)
		{
			Portal::GetPtr()->GetLog()->DebugLog("DestroySprite: path" + sprite.path);

			_s_spriteDictionary.erase(sprite.path);
			DestroySprite(sprite);
		}
	}

}