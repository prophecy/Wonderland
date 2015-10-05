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

#include "TouchAndroid.h"
#include "../../Foundation/Portal/Portal.h"

TouchAndroid::TouchAndroid()
{
	_touchStatus	= TouchStatusIdle;
	_touchPoint.set(0, 0);
}

TouchAndroid::~TouchAndroid()
{

}

void TouchAndroid::PollEventStart()
{
	_touchPointLastFrame	= _touchPoint;
}

void TouchAndroid::PollEventUpdate(SDL_Event* event)
{
	Log* log		= Portal::GetPtr()->GetLog();

	// Touch status
	if ( event->type == SDL_FINGERDOWN )
	{
		_touchStatus	= TouchStatusBegan;
		
		log->DebugLog(	"Touch point: x: " + TO_STR(event->tfinger.x) +
						" y: " + TO_STR(event->tfinger.y));

	}

	if ( event->type == SDL_FINGERMOTION )
	{
		_touchStatus	= TouchStatusMoved;
	}

	if ( event->type == SDL_FINGERUP )
	{
		_touchStatus	= TouchStatusEnded;
	}

	_SetCursor(event->tfinger.x, event->tfinger.y);
}

void TouchAndroid::_SetCursor(f32 touchX, f32 touchY)
{
	Canvas* canvas	= Portal::GetPtr()->GetCanvas();

	// Cursor
	size2f screenSize	= canvas->GetScreenSize();
	f32 pointScreenX	= screenSize.data()[0] * touchX;
	f32 pointScreenY	= screenSize.data()[1] * touchY;
	point2f point		= point2f(pointScreenX, pointScreenY);

	_touchPoint			= canvas->GetCanvasPointFromScreenPoint(&point);
}

void TouchAndroid::PollEventFinish()
{
	if ( _touchStatusLastFrame == TouchStatusEnded )
		_touchStatus	= TouchStatusIdle;
	_touchStatusLastFrame	= _touchStatus;
}

TouchStatus TouchAndroid::GetStatus()
{
	return _touchStatus;
}

point2f* TouchAndroid::GetPoint()
{
	return &_touchPoint;
}