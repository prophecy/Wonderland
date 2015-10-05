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

#include "LibRocketFacade.h"

#include <GL/glew.h>

#include "../../SDLGenericLib.h"
#include "../../Florist/Florist.h"

#include "shell/include/ShellFileInterface.h"
#include "SystemInterfaceSDL2.h"
#include "RenderInterfaceSDL2.h"

LibRocketFacade* LibRocketFacade::s_instance = NULL;

void LibRocketFacade::Create()
{
	s_instance = this;
}

void LibRocketFacade::BuildOpenGL()
{
	// Init GLEW ( The OpenGL extensions )
	GLenum err = glewInit();

	// Error~
	if (err != GLEW_OK)
		DebugLog("GLEW ERROR: " + ToString(glewGetErrorString(err)));

	// Set GL attribute
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void LibRocketFacade::BuildLibRocketComponent(SDL_Renderer* sdlRenderer, SDL_Window* sdlWindow,
	s32 windowWidth, s32 windowHeight)
{
	// Cache width & height, these vars are necessary with rendering system
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	// Init libRocket
	rocketSdlRenderer = new RocketSDL2Renderer(sdlRenderer, sdlWindow);
	rocketSystemInterface = new RocketSDL2SystemInterface();
	rocketFileInterface = new ShellFileInterface("");

	Rocket::Core::SetFileInterface(rocketFileInterface);
	Rocket::Core::SetRenderInterface(rocketSdlRenderer);
	Rocket::Core::SetSystemInterface(rocketSystemInterface);

	if (!Rocket::Core::Initialise())
	{
		DebugLog("LibRocket initialization failure!");
		return;
	}

	rocketContext = Rocket::Core::CreateContext("default",
		Rocket::Core::Vector2i(windowWidth, windowHeight));

	Rocket::Debugger::Initialise(rocketContext);
}

void LibRocketFacade::BuildFoundationResource()
{
	bool isLoadSuccess = false;

	isLoadSuccess = Rocket::Core::FontDatabase::LoadFontFace("Resource/Shared/LibRocket/Font/Delicious-Bold.otf");
	isLoadSuccess = Rocket::Core::FontDatabase::LoadFontFace("Resource/Shared/LibRocket/Font/Delicious-BoldItalic.otf");
	isLoadSuccess = Rocket::Core::FontDatabase::LoadFontFace("Resource/Shared/LibRocket/Font/Delicious-Italic.otf");
	isLoadSuccess = Rocket::Core::FontDatabase::LoadFontFace("Resource/Shared/LibRocket/Font/Delicious-Roman.otf");
}

void LibRocketFacade::Update()
{
	rocketContext->Update();
}

void LibRocketFacade::Render()
{
	// Set this orthogonal camera for LibRocket renderer ( to make it's not equal, such a UI region )
	glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(
		0,				// Left
		windowWidth,	// Right
		windowHeight,	// Bottom
		0,				// Top
		0,				// Near 
		1);				// Far

	rocketContext->Render(); // Render lib rocket things
}

void LibRocketFacade::OnEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_QUIT:
		break;

	case SDL_MOUSEMOTION:
		rocketContext->ProcessMouseMove(event.motion.x, event.motion.y, rocketSystemInterface->GetKeyModifiers());
		break;
	case SDL_MOUSEBUTTONDOWN:
		rocketContext->ProcessMouseButtonDown(rocketSystemInterface->TranslateMouseButton(event.button.button), rocketSystemInterface->GetKeyModifiers());
		break;

	case SDL_MOUSEBUTTONUP:
		rocketContext->ProcessMouseButtonUp(rocketSystemInterface->TranslateMouseButton(event.button.button), rocketSystemInterface->GetKeyModifiers());
		break;

	case SDL_MOUSEWHEEL:
		rocketContext->ProcessMouseWheel(event.wheel.y, rocketSystemInterface->GetKeyModifiers());
		break;

	case SDL_KEYDOWN:
	{
		// Intercept SHIFT + ~ key stroke to toggle libRocket's 
		// visual debugger tool
		if (event.key.keysym.sym == SDLK_BACKQUOTE &&
			event.key.keysym.mod == KMOD_LSHIFT)
		{
			Rocket::Debugger::SetVisible(!Rocket::Debugger::IsVisible());
			break;
		}

		rocketContext->ProcessKeyDown(rocketSystemInterface->TranslateKey(event.key.keysym.sym), rocketSystemInterface->GetKeyModifiers());
		break;
	}

	default:
		break;
	}
}

void LibRocketFacade::Destroy()
{
	/* // Todo: Investigate this due to can delete my created objects
	delete rocketSystemInterface;
	delete rocketFileInterface;
	delete rocketSdlRenderer;

	rocketSdlRenderer = NULL;
	rocketSystemInterface = NULL;
	rocketFileInterface = NULL;
	*/
}
