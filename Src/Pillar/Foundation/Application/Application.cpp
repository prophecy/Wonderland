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

#include "../Application/Application.h"
#include "../Wonderland/Wonderland.h"
#include "../IScene.h"

Application::Application()
{

}

void Application::Create()
{
	// Build Wonderland up here
	// If Resource tasks are run here, wait until those tasks are finished before run Start
	// **** This function cannot guarantee that everything is ready to rock!
	WonderPtr<SceneManager> sMgr = CreateElement<SceneManager>();

	sceneManager = sMgr;
	specificApplication->sceneManager = sceneManager;

	// Redirect
	specificApplication->Create();

	specificApplication->sceneManager->GetCurrentScene()->Create();
}

void Application::Destroy()
{
	// Redirect
	specificApplication->Destroy();

	// Naah, Destroy Everything
	sceneManager.Destroy();
}

void Application::Start()
{
	// Start everything after "Build everything up"
	// This is a safe place to start TaskUpdate, Or any logic module

	// Create Entities

	// Create Tasks

	// Create Scene

	// Redirect
	specificApplication->Start();

}

void Application::Stop()
{
	// This wonder world is stop because of this function

	// Redirect
	specificApplication->Stop();

}

void Application::Resume()
{
	// If resume, every tasks will run
	// If already resumed, don't call this again

	// Redirect
	specificApplication->Resume();
}

void Application::Pause()
{
	// If pause, every tasks will stop
	// If already stopped, don't call this again

	// Redirect
	specificApplication->Pause();

}