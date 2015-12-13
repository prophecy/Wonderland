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

#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

#include "Utility.h"
#include "ITaskManager.h"
#include "IEntity.h"

class TaskManager : public ITaskManager
{
public:
	virtual void UpdateTasksResource();
	virtual void UpdateTasksRender();
	virtual void UpdateTasksCalculator();
	virtual void AddTask(WonderPtr<ITask> task);
	virtual void StartTask(WonderPtr<ITask> task);
	virtual void StopTask(WonderPtr<ITask> task);
protected:
	// todo: change to more appropriate data structure
	std::vector<WonderPtr<ITask>>	_tasks;
	std::vector<WonderPtr<ITask>> _runningTasks;

	WonderPtr<ITask> _SearchTask(WonderPtr<ITask> task);
	bool _RemoveRunningTask(WonderPtr<ITask> task);
};

#endif // __TASK_MANAGER_H__