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

#ifndef __WONDERLAND_H__
#define __WONDERLAND_H__

#include "../IWonderland.h"

#include "../IApplication.h"
#include "../IRunLoop.h"
#include "../Manager/TaskManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/EventManager.h"
#include "../../Library/Library.h"

class Wonderland
{
public:
	Wonderland();
	~Wonderland();

	void SetApplication(IApplication* application);
	void SetRunLoop(IRunLoop* runLoop);
	void Create();
	void Destroy();

private:
	IApplication*	_application;
	IRunLoop*		_runLoop;
	TaskManager*	_taskManager;
	SceneManager*	_sceneManager;
	EventManager*	_eventManager;
};

#endif // __WONDERLAND_H__