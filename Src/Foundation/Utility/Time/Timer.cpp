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

#include "Timer.h"

static u64 _s_tickCurrent	= 0;
static u64 _s_tickPrevious	= 0;

static f64 _s_deltaTimeMax	= 0.5;

void Timer::Update()
{
	_s_tickPrevious = _s_tickCurrent;
	_s_tickCurrent = SDL_GetPerformanceCounter();
}

f32 Timer::GetDeltaTime()
{
	f64 dt = (f64)(_s_tickCurrent - _s_tickPrevious) / (f64)SDL_GetPerformanceFrequency();
	return (f32)((dt < _s_deltaTimeMax) ? dt : _s_deltaTimeMax);
}

f32 Timer::GetFps()
{
	return 1.0f / GetDeltaTime();
}

f64 Timer::GetHighPrecisionDeltaTime()
{
	f64 dt = (f64)(_s_tickCurrent - _s_tickPrevious) / (f64)SDL_GetPerformanceFrequency();
	return (dt < _s_deltaTimeMax) ? dt : _s_deltaTimeMax;
}

f64 Timer::GetHighPrecisionFps()
{
	return 1.0 / GetHighPrecisionDeltaTime();
}