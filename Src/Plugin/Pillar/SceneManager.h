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

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "Library.h"
#include "ISceneManager.h"

class IScene;

// Scenes are in the Application
class SceneManager : public ISceneManager
{
public:
	u32 AddScene(WonderPtr<IScene> scene);
	void RemoveScene(WonderPtr<IScene> scene);
	void RemoveScene(u32 sceneId);
	void StartScene(WonderPtr<IScene> scene);
	void SetNextScene(u32 sceneCode);
	WonderPtr<IScene> GetCurrentScene();
	virtual void OnChangeScene();

private:
	WonderPtr<IScene> _currentScene;
	WonderPtr<IScene> _previousScene;
	std::map<u32, WonderPtr<IScene>>	_sceneMap;
	//std::map<WonderPtr<IScene>, u32>	_sceneMapReverse;
};

#endif // __SCENE_MANAGER_H__