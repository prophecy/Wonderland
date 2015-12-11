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

#include "InputManager.h"
#include <vector>

using namespace std;

static vector<IInput*> _s_inputs;

void InputManager::AddInput(IInput* input)
{
	_s_inputs.push_back(input);
}

s32 InputManager::RemoveInput(s32 index)
{
	if (index >= (s32)_s_inputs.size())
		return -1;

	vector<IInput*> tmpInputs;

	for (u32 i = 0; i < _s_inputs.size(); ++i)
		if (i != index)
			tmpInputs.push_back(_s_inputs[i]);

	_s_inputs = tmpInputs;

	return 0;
}

void InputManager::ClearInputs()
{
	_s_inputs.clear();
}

IInput* InputManager::GetInput(s32 index)
{
	if (index > (s32)_s_inputs.size())
		return NULL;

	return _s_inputs[index];
}

void InputManager::PollEventStart()
{
	vector<IInput*>::iterator it = _s_inputs.begin();
	for (; it != _s_inputs.end(); ++it)
		(*it)->PollEventStart();
}

void InputManager::PollEventUpdate()
{
	vector<IInput*>::iterator it = _s_inputs.begin();
	for (; it != _s_inputs.end(); ++it)
		(*it)->PollEventUpdate();
}

void InputManager::PollEventFinish()
{
	vector<IInput*>::iterator it = _s_inputs.begin();
	for (; it != _s_inputs.end(); ++it)
		(*it)->PollEventFinish();
}
