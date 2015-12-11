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

#ifndef __FACTORY_H__
#define __I_BLUEPRINT_H__

#include "Utility/Utility.h"
#include "FactoryScript.h"
#include "RTTI.h"

template <class T_RTTI, class T_DATA>
class Factory
{
public:
	virtual void Register(T_RTTI name, FactoryScript<T_DATA>* script)
	{
		_factoryScriptMap.insert(std::pair< T_RTTI, FactoryScript<T_DATA>* >(name, script));
	}
	virtual T_DATA* Create(T_RTTI name)
	{
		return _factoryScriptMap.find(name)->second->RunScript();
	}
protected:
	std::map< T_RTTI, FactoryScript<T_DATA>* >	_factoryScriptMap;
};

#endif // __I_BLUEPRINT_H__