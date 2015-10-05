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

#ifndef __ISCENE_H__
#define __ISCENE_H__

#include "IBase.h"
#include "ITaskManager.h"
#include "IEventManager.h"
#include "IEntityManager.h"
#include "IEntity.h"
#include "../Entity/Entity.h"
#include "../Library/Library.h"
#include "Portal/Portal.h"

class IScene : public IBase
{
public:
	virtual void Create()	= 0;
	virtual void Destroy()	= 0;
	virtual void Start()	= 0;
	virtual void Stop()		= 0;
	virtual void Resume()	= 0;
	virtual void Pause()	= 0;

	// todo: consider to move "AddEntity" to be in "Entity manager"
	virtual void AddEntity(WonderPtr<IEntity> entity)
	{
		std::vector< WonderPtr<IEntity> > entitiesDepth;
		entitiesDepth.push_back(entity);
		std::vector< std::vector< WonderPtr<IEntity> > > entitiesDepthList;
		std::vector< WonderPtr<IEntity> > rootEntityAsList;
		rootEntityAsList.push_back(entity);
		entitiesDepthList.push_back(rootEntityAsList);

		// depth search
		while ( true )
		{
			// Found brunch
			if ( ! entitiesDepth.back()->entities.empty() )
			{
				// Initiate sub brunches/entities AT index 0
				entitiesDepthList.push_back(entitiesDepth.back()->entities);
				// Initiate tasks
				_AddTasks(entitiesDepth.back());
				// Add the index 0 for the next depth
				entitiesDepth.push_back(*entitiesDepthList.back().begin());
			}
			// Found leaf
			else  
			{
				// Initiate tasks
				_AddTasks(entitiesDepth.back());
				// Next entity in the same tree depth level,
				// If the index is AT end(), pop_back, and next entity in higher level
				_Next(entitiesDepth, entitiesDepthList);
			}

			// if root is pop, end this tree
			if ( entitiesDepth.empty() )
				break;
		}
	}

	virtual void DisplayFps(void)
	{

	}

	virtual void BindTask(WonderPtr<ITask> task)
	{
		task->scene = this;
		taskManager->AddTask(task);
		taskManager->StartTask(task);
	}

private:

	void _Next(	std::vector< WonderPtr<IEntity> >& entitiesDepth,
		std::vector< std::vector< WonderPtr<IEntity> > > entitiesDepthList)
	{
		// Searth
		bool isFound = false;
		WonderPtr<IEntity> entity = entitiesDepth.back();
		std::vector< WonderPtr<IEntity> > list = entitiesDepthList.back();
		//std::vector< WonderPtr<IEntity> >::iterator	it = list.begin();
		u32 index = 0;
		for (; index < list.size(); ++index)
		{
			if (list[index] == entity)
				isFound = true;
		}

		if ( isFound )
		{	
			if ( index >= entitiesDepthList.back().size() )
			{
				// Last element, pop_back 1 level
				entitiesDepth.pop_back();
				entitiesDepthList.pop_back();
				// if entities depth is 0, early return
				if ( entitiesDepth.empty() )
					return; // End point of recursive stack
				// Next the upper level
				_Next(entitiesDepth, entitiesDepthList);
			}
			else
			{
				// Next entity
				entitiesDepth.pop_back();
				entitiesDepth.push_back(list[index]);
			}
		}
		else
		{
			Portal::GetPtr()->GetLog()->DebugLog("entitiesDepth not found in entitiesDepthList!");
		}
	}

	void _AddTasks(WonderPtr<IEntity> entity)
	{
		// Add all tasks of entity
		std::vector<WonderPtr<ITask>> tasks = entity->tasks;
		std::vector<WonderPtr<ITask>>::iterator it;
		for ( it = tasks.begin(); it != tasks.end(); ++it )
		{
			(*it)->scene = this;
			taskManager->AddTask(*it);
			taskManager->StartTask(*it);
		}
	}

public:
	WonderPtr<ISceneManager>	sceneManager;
	WonderPtr<ITaskManager>		taskManager;
	WonderPtr<IEventManager>	eventManager;
	WonderPtr<IEntityManager>	entityManager;
};

#endif // __ISCENE_H__