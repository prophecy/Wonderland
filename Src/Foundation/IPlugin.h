
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

#ifndef __I_PLUGIN_H__
#define __I_PLUGIN_H__

#include "IBase.h"

class IApplication;

class IPlugin : public IBase
{
public:
	virtual void Create(WonderPtr<IApplication>	application) = 0;
	virtual void Destroy() = 0;
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void Resume() = 0;
	virtual void Pause() = 0;
    virtual void Update() = 0;
};

#endif // __I_PLUGIN_H__