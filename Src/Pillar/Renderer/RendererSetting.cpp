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

#include "RendererSetting.h"
#include "../Foundation/Portal/Portal.h"
#include "../Foundation/IRenderer.h"
#include "SDLRenderer.h"
#include "SDLSimpleRenderer.h"
#include "SDLLibRocketRenderer.h"
#include "SDLOpenGLRenderer.h"

SDLRenderer*	_sdlRenderer;
SDL_Window*		RendererSetting::s_window;
SDL_Renderer*	RendererSetting::s_SDLRenderer;

void RendererSetting::Destroy()
{
	_sdlRenderer->Destroy();
	delete _sdlRenderer;
	_sdlRenderer = NULL;
}

IRenderer* RendererSetting::CreateRenderer(Configuration::Renderertype rendererType)
{
	if (rendererType == Configuration::Renderertype::RENDERER_TYPE_SDL_SIMPLE)
		_sdlRenderer = new SDLSimpleRenderer();
	else if (rendererType == Configuration::RENDERER_TYPE_SDL_LIBROCKET)
		_sdlRenderer = new SDLLibRocketRenderer();
	else if (rendererType == Configuration::RENDERER_TYPE_SDL_OPENGL)
		_sdlRenderer = new SDLOpenGLRenderer();
	else
		Portal::GetPtr()->GetLog()->DebugLog("Renderer not found!");

	_sdlRenderer->sdlWindow = s_window;
	_sdlRenderer->sdlRenderer = s_SDLRenderer;

	return (IRenderer*)_sdlRenderer;
}

IRenderer* RendererSetting::CreateRenderer(IRenderer* renderer)
{
	Portal::GetPtr()->GetLog()->DebugLog("No implementation");
	return NULL;
}
