#ifndef __MOVE_HPP__
#define __MOVE_HPP__

#include "../AppInclude.h"
#include "SpartanAnim.hpp"

class Move : public TaskUpdate
{
public:
	WonderPtr<SpartanAnim> spartanAnim;

private:
	WonderPtr<ImageEntity> _actor;

	f32 _deltaTime;
	ISensor::KeyField* _keyField;

	f32 _horzSpeed;
	f32 _vertSpeed;

	ISensor::MouseButtonState mouseLeftPrevState;
	ISensor::MouseButtonState mouseRightPrevState;

	virtual void Start()
	{
		// Set ship
		_actor = NULL;
		if (!entities.empty())
			_actor = entities[0];

		_horzSpeed = 500.0f;
		_vertSpeed = 300.0f;

		mouseLeftPrevState = ISensor::MouseButtonStateNone;
	}

	virtual void OnTask()
	{
		f32 _deltaTime = Timer::GetDeltaTime();
		ISensor::KeyField* _keyField = SilkRoad::GetPtr()->GetSensor()->GetKeyField();
		ISensor::MouseButtonField* _mouseButtonField = SilkRoad::GetPtr()->GetSensor()->GetMouseButtonField();

		vector2f velocity;
		velocity.zero();

		if (_keyField->a == ISensor::KeyState::KeyStatePressed)
		{
			velocity.data()[0] -= (_horzSpeed*_deltaTime);

			if (! (spartanAnim->GetAnimation() == SpartanAnim::ATTACK))
				_actor->flip = ImageFlipHorizontal;
		}

		if (_keyField->d == ISensor::KeyState::KeyStatePressed)
		{
			velocity.data()[0] += (_horzSpeed*_deltaTime);

			if (!(spartanAnim->GetAnimation() == SpartanAnim::ATTACK))
				_actor->flip = ImageFlipNone;
		}

		if (_keyField->s == ISensor::KeyState::KeyStatePressed)
		{
			velocity.data()[1] -= (_vertSpeed*_deltaTime);
		}

		if (_keyField->w == ISensor::KeyState::KeyStatePressed)
		{
			velocity.data()[1] += (_vertSpeed*_deltaTime);
		}

		if (velocity.data()[0] >= -0.01f && velocity.data()[0] <= 0.01f)
		{
			if (!(spartanAnim->GetAnimation() == SpartanAnim::IDLE ||
				spartanAnim->GetAnimation() == SpartanAnim::ATTACK ||
				spartanAnim->GetAnimation() == SpartanAnim::BLOCK))
			{
				spartanAnim->SetAnimation(SpartanAnim::IDLE);
			}
		}
		else if (spartanAnim->GetAnimation() != SpartanAnim::WALK)
		{
			if (!(spartanAnim->GetAnimation() == SpartanAnim::ATTACK ||
				spartanAnim->GetAnimation() == SpartanAnim::BLOCK))
			{
				spartanAnim->SetAnimation(SpartanAnim::WALK);
			}
		}
		
		if ((spartanAnim->GetAnimation() == SpartanAnim::ATTACK ||
			spartanAnim->GetAnimation() == SpartanAnim::BLOCK))
			velocity = vector2f(0.0f, 0.0f);

		_actor->position += velocity;

		if (_mouseButtonField->Left == ISensor::MouseButtonState::MouseButtonStateDown)
		{
			if (mouseLeftPrevState != _mouseButtonField->Left)
				if (!(spartanAnim->GetAnimation() == SpartanAnim::ATTACK ||
					spartanAnim->GetAnimation() == SpartanAnim::BLOCK))
					spartanAnim->SetAnimation(SpartanAnim::ATTACK);
		}

		if (_mouseButtonField->Right == ISensor::MouseButtonState::MouseButtonStateDown)
		{
				if (!(spartanAnim->GetAnimation() == SpartanAnim::BLOCK ||
					spartanAnim->GetAnimation() == SpartanAnim::ATTACK))
					spartanAnim->SetAnimation(SpartanAnim::BLOCK);
		}
		else if (_mouseButtonField->Right == ISensor::MouseButtonState::MouseButtonStateUp)
		{
			if (mouseRightPrevState != _mouseButtonField->Right)
				if (!(spartanAnim->GetAnimation() == SpartanAnim::IDLE))
					spartanAnim->SetAnimation(SpartanAnim::IDLE);
		}

		mouseLeftPrevState = _mouseButtonField->Left;
		mouseRightPrevState = _mouseButtonField->Right;
	}
};

#endif // __MOVE_HPP__