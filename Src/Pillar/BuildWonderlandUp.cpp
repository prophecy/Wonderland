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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Library/Library.h"
#include "SDLGenericLib.h"

// Generic implementation
#include "Foundation/Wonderland/Wonderland.h"
#include "Foundation/Application/Application.h"
#include "Foundation/RunLoop/RunLoop.h"
#include "Foundation/Portal/Portal.h"
#include "Foundation/Timer/Timer.h"

#include "Renderer/Renderer.h"
#include "Renderer/SDLLibRocketRenderer.h"

#include "Configuration.h"
#include "Canvas/Canvas.h"
#include "SilkRoad/SilkRoad.h"
#include "WonderLang.h"

// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------

#if WONDERLAND_ACTIVE_PLATFORM == WONDERLAND_PLATFORM_WINDOWS
	static const f32 _s_canvasScale	=  0.5f;
#else
	static const f32 _s_canvasScale	=  1.0f;
#endif // WONDERLAND_ACTIVE_PLATFORM == WONDERLAND_PLATFORM_WINDOWS

// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------

int BuildWonderlandUp(int argc, char *argv[], IApplication* specificApplication)
{
	// ---------------------------------------------------------------------------------------
	Memory::Create();
	Portal::Create();

	Log* log	= Portal::GetPtr()->GetLog();
	log->DebugLog("main.START");

	u32 initMemCounter	= Memory::GetPtr()->GetMemoryCounter();
	log->DebugLog("Memory counter: " + TO_STR(initMemCounter));

	// Setup configuration
	size2f canvasSize	= Configuration::GetPtr()->GetCanvasSize();

	// ---------------------------------------------------------------------------------------
	// Init Wonderland
	Wonderland wonderland;
	Application application; // Application is for contain
	RunLoop runLoop; // RunLoop is for active
	application.specificApplication = specificApplication;
	wonderland.SetApplication(&application);
	wonderland.SetRunLoop(&runLoop);

	// ---------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------
	// Init renderer
	// This has some dirty casting ( The code won't work if renderer is not inherit form SDL )

	// Set renderer from type
	Configuration::Renderertype rendererType = Configuration::GetPtr()->GetRendererType();
	SDLRenderer* renderer;

	// Set renderer from type
	if (rendererType != Configuration::Renderertype::RENDERER_TYPE_USER_DEFINED)
		renderer = (SDLRenderer*)RendererSetting::CreateRenderer(rendererType);
	// Set renderer from user defined one
	else
		renderer = (SDLRenderer*)RendererSetting::CreateRenderer(Configuration::GetPtr()->GetUserDefinedRenderer());

	// ---------------------------------------------------------------------------------------
	// Init SDL renderer
	renderer->windowWidth = (s32)(canvasSize.data()[0] * _s_canvasScale);
	renderer->windowHeight = (s32)(canvasSize.data()[1] * _s_canvasScale);
	renderer->Create();
	
	// Get reference vars from renderer
	SDL_Window *sdlWindow = renderer->sdlWindow;
	SDL_Renderer *sdlRenderer = renderer->sdlRenderer;

	// ---------------------------------------------------------------------------------------
	// Set screen size to canvas system
	int windowWidth		= 0;
	int windowHeight	= 0;
	SDL_GetWindowSize(sdlWindow, &windowWidth, &windowHeight);
	size2f screenSize;
	screenSize.set((f32)windowWidth, (f32)windowHeight);
	Configuration::GetPtr()->SetScreenSize(&screenSize);

	RendererSetting::s_SDLRenderer = sdlRenderer;
	RendererSetting::s_window = sdlWindow;

	// Get canvas
	Canvas* canvas	= Portal::GetPtr()->GetCanvas();

	// Setup canvas
	canvas->SetupParameter(	&canvasSize,
							&screenSize,
							Configuration::GetPtr()->GetCanvasMode());
	
	// ---------------------------------------------------------------------------------------
	// Set renderer to SDLGenericLib
	SDLGenericLib::SetRenderer(sdlRenderer);
	
	// ---------------------------------------------------------------------------------------
	// Build Wonderland up
	wonderland.Create();

	// ---------------------------------------------------------------------------------------
	// Build Silkroad up
	SilkRoad::Create();
	SilkRoad* silkRoad	= SilkRoad::GetPtr();
	silkRoad->BuildUp();

	// ---------------------------------------------------------------------------------------
	// Invoke application to start
	application.Start();

	// ---------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------
	// Main render loop
	Uint8 done = 0;
	SDL_Event event;
	while(!done)
	{
		// Set time
		Timer::Update();

		// Start poll event
		silkRoad->PollEventStart();

		// Check for events
		while(SDL_PollEvent(&event))
		{
			if(	event.type == SDL_QUIT || 
				( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE ))
			{
				done = 1;
			}

			// Todo: Remove this~
			if (Configuration::GetPtr()->GetRendererType() == Configuration::RENDERER_TYPE_SDL_LIBROCKET)
				((SDLLibRocketRenderer*)renderer)->BypassEvent(event);

			silkRoad->PollEventUpdate(&event);
		}

		silkRoad->PollEventFinish();

		// Draw background with solid color
		u8* canvasColor = Configuration::GetPtr()->GetCanvasColor();
		SDL_SetRenderDrawColor(sdlRenderer, canvasColor[0], canvasColor[1], canvasColor[2], canvasColor[3]);
		SDL_RenderClear(sdlRenderer);
		
		// Update resource ( Should be in sub thread )
		runLoop.OnUpdateResourceThread();

		// Update application state
		ISensor::AppStateField* appStateField = silkRoad->GetPtr()->GetSensor()->GetAppStateField();

		if ( appStateField->IsOnState(ISensor::AppState::AppStateResume) )
			application.Resume();
		if ( appStateField->IsOnState(ISensor::AppState::AppStatePause) )
			application.Pause();

		// Update runloop!
		runLoop.OnUpdate();

		// Render things
		runLoop.OnRender();

		// Batch render
		renderer->Render();

		// Update the screen!
		SDL_RenderPresent(sdlRenderer);
	}
	// ---------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------

	// ---------------------------------------------------------------------------------------
	// Invoke application ( Stopping event )
	application.Stop();

	log->DebugLog("main.FINISH");

	// ---------------------------------------------------------------------------------------
	// Tear down renderer
	RendererSetting::Destroy();

	// ---------------------------------------------------------------------------------------
	// Tear down silk road
	silkRoad->TearDown();
	silkRoad->Destroy();
	
	// ---------------------------------------------------------------------------------------
	// Tear Wonderland down
	wonderland.Destroy();

	// ---------------------------------------------------------------------------------------
	// Release all memory
	u32 finalMemCounter	= Memory::GetPtr()->GetMemoryCounter();
	log->DebugLog ("Memory counter: " + TO_STR(finalMemCounter));
	if ( finalMemCounter > 0 )
	{
		log->DebugLog("memory leak!");
		Portal::Destroy();
		Memory::GetPtr()->FreeAll();		
	}
	else
	{
		Portal::Destroy();
	}
	Memory::Destroy();

	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
	IMG_Quit();
	SDL_Quit();

	// ---------------------------------------------------------------------------------------
#if WONDERLAND_ACTIVE_PLATFORM == WONDERLAND_PLATFORM_WINDOWS
	// Need this line in development mode
	Sleep(400);
#endif

	exit(0);

	// ---------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------
}