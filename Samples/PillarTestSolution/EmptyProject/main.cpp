// EmptyProject.cpp : Defines the entry point for the console application.
//

#include "ISceneManager.h"
#include "ITaskManager.h"
#include "IApplication.h"
#include "Utility/Factory.h"
#include "IScene.h"
#include "Utility/Time/Timer.h"

#include "PillarPlugin.h"

#include "WonderApp.h"

#undef main

int main(int argc, char* argv[])
{
	// Create application
	WonderPtr<WonderApp> application;
	application.Alloc();

	// Create Pillar plugin
	WonderPtr<PillarPlugin> pillarPlugin;
	pillarPlugin.Alloc();
	pillarPlugin->Create(application);

	return 0;
}

