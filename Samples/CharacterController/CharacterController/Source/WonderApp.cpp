#include "WonderApp.h"

#include "Scene/SceneWelcome.hpp"

void WonderApp::Create()
{
	WonderPtr<SceneWelcome> sceneWelcome = CreateElement<SceneWelcome>();

	// Add scenes
	sceneManager->SetNextScene(sceneManager->AddScene(sceneWelcome));
}

void WonderApp::Destroy()
{
	DebugLog("WonderApp TearDown()");
}

void WonderApp::Start()
{
	DebugLog("WonderApp Start()");
}

void WonderApp::Stop()
{
	DebugLog("WonderApp Stop()");
}

void WonderApp::Resume()
{
	DebugLog("WonderApp Resume()");
}

void WonderApp::Pause()
{
	DebugLog("WonderApp Pause()");
}