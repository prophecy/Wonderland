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

#include "Configuration.h"
#include "Foundation/IRenderer.h"

template <> Configuration* Singleton<Configuration>::instance	= 0;

Configuration::Configuration()
{
	_canvasSize.set( 1180.0f, 720.0f ); 
	_canvasMode = CanvasMode::CanvasModeAspectFit;
	_screenSize.set( 1180.0f, 720.0f ); 
	_canvasColor[0] = 0x00;
	_canvasColor[1] = 0x49;
	_canvasColor[2] = 0x83;
	_canvasColor[3] = 0xFF;
	_rendererType = Renderertype::RENDERER_TYPE_SDL_SIMPLE;
	_userDefinedRenderer = NULL;
}

void Configuration::SetCanvasSize(const size2f* size)
{
	_canvasSize	= *size;
}

size2f Configuration::GetCanvasSize()
{
	return _canvasSize;
}

void Configuration::SetCanvasMode(CanvasMode canvasMode)
{
	_canvasMode	= canvasMode;
}
	
CanvasMode Configuration::GetCanvasMode()
{
	return _canvasMode;
}

void Configuration::SetScreenSize(const size2f* size)
{
	_screenSize	= *size;
}

size2f Configuration::GetScreenSize()
{
	return _screenSize;
}

void Configuration::SetCanvasColor(u8 r, u8 g, u8 b, u8 a)
{
	_canvasColor[0] = r;
	_canvasColor[1] = g;
	_canvasColor[2] = b;
	_canvasColor[3] = a;
}

u8* Configuration::GetCanvasColor()
{
	return _canvasColor;
}

void Configuration::SetRendererType(Configuration::Renderertype type)
{
	_rendererType = type;
}

Configuration::Renderertype	Configuration::GetRendererType()
{
	return _rendererType;
}

void Configuration::SetUserDefinedRenderer(IRenderer* renderer)
{
	_userDefinedRenderer = renderer;
}

IRenderer* Configuration::GetUserDefinedRenderer()
{
	return _userDefinedRenderer;
}