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

//--------------------------------------------
#ifdef POOL_PRECOMP_SUPPORT
#include PRECOMP_DOT_H
#else // #ifdef POOL_PRECOMP_SUPPORT

#include <iostream>
#include <vector>
using namespace std;

#endif // #ifdef POOL_PRECOMP_SUPPORT
//--------------------------------------------
#include "GenericPool.h"
#include "PoolFacade.h"

//--------------------------------------------
// PIMPL
struct PoolFacade::PIMPL
{
	vector<Pool*> pPools; 
};
//--------------------------------------------

template <> PoolFacade* Singleton<PoolFacade>::instance	= 0;
//--------------------------------------------
PoolFacade::PoolFacade()
{
	_pimpl	= new PIMPL;
}
//--------------------------------------------
PoolFacade::~PoolFacade()
{
	delete(_pimpl);
}
//--------------------------------------------
PoolFacade::Pool* const PoolFacade::CreatePool(size_t sliceSize, long sliceCount)
{
	Pool* newPool	= NULL;
	
	try
	{
		newPool = new(sliceSize, sliceCount)GenericPool;
	}
	catch(...) // if pool has some troubles when attempt to be created.
	{
		delete(newPool);
		newPool	= NULL;
		return NULL;
	}
	
	// successful
	
	// keep pool pointer in vector
	_pimpl->pPools.push_back(newPool);

	// return pool pointer
	return newPool;
}
//--------------------------------------------
bool PoolFacade::DeletePool(PoolFacade::Pool *poolPtr)
{
	delete(poolPtr);
	poolPtr	= NULL;
	return true;
}
//--------------------------------------------
std::vector<PoolFacade::Pool*> PoolFacade::GetPoolList()
{
	return _pimpl->pPools;
}
//--------------------------------------------
void PoolFacade::DeleteAllPool()
{
	std::vector<Pool*>::iterator	it;
	for (it = _pimpl->pPools.begin(); it != _pimpl->pPools.end(); ++it)
	{
		DeletePool(*it);
	}
}