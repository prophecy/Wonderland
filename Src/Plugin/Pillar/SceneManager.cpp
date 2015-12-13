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

#include "SceneManager.h"
#include "IScene.h"
#include "TaskManager.h"
#include "EventManager.h"
#include "MemoryHandle.h"
#include "Memory.h"

static u32 _s_sceneIdCurrent = 0;

u32 SceneManager::AddScene(WonderPtr<IScene> scene)
{
	// Ser vars
	_currentScene = NULL;
	_previousScene = NULL;

	// check is duplicate scene
	//bool isDuplicate	= false;
	//if (_sceneMapReverse.count(scene))
	//	isDuplicate		= true;

	//if ( isDuplicate )
	//	return 0;

	// increse scene counter
	++_s_sceneIdCurrent;

	// insert scene to map
	_sceneMap.insert(std::pair<u32, WonderPtr<IScene>>(_s_sceneIdCurrent, scene));
	//_sceneMapReverse.insert(std::pair<WonderPtr<IScene>, u32>(scene, _s_sceneIdCurrent));

	// Create necessary stuff for scene
	MemoryHandle<TaskManager>* hTaskMgr = ALLOC(TaskManager);
	scene->taskManager = (MemoryHandle<ITaskManager>*)hTaskMgr;
	MemoryHandle<EventManager>* hEvtMgr = ALLOC(EventManager);
	scene->eventManager = (MemoryHandle<IEventManager>*)hEvtMgr;

	// return scene counter
	return _s_sceneIdCurrent;
}

void SceneManager::RemoveScene(WonderPtr<IScene> scene)
{
	//if (_sceneMapReverse.count(scene))
	//	isSceneExist = true;

	// tear scene down
	scene->taskManager.Free();
	scene->entityManager.Free();

	// remove
	std::map<WonderPtr<IScene>, u32>::iterator it;
	//it = _sceneMapReverse.find(scene);
	_sceneMap.erase(it->second);
	//_sceneMapReverse.erase(scene);
}

void SceneManager::RemoveScene(u32 code)
{
	// remove
	std::map<u32, WonderPtr<IScene>>::iterator it;
	it = _sceneMap.find(code);
	//_sceneMapReverse.erase(it->second);
	_sceneMap.erase(code);
}

void SceneManager::StartScene(WonderPtr<IScene> scene)
{
	_currentScene = scene;
}

void SceneManager::SetNextScene(u32 sceneCode)
{
	_currentScene = _sceneMap[sceneCode];
}

WonderPtr<IScene> SceneManager::GetCurrentScene()
{
	return _currentScene;
}

void SceneManager::OnChangeScene()
{
	if (_currentScene != _previousScene)
	{
		if (_previousScene.IsValid())
		{
			// Collapse previous scene
			_previousScene->Stop();
			_previousScene->Destroy();

			// Build new scene
			_currentScene->Create();
			_currentScene->Start();
		}
	}

	_previousScene = _currentScene;
}