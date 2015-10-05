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

#ifndef __SENSOR_IOS_H__
#define __SENSOR_IOS_H__

#include "../../Library/Library.h"
#include "../ISensor.h"

class SensorIOS : public ISensor
{
public:
	SensorIOS()		{_currentAccel.zero();}
	~SensorIOS()	{}
	virtual void PollEventStart()					{}
	virtual void PollEventUpdate(SDL_Event* event)	{}
	virtual void PollEventFinish()					{}	

	virtual vector3f* GetAccelerometerValues()	{ return &_currentAccel; }
	
	virtual vector2s* GetMouseCursor()				{ }
	virtual MouseEvent* GetMouseClickEvent()		{ }
	virtual MouseEvent* GetMouseReleaseEvent()		{ }
	
	virtual std::vector<vector2s>* GetTouchPoints()	{ }
	virtual TouchEvent* GetTouchBeganEvent()		{ }
	virtual TouchEvent* GetTouchEndedEvent()		{ }

public:
	vector3f	_currentAccel;	
};


#endif // __SENSOR_IOS_H__