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

#include "SensorWindows.h"
#include "SDL.h"

bool _isKeyStatusOnLeft;
bool _isKeyStatusOnRight;
bool _isKeyStatusOnUp;
bool _isKeyStatusOnDown;

SensorWindows::SensorWindows()		
{
	_isKeyStatusOnLeft	= false;
	_isKeyStatusOnRight	= false;
	_isKeyStatusOnUp	= false;
	_isKeyStatusOnDown	= false;

	_currentAccel.zero(); 
}

SensorWindows::~SensorWindows()	
{
}

void SensorWindows::PollEventStart()					
{
	_directionKey.zero();
	_appStateField.states	= 0;
}

void SensorWindows::PollEventUpdate(SDL_Event* event)
{
	if ( event->type == SDL_KEYDOWN )
	{
		if ( event->key.keysym.sym == SDLK_LEFT )
			_isKeyStatusOnLeft	= true;
		else if ( event->key.keysym.sym == SDLK_RIGHT )
			_isKeyStatusOnRight	= true;
		else if ( event->key.keysym.sym == SDLK_UP )
			_isKeyStatusOnUp	= true;
		else if ( event->key.keysym.sym == SDLK_DOWN )
			_isKeyStatusOnDown	= true;
		else if ( event->key.keysym.sym == SDLK_SPACE)
			_keyField.spacebar	= ISensor::KeyStatePressed;
		else if ( event->key.keysym.sym == SDLK_a )
			_keyField.a = ISensor::KeyStatePressed;
		else if ( event->key.keysym.sym == SDLK_s )
			_keyField.s = ISensor::KeyStatePressed;
		else if ( event->key.keysym.sym == SDLK_d )
			_keyField.d = ISensor::KeyStatePressed;
		else if ( event->key.keysym.sym == SDLK_w )
			_keyField.w = ISensor::KeyStatePressed;
	}
	else if ( event->type == SDL_KEYUP)
	{
		if ( event->key.keysym.sym == SDLK_LEFT )
			_isKeyStatusOnLeft	= false;
		else if ( event->key.keysym.sym == SDLK_RIGHT )
			_isKeyStatusOnRight	= false;
		else if ( event->key.keysym.sym == SDLK_UP )
			_isKeyStatusOnUp	= false;
		else if ( event->key.keysym.sym == SDLK_DOWN )
			_isKeyStatusOnDown	= false;
		else if ( event->key.keysym.sym == SDLK_SPACE)
			_keyField.spacebar	= ISensor::KeyStateReleased;
		else if ( event->key.keysym.sym == SDLK_a )
			_keyField.a = ISensor::KeyStateReleased;
		else if ( event->key.keysym.sym == SDLK_s )
			_keyField.s = ISensor::KeyStateReleased;
		else if ( event->key.keysym.sym == SDLK_d )
			_keyField.d = ISensor::KeyStateReleased;
		else if ( event->key.keysym.sym == SDLK_w )
			_keyField.w = ISensor::KeyStateReleased;
	}

	if ( event->type == SDL_MOUSEBUTTONDOWN )
	{
		if (event->button.button == SDL_BUTTON_LEFT)
			_mouseButtonField.Left = ISensor::MouseButtonStateDown;
		else if (event->button.button == SDL_BUTTON_MIDDLE)
			_mouseButtonField.Middle = ISensor::MouseButtonStateDown;
		else if (event->button.button == SDL_BUTTON_RIGHT)
			_mouseButtonField.Right = ISensor::MouseButtonStateDown;
	}
	else if ( event->type == SDL_MOUSEBUTTONUP )
	{
		if (event->button.button == SDL_BUTTON_LEFT)
			_mouseButtonField.Left = ISensor::MouseButtonStateUp;
		else if (event->button.button == SDL_BUTTON_MIDDLE)
			_mouseButtonField.Middle = ISensor::MouseButtonStateUp;
		else if (event->button.button == SDL_BUTTON_RIGHT)
			_mouseButtonField.Right = ISensor::MouseButtonStateUp;
	}

	// Application state
	if ( event->type == SDL_WINDOWEVENT )
	{
		if (	event->window.event == SDL_WINDOWEVENT_RESTORED
				)
		{
			_appStateField.states |= AppStateResume;
		}
		else if (	event->window.event == SDL_WINDOWEVENT_MINIMIZED ||
					event->window.event == SDL_WINDOWEVENT_MOVED
				)
		{
			_appStateField.states |= AppStatePause;
		}
	}
}

void SensorWindows::PollEventFinish()					
{
	if ( _isKeyStatusOnLeft )
		_directionKey.data()[0] -= 1.0f;
	if ( _isKeyStatusOnRight )
		_directionKey.data()[0] += 1.0f;
	if ( _isKeyStatusOnUp )
		_directionKey.data()[1] -= 1.0f;
	if ( _isKeyStatusOnDown )
		_directionKey.data()[1] += 1.0f;

	_currentAccel.set(_directionKey.data()[0], _directionKey.data()[1], 1.0f);
	_currentAccel.normalize();
}	

vector3f* SensorWindows::GetAccelerometerValues()	
{ 
	return &_currentAccel; 
}

ISensor::KeyField* SensorWindows::GetKeyField()
{
	return &_keyField;
}

ISensor::MouseButtonField* SensorWindows::GetMouseButtonField()
{
	return &_mouseButtonField;
}

ISensor::AppStateField* SensorWindows::GetAppStateField()
{
	return &_appStateField;
}