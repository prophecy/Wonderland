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

#ifndef __COLLISION_ENTITY_H__
#define __COLLISION_ENTITY_H__

#include "../Library/Library.h"
#include "../Foundation/IEntity.h"

enum CollisionShape
{
	CollisionShapeSphere	= 0,
	CollisionShapeBoundingBox,
};

class CollisionEntity : public IEntity
{
public:
	static RTTI rtti;
	RTTI* rttiPtr;

	CollisionEntity()	
	{
		CollisionEntity::rttiPtr = &CollisionEntity::rtti;
	}

	void Create(
		WonderPtr<CollisionEntity> entity, CollisionShape shape,
		std::string groupName, std::string colliderName);
	void Destroy();

	WonderPtr<CollisionEntity>		GetEntity()		{ return _entity; }
	CollisionShape	GetCollisionShape()		{ return _shape; }
	std::string		GetGroupName()			{ return _groupName; }
	std::string		GetColliderName()		{ return _colliderName; }

private:
	WonderPtr<CollisionEntity>	_entity;
	CollisionShape		_shape;
	std::string			_groupName;
	std::string			_colliderName;
};

#endif // __COLLISION_ENTITY_H__