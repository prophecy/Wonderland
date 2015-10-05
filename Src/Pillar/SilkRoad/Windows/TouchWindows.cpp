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

#include "TouchWindows.h"
#include "../../Foundation/Portal/Portal.h"

TouchWindows::TouchWindows()
{
	_touchStatus	= TouchStatusIdle;
	_touchPoint.set(0, 0);
}

TouchWindows::~TouchWindows()
{

}

void TouchWindows::PollEventStart()
{
	_touchPointLastFrame	= _touchPoint;
}

void TouchWindows::PollEventUpdate(SDL_Event* event)
{
	Canvas* canvas = Portal::GetPtr()->GetCanvas();
	Log* log = Portal::GetPtr()->GetLog();

	// Touch status
	if ( event->type == SDL_MOUSEBUTTONDOWN )
	{
		_touchStatus	= TouchStatusBegan;
	}

	if ( event->type == SDL_MOUSEBUTTONUP )
	{
		_touchStatus	= TouchStatusEnded;
	}

	// Cursor
	point2f point = point2f((f32)event->button.x, 
							(f32)event->button.y);
	_touchPoint	= canvas->GetCanvasPointFromScreenPoint(&point);
}

void TouchWindows::PollEventFinish()
{
	if ( _touchStatusLastFrame == TouchStatusBegan )
		_touchStatus	= TouchStatusMoved;
	if ( _touchStatusLastFrame == TouchStatusEnded )
		_touchStatus	= TouchStatusIdle;
	_touchStatusLastFrame	= _touchStatus;
}

TouchStatus TouchWindows::GetStatus()
{
	return _touchStatus;
}

point2f* TouchWindows::GetPoint()
{
	return &_touchPoint;
}