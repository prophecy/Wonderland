#ifndef __SCENE_WELCOME_HPP_
#define __SCENE_WELCOME_HPP_

#include "../AppInclude.h"
#include "../Task/Move.hpp"
#include "../Task/SpartanAnim.hpp"

class SceneWelcome : public IScene
{
	virtual void Create()
	{
		WonderPtr<ImageEntity> tileImage = CreateElement<ImageEntity>();
		tileImage->LoadImage("Resource/Image/DemoTileGreen.png");
		tileImage->pivot = point2f(0.0f, 72.0f);
		tileImage->position = point2f(300.0f, 300.0f);
		AddEntity(tileImage);
	}

	virtual void Destroy() { }

	virtual void Start() { }

	virtual void Stop() { }

	virtual void Resume() { }

	virtual void Pause() { }

};


#endif // __SCENE_MAIN_MENU_H__