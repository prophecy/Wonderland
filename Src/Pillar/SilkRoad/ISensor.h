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

#ifndef __I_SENSOR_H__
#define __I_SENSOR_H__

#include "../Library/Library.h"

class ISensor
{
public:

	enum KeyState
	{
		KeystateNone = 0,
		KeyStatePressed,
		KeyStateReleased,
	};

	struct KeyField
	{
		KeyState	spacebar;
		KeyState	a, s, d, w;

		KeyField()
		{
			a = s = d = w	= 
			spacebar		= KeystateNone;
		}
	};

	enum MouseButtonState
	{
		MouseButtonStateNone = 0,
		MouseButtonStateDown,
		MouseButtonStateUp,
	};

	struct MouseButtonField
	{
		MouseButtonState Left;
		MouseButtonState Middle;
		MouseButtonState Right;

		MouseButtonField()
		{
			Left = Middle = Right = MouseButtonStateNone;
		}
	};

	enum AppState
	{
		AppStateCreate		= 1,
		AppStateDestroy		= 2,
		AppStateStart		= 4,
		AppStateStop		= 8,
		AppStateResume		= 16,
		AppStatePause		= 32,
	};

	struct AppStateField
	{
		u64 states;

		AppStateField()
		{
			states = 0;
		}

		bool IsOnState(AppState state)
		{
			if ( states & state )
				return true;
			return false;
		}
	};



public:
	// Polling functions
	virtual void PollEventStart()						= 0;
	virtual void PollEventUpdate(SDL_Event* event)		= 0;
	virtual void PollEventFinish()						= 0;
	// Accelerometers
	virtual vector3f* GetAccelerometerValues()			= 0;
	// Key
	virtual KeyField* GetKeyField()						= 0;
	// Mouse
	virtual MouseButtonField* GetMouseButtonField()		= 0;
	// Application state
	virtual AppStateField* GetAppStateField()			= 0;
};

#endif // __I_SENSOR_H__