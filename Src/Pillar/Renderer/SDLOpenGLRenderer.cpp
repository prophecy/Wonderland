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

#include "SDLOpenGLRenderer.h"

#include <GL/glew.h>
#include "../Florist/Florist.h"

void SDLOpenGLRenderer::Create()
{
	// Build up from base class
	SDLRenderer::Create();

	// Init GLEW ( The OpenGL extensions )
	GLenum err = glewInit();

	// Error~
	if (err != GLEW_OK)
		DebugLog("GLEW ERROR: " + ToString(glewGetErrorString(err)));

	// Set GL attribute
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void SDLOpenGLRenderer::Render()
{
	// Set this orthogonal camera for SDL renderer
	glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(
		0,				// Left
		windowWidth,	// Right
		windowHeight,	// Bottom
		0,				// Top
		0,				// Near 
		1);

	// Render SDL stuff
	SDLRenderer::Render();

	// Draw primitive
	glUseProgramObjectARB(0);

	glBegin(GL_QUADS);
	glVertex2f(200.0f, 200.0f);
	glVertex2f(400.0f, 200.0f);
	glVertex2f(400.0f, 400.0f);
	glVertex2f(200.0f, 400.0f);
	glEnd();
}