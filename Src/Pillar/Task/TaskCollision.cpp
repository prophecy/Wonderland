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

#include "TaskCollision.h"
#include "../Physics/Physics.h"

void TaskCollision::Start()
{
	_touchPoint.set(-1, -1);
}

void TaskCollision::OnTask()
{
	_TestEntitiesCollisionWithTouchPoint();
	_TestEntitiesCollisionWithEntities();
}

void TaskCollision::_TestEntitiesCollisionWithTouchPoint()
{
	// Check collision if touch
	if ( _touchPoint != point2s(-1, -1) )
	{
		// Check collision between touch and entities
		std::map< std::string, std::vector<WonderPtr<CollisionEntity>> >::iterator iterMap;
		
		for (	iterMap = _entityGroup.begin();
				iterMap != _entityGroup.end();
				++iterMap	)
		{
			std::vector<WonderPtr<CollisionEntity>> vec = iterMap->second;
			std::vector<WonderPtr<CollisionEntity>>::iterator	iterVec;

			for (	iterVec	= vec.begin();
					iterVec != vec.end();
					++iterVec	)
			{
				WonderPtr<CollisionEntity> entity = (*iterVec);
				
				// Update collision entity
				WonderPtr<CollisionEntity> contentEntity = entity->GetEntity();
				entity->position	= contentEntity->position;
				entity->pivot		= contentEntity->pivot;
				entity->radian		= contentEntity->radian;
				entity->scale		= contentEntity->scale;
				entity->size		= contentEntity->size;

				// Start collision test
				if ( entity->GetCollisionShape() == CollisionShapeBoundingBox )
				{
					// Collision testing between bounding box, and touch point
					ColliderBoundingBox boundingBoxCollider;
					boundingBoxCollider.pointA	= entity->position - entity->pivot;
					boundingBoxCollider.pointB	= entity->position + entity->size - entity->pivot;
					ColliderPoint point	= ColliderPoint(_touchPoint);
					bool isColid	= Collision2D::IsCollid(
										boundingBoxCollider, 
										point);
					if ( isColid )
						OnCollision(entity, &point.position);
				}
				else if ( entity->GetCollisionShape() == CollisionShapeSphere )
				{
					// Collision testing between sphere, and touch point
					ColliderSphere sphereCollider;
					point2f center	= entity->size / 2;
					sphereCollider.position	= entity->position + center - entity->pivot;
					sphereCollider.radious	= ( entity->size.data()[0] + entity->size.data()[1] ) / 4;
					ColliderPoint point	= ColliderPoint(_touchPoint);
					bool isColid	= Collision2D::IsCollid(
										sphereCollider, 
										point);
					if ( isColid )
						OnCollision(entity, &point.position);
				}
			}
		}
	}
	
	// reset touch point
	_touchPoint.set(-1, -1);
}

void TaskCollision::_TestEntitiesCollisionWithEntities()
{
	std::map< std::string, s32 >	groupCheckedMap;
	std::map< std::string, std::vector<WonderPtr<CollisionEntity>> >::iterator iterMapGroupA;
	for (	iterMapGroupA = _entityGroup.begin();
			iterMapGroupA != _entityGroup.end();
			++iterMapGroupA	)
	{
		// Check if any group has already checked
		std::string groupName	= (*iterMapGroupA).second[0]->GetGroupName();
		if ( groupCheckedMap.empty() && groupCheckedMap.count( groupName ) )
			continue;

		groupCheckedMap.insert( std::pair< std::string, s32 > (groupName, 0) );

		std::map< std::string, std::vector<WonderPtr<CollisionEntity>> >::iterator iterMapGroupB;
		for (	iterMapGroupB = _entityGroup.begin();
				iterMapGroupB != _entityGroup.end();
				++iterMapGroupB	)
		{
			// Check to abandon if the same group
			if ( iterMapGroupA == iterMapGroupB )
				break;

			// Check collision
			std::vector<WonderPtr<CollisionEntity>> vecGroupA = iterMapGroupA->second;
			std::vector<WonderPtr<CollisionEntity>>::iterator	iterVecGroupA;
			std::vector<WonderPtr<CollisionEntity>> vecGroupB = iterMapGroupB->second;
			std::vector<WonderPtr<CollisionEntity>>::iterator	iterVecGroupB;

			for (	iterVecGroupA = vecGroupA.begin();
					iterVecGroupA != vecGroupA.end();
					++iterVecGroupA	)
			{
				for (	iterVecGroupB = vecGroupB.begin();
						iterVecGroupB != vecGroupB.end();
						++iterVecGroupB	)
				{
					WonderPtr<CollisionEntity> entityA = (*iterVecGroupA);
					WonderPtr<CollisionEntity> entityB = (*iterVecGroupB);
					
					// Update collision entity
					WonderPtr<CollisionEntity> contentEntityA = entityA->GetEntity();
					entityA->position	= contentEntityA->position;
					entityA->pivot		= contentEntityA->pivot;
					entityA->radian		= contentEntityA->radian;
					entityA->scale		= contentEntityA->scale;
					entityA->size		= contentEntityA->size;
					
					WonderPtr<CollisionEntity> contentEntityB = entityB->GetEntity();
					entityB->position	= contentEntityB->position;
					entityB->pivot		= contentEntityB->pivot;
					entityB->radian		= contentEntityB->radian;
					entityB->scale		= contentEntityB->scale;
					entityB->size		= contentEntityB->size;

					ColliderBoundingBox boundingBoxColliderA;
					boundingBoxColliderA.pointA	= entityA->position - entityA->pivot;
					boundingBoxColliderA.pointB	= entityA->position + entityA->size - entityA->pivot;

					ColliderBoundingBox boundingBoxColliderB;
					boundingBoxColliderB.pointA	= entityB->position - entityB->pivot;
					boundingBoxColliderB.pointB	= entityB->position + entityB->size - entityB->pivot;

					bool isColid	= Collision2D::IsCollid(
										boundingBoxColliderA, 
										boundingBoxColliderB);
					if ( isColid )
						OnCollision(entityA, entityB);
				}
			}
		}
	}
}

void TaskCollision::AddCollisionEntity(WonderPtr<CollisionEntity> collisionEntity)
{
	// Group ( by name ) is exist
	if ( ! _entityGroup.empty() && _entityGroup.count(collisionEntity->GetGroupName()) )
	{
		// Add entity to vector in the map
		_entityGroup.find(collisionEntity->GetGroupName())->second.push_back(collisionEntity);
	}
	// Group ( by name ) is not exist
	else
	{
		// Add entity to new group
		std::pair< std::string, std::vector<WonderPtr<CollisionEntity>> > ePair;
		ePair.first		= collisionEntity->GetGroupName();
		ePair.second = std::vector<WonderPtr<CollisionEntity>>();
		ePair.second.push_back(collisionEntity);

		_entityGroup.insert(ePair);
	}
}

void TaskCollision::SetTouchPoint(point2s* point)
{
	_touchPoint	= *point;
}
