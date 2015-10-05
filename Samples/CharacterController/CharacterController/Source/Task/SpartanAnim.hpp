#ifndef __SPARTAN_ANIM_HPP__
#define __SPARTAN_ANIM_HPP__

#include "../AppInclude.h"

#include <vector>
#include <string>
using namespace std;

class SpartanAnim : public TaskUpdate
{
public:

	enum ANIM_TYPE
	{
		NONE = 0,
		IDLE,
		WALK,
		ATTACK,
		BLOCK,
	};

	void SetAnimation(ANIM_TYPE type)
	{
		if (type == ANIM_TYPE::IDLE)
			_frameNamesPtr = &_idleFrameNames;
		else if (type == ANIM_TYPE::WALK)
			_frameNamesPtr = &_walkFrameNames;
		else if (type == ANIM_TYPE::ATTACK)
			_frameNamesPtr = &_attackStandFrameNames;
		else if (type == ANIM_TYPE::BLOCK)
			_frameNamesPtr = &_blockFrameNames;

		_currentFrameIndex = 0;
	}

	ANIM_TYPE GetAnimation()
	{
		if (_frameNamesPtr == &_idleFrameNames)
			return ANIM_TYPE::IDLE;
		else if (_frameNamesPtr == &_walkFrameNames)
			return ANIM_TYPE::WALK;
		else if (_frameNamesPtr == &_attackStandFrameNames)
			return ANIM_TYPE::ATTACK;
		else if (_frameNamesPtr == &_blockFrameNames)
			return ANIM_TYPE::BLOCK;
		return ANIM_TYPE::NONE;
	}

private:

	f32 _remainTime;
	f32 _flipTime;

	vector<string> _idleFrameNames;
	vector<string> _walkFrameNames;
	vector<string> _attackStandFrameNames;
	vector<string> _blockFrameNames;

	vector<string>* _frameNamesPtr;

	s32 _currentFrameIndex;

	WonderPtr<ImageAtlasEntity> _spartan;

	virtual void Start() override
	{
		_flipTime = 0.08f;
		_remainTime = _flipTime;

		_currentFrameIndex = 0;

		_idleFrameNames.push_back("idle_stand (1).png");
		_idleFrameNames.push_back("idle_stand (2).png");
		_idleFrameNames.push_back("idle_stand (3).png");
		_idleFrameNames.push_back("idle_stand (4).png");
		_idleFrameNames.push_back("idle_stand (5).png");
		_idleFrameNames.push_back("idle_stand (6).png");

		_walkFrameNames.push_back("walk (1).png");
		_walkFrameNames.push_back("walk (2).png");
		_walkFrameNames.push_back("walk (3).png");
		_walkFrameNames.push_back("walk (4).png");
		_walkFrameNames.push_back("walk (5).png");
		_walkFrameNames.push_back("walk (6).png");
		_walkFrameNames.push_back("walk (7).png");
		_walkFrameNames.push_back("walk (8).png");
		_walkFrameNames.push_back("walk (9).png");
		_walkFrameNames.push_back("walk (10).png");
		_walkFrameNames.push_back("walk (11).png");
		_walkFrameNames.push_back("walk (12).png");

		_attackStandFrameNames.push_back("attack_stand (1).png");
		_attackStandFrameNames.push_back("attack_stand (2).png");
		_attackStandFrameNames.push_back("attack_stand (3).png");
		_attackStandFrameNames.push_back("attack_stand (4).png");
		_attackStandFrameNames.push_back("attack_stand (5).png");
		_attackStandFrameNames.push_back("attack_stand (6).png");
		_attackStandFrameNames.push_back("attack_stand (7).png");
		_attackStandFrameNames.push_back("attack_stand (8).png");
		_attackStandFrameNames.push_back("attack_stand (9).png");
		_attackStandFrameNames.push_back("attack_stand (10).png");

		_blockFrameNames.push_back("defend_stand (1).png");
		_blockFrameNames.push_back("defend_stand (2).png");
		_blockFrameNames.push_back("defend_stand (3).png");
		_blockFrameNames.push_back("defend_stand (4).png");
		
		// Set Spartan
		_spartan = NULL;
		if (!entities.empty())
			_spartan = entities[0];

		_frameNamesPtr = &_idleFrameNames;
		_spartan->SetCurrentFrame((*_frameNamesPtr)[_currentFrameIndex]);
	}

	virtual void OnTask() override
	{
		f32 _deltaTime = Timer::GetDeltaTime();
		_remainTime -= _deltaTime;

		if (_remainTime <= 0.0f)
		{
			_remainTime = _flipTime - _remainTime;

			if (_frameNamesPtr == &_blockFrameNames &&
				_currentFrameIndex >= (s32)(*_frameNamesPtr).size() - 1)
			{
				// Don't change frame
			}
			else
			{
				if (++_currentFrameIndex >= (s32)_frameNamesPtr->size())
					_currentFrameIndex = 0;

				_spartan->SetCurrentFrame((*_frameNamesPtr)[_currentFrameIndex]);
			}

			if (_frameNamesPtr == &_attackStandFrameNames)
			{
				if (_currentFrameIndex >= (s32)(*_frameNamesPtr).size() - 1)
				{
					_frameNamesPtr = &_idleFrameNames;
					_currentFrameIndex = 0;
				}
			}
		}
	}
};

#endif // __SPARTAN_ANIM_HPP__