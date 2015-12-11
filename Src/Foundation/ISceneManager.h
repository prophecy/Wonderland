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

#ifndef __I_SCENE_MANAGER_H__
#define __I_SCENE_MANAGER_H__

#include "IBase.h"

class IScene;

// Scenes are in the Application
class ISceneManager : public IBase
{
public:
	virtual u32 AddScene(WonderPtr<IScene> scene)			= 0;
	virtual void RemoveScene(WonderPtr<IScene> scene)		= 0;
	virtual void RemoveScene(u32 sceneId)					= 0;
	virtual void StartScene(WonderPtr<IScene> scene)		= 0;
	virtual void SetNextScene(u32 sceneCode)				= 0;
	virtual WonderPtr<IScene> GetCurrentScene()				= 0;
	virtual void OnChangeScene()							= 0;
protected:
	WonderPtr<IScene> currentScene;
};

#endif // __I_SCENE_MANAGER_H__