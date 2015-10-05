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

#include "SilkRoad.h"

#if WONDERLAND_ACTIVE_PLATFORM == WONDERLAND_PLATFORM_WINDOWS
	#include "Windows/SensorWindows.h"
	#include "Windows/TouchWindows.h"
	typedef SensorWindows	ISensorCurrentPlatform;
	MemoryHandle<ISensorCurrentPlatform>*	_s_hSensor;
	typedef TouchWindows	ITouchCurrentPlatform;
	MemoryHandle<ITouchCurrentPlatform>*		_s_hTouch;
#elif WONDERLAND_ACTIVE_PLATFORM == WONDERLAND_PLATFORM_ANDROID
	#include "Android/SensorAndroid.h"
	#include "Android/TouchAndroid.h"
	typedef SensorAndroid	ISensorCurrentPlatform;
	MemoryHandle<ISensorCurrentPlatform>* _s_hSensor;
	typedef TouchAndroid	ITouchCurrentPlatform;
	MemoryHandle<ITouchCurrentPlatform>* _s_hTouch;
#elif WONDERLAND_ACTIVE_PLATFORM == WONDERLAND_PLATFORM_IPHONE
	#include "iOS/SensorIOS.h"
	typedef SensorIOS	ISensorCurrentPlatform;
	MemoryHandle<ISensorCurrentPlatform>* _s_hSensor;
#endif // WONDERLAND_ACTIVE_PLATFORM == ...

template <> SilkRoad* Singleton<SilkRoad>::instance	= 0;

SilkRoad::SilkRoad()
{
}

SilkRoad::~SilkRoad()
{
}

void SilkRoad::BuildUp()
{
	_s_hSensor	= ALLOC(ISensorCurrentPlatform);
	_activeSensor	= _s_hSensor->ptr;
	_s_hTouch	= ALLOC(ITouchCurrentPlatform);
	_activeTouch	= _s_hTouch->ptr;
}

void SilkRoad::TearDown()
{
	FREE(_s_hTouch);
	FREE(_s_hSensor);
}
	
ISensor* SilkRoad::GetSensor()
{
	return _activeSensor;
}

IMerchant* SilkRoad::GetMerchant()
{
	return _activeMerchant;
}

ISocial* SilkRoad::GetSocial()
{
	return _activeSocial;
}

ITouch* SilkRoad::GetTouch()
{
	return _activeTouch;
}

void SilkRoad::PollEventStart()
{
	_s_hSensor->ptr->PollEventStart();
	_s_hTouch->ptr->PollEventStart();
}

void SilkRoad::PollEventUpdate(SDL_Event* event)
{
	_s_hSensor->ptr->PollEventUpdate(event);
	_s_hTouch->ptr->PollEventUpdate(event);
}

void SilkRoad::PollEventFinish()
{
	_s_hSensor->ptr->PollEventFinish();
	_s_hTouch->ptr->PollEventFinish();
}
