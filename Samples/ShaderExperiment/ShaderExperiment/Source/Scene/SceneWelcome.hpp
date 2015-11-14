#ifndef __SCENE_WELCOME_HPP_
#define __SCENE_WELCOME_HPP_

#include "../AppInclude.h"
#include "../Task/Move.hpp"
#include "../Task/SpartanAnim.hpp"

class SceneWelcome : public IScene
{
	virtual void Create()
	{
		CreateDemoTile();
		CreateSpartan();
	}

	void CreateDemoTile()
	{
		size2s size;
		size.data()[0] = 27;
		size.data()[1] = 15;

		for (int i = 0; i < size.data()[0]; ++i)
		{
			for (int j = 0; j < size.data()[1]; ++j)
			{
				WonderPtr<ImageEntity> tileImage = CreateElement<ImageEntity>();
				tileImage->LoadImage("Resource/DemoTileGreen.png");
				tileImage->pivot = point2f(0.0f, 72.0f);
				tileImage->position = point2f(72.0f * i, 72.0f * j);
				AddEntity(tileImage);
			}
		}
	}

	WonderPtr<ImageAtlasEntity> spartanImage;

	void CreateSpartan()
	{
		spartanImage = CreateElement<ImageAtlasEntity>();
		spartanImage->LoadImage("Resource/Character/Spartans.png");
		spartanImage->LoadJsonDataFormat("Resource/Character/Spartans.json");
		spartanImage->pivot = point2f(0.0f, 0.0f);
		spartanImage->position = point2f(300.0f, 300.0f);

		WonderPtr<SpartanAnim> anim = CreateElement<SpartanAnim>();
		spartanImage->BindTask(anim);
		WonderPtr<Move> move = CreateElement<Move>();
		move->spartanAnim = anim;
		spartanImage->BindTask(move);

		AddEntity(spartanImage);
	}

	virtual void Destroy() { }

	virtual void Start() { }

	virtual void Stop() { }

	virtual void Resume() { }

	virtual void Pause() { }

};


#endif // __SCENE_MAIN_MENU_H__