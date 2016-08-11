/*
 * This source file is part of Wonderland, the C++ Cross-platform middleware for game
 *
 * For the latest information, see https://github.com/prophecy/Wonderland
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

#include "TaskManager.h"
#include "ITask.h"

void TaskManager::UpdateTasks()
{
	for (u32 i = 0; i < _runningTasks.size(); ++i)
	{
		_runningTasks[i]->OnTask();
	}
}

void TaskManager::AddTask(WonderPtr<ITask> task)
{
	_tasks.push_back(task);
	task->taskManager	= this;
}

void TaskManager::StartTask(WonderPtr<ITask> task)
{
	_runningTasks.push_back(task);
	task->Start();
}

void TaskManager::StopTask(WonderPtr<ITask> task)
{
	task->Stop();
	_RemoveRunningTask(task);
}

// todo: need better search algorithm
WonderPtr<ITask> TaskManager::_SearchTask(WonderPtr<ITask> task)
{
	for ( u32 i = 0; i < _tasks.size(); ++i )
	{
		if ( _tasks[i] == task )
		{
			return _tasks[i];
		}
	}

	return NULL;
}

bool TaskManager::_RemoveRunningTask(WonderPtr<ITask> task)
{
	std::vector<WonderPtr<ITask>>::iterator it;
	for ( it = _runningTasks.begin(); it != _runningTasks.end(); ++it )
	{
		if ( *it == task )
		{
			_runningTasks.erase(it);
			return true;
		}
	}
	return false;
}