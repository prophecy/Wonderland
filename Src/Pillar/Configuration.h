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

#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "Utilities/Singleton.h"
#include "Library/Library.h"
#include "Canvas/CanvasMode.h"

class IRenderer;

class Configuration : public Singleton<Configuration>
{
public:

	enum Renderertype
	{
		RENDERER_TYPE_NONE = 0,
		RENDERER_TYPE_SDL_SIMPLE,
		RENDERER_TYPE_SDL_LIBROCKET,
		RENDERER_TYPE_USER_DEFINED,
		RENDERER_TYPE_SDL_OPENGL,
	};

	Configuration();
	void					SetCanvasSize(const size2f* size);
	size2f					GetCanvasSize();
	void					SetCanvasMode(CanvasMode mode);
	CanvasMode				GetCanvasMode();
	void					SetScreenSize(const size2f* size);
	size2f					GetScreenSize();
	void					SetCanvasColor(u8 r, u8 g, u8 b, u8 a);
	u8*						GetCanvasColor();
	void					SetRendererType(Renderertype type);
	Renderertype			GetRendererType();
	void					SetUserDefinedRenderer(IRenderer* renderer);
	IRenderer*				GetUserDefinedRenderer();

private:

	size2f				_canvasSize;
	CanvasMode			_canvasMode;
	size2f				_screenSize;
	u8					_canvasColor[4];
	Renderertype		_rendererType;
	IRenderer*			_userDefinedRenderer;
};

#endif // __CONFIGURATION_H__