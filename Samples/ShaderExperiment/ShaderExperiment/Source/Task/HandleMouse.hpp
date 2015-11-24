#ifndef __HANDLE_MOUSE_HPP__
#define __HANDLE_MOUSE_HPP__

#include "../AppInclude.h"
#include "../Renderer/SilhouetteRenderer.h"

class HandleMouse : public TaskUpdate
{
	virtual void Start()
	{
	}

	float v = 1.0f;
	ISensor::MouseButtonState prevState = ISensor::MouseButtonStateNone;

	virtual void OnTask()
	{
		ISensor::MouseButtonField* mouseButtonField = SilkRoad::GetPtr()->GetSensor()->GetMouseButtonField();

		if (mouseButtonField->Left == ISensor::MouseButtonState::MouseButtonStateDown &&
			mouseButtonField->Left != prevState)
		{
			v = (v == 1.0f) ? 0.5f : 1.0f;
			SilhouetteRenderer::SetParameter(v);
		}
		
		prevState = mouseButtonField->Left;
	}
};

#endif // __HANDLE_MOUSE_HPP__