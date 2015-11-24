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

#include "SilhouetteRenderer.h"
#include "Pillar/SDLGenericLib.h"

#include "Pillar/Foundation/Wonderland/Wonderland.h"
#include "Pillar/Foundation/Portal/Portal.h"
#include "Pillar/WonderLang.h"
#include "Pillar/Configuration.h"
#include "Pillar/Florist/Florist.h"

//Using SDL, SDL OpenGL, GLEW, standard IO, and strings
#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/glu.h>
#include <stdio.h>
#include <string>

using namespace std;

//Graphics program
GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;
GLuint h_uVertexScale = -1;

// GL helper function's prototypes
void printProgramLog(GLuint program);
void printShaderLog(GLuint shader);
string LoadTextFile(string path);
bool InitGL(string vertexShaderPath, string fragmentShaderPath);

GLint myFragColorloc = -1;

f32 g_obj_scale = 1.0;

// Parameter setting functions (Used to interact with core system)
void SilhouetteRenderer::SetParameter(f32 v0)
{
	g_obj_scale = v0;
}

// Wonderland framework
void SilhouetteRenderer::Create()
{
	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Create SDL from base class
	SDLRenderer::Create();

	// Init GLEW ( The OpenGL extensions )
	GLenum err = glewInit();

	// Error~
	if (err != GLEW_OK)
		DebugLog("GLEW ERROR: " + ToString(glewGetErrorString(err)));

	// Very sample shader
	//InitGL("Resource/Shader/sample.vert", "Resource/Shader/sample.frag");

	// Color blend
	InitGL("Resource/Shader/sampleColorBlend.vert", "Resource/Shader/sampleColorBlend.frag");

	// This code works with uniform
// 	myFragColorloc = glGetUniformLocation(gProgramID, "color");
// 	if (myFragColorloc == -1)
// 	{
// 		DebugLog("LVertexPos2D is not a valid glsl program variable!");
// 	}
// 	else
// 	{
// 		float myFloats[4] = { 1.0f, 0.8f, 0.1f, 1.0f };
// 		glProgramUniform4fv(gProgramID, myFragColorloc, 1, myFloats);
// 	}

	h_uVertexScale = glGetUniformLocation(gProgramID, "uVertexScale");

	// Shader with texture (Sampler2D)
	//InitGL("Resource/Shader/texture.vert", "Resource/Shader/texture.frag");
}

void SilhouetteRenderer::Render()	
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Bind program
	glUseProgram(gProgramID);

	//Enable vertex position
	glEnableVertexAttribArray(gVertexPos2DLocation);

	// Manipulate vertex by mouse position
	glUniform1f(h_uVertexScale, g_obj_scale);

	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

	//Disable vertex position
	glDisableVertexAttribArray(gVertexPos2DLocation);

	//Unbind program
	glUseProgram(NULL);

	//Update screen
	SDL_GL_SwapWindow(sdlWindow);
}

void SilhouetteRenderer::Destroy()
{

}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

bool InitGL(string vertexShaderPath, string fragmentShaderPath)
{
	//Success flag
	bool success = true;

	//Generate program
	gProgramID = glCreateProgram();

	//Create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Get vertex shader source
	string vertShadder = LoadTextFile(vertexShaderPath);
	const GLchar* vertexShaderSource = vertShadder.c_str();

	//Set vertex source
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	//Compile vertex source
	glCompileShader(vertexShader);

	//Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE)
	{
		DebugLog("Unable to compile vertex shader " + TO_STR(vertexShader) + "!");
		printShaderLog(vertexShader);
		success = false;
	}
	else
	{
		//Attach vertex shader to program
		glAttachShader(gProgramID, vertexShader);

		//Create fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//Get fragment source
		string fragShadder = LoadTextFile(fragmentShaderPath);
		const GLchar* fragmentShaderSource = fragShadder.c_str();

		//Set fragment source
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

		//Compile fragment source
		glCompileShader(fragmentShader);

		//Check fragment shader for errors
		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
		if (fShaderCompiled != GL_TRUE)
		{
			DebugLog("Unable to compile fragment shader " + TO_STR(fragmentShader) + "!");
			printShaderLog(fragmentShader);
			success = false;
		}
		else
		{
			//Attach fragment shader to program
			glAttachShader(gProgramID, fragmentShader);


			//Link program
			glLinkProgram(gProgramID);

			//Check for errors
			GLint programSuccess = GL_TRUE;
			glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
			if (programSuccess != GL_TRUE)
			{
				DebugLog("Error linking program " + TO_STR(gProgramID) + "!");
				printProgramLog(gProgramID);
				success = false;
			}
			else
			{
				//Get vertex attribute location
				gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");
				if (gVertexPos2DLocation == -1)
				{
					DebugLog("LVertexPos2D is not a valid glsl program variable!");
					success = false;
				}
				else
				{
					//Initialize clear color
					glClearColor(0.f, 0.f, 0.f, 1.f);

					//VBO data
					GLfloat vertexData[] =
					{
						-0.5f, -0.5f,
						0.5f, -0.5f,
						0.5f,  0.5f,
						-0.5f,  0.5f
					};

					//IBO data
					GLuint indexData[] = { 0, 1, 2, 3 };

					//Create VBO
					glGenBuffers(1, &gVBO);
					glBindBuffer(GL_ARRAY_BUFFER, gVBO);
					glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

					//Create IBO
					glGenBuffers(1, &gIBO);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
				}
			}
		}
	}

	return success;
}

// ---------------------------------------------------------------------------
//Shader loading utility programs
void printProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			DebugLog(infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		DebugLog("Name " + TO_STR(program) + " is not a program");
	}
}

void printShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			DebugLog(infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		DebugLog("Name " + TO_STR(shader) + " is not a shader");
	}
}

string LoadTextFile(string path)
{
	// String to store content
	char* document = NULL;

	// Load JSON from file
	SDL_RWops* file = SDL_RWFromFile(path.c_str(), "r");

	Sint64 sz = file->size(file) + 1;

	if (file != NULL)
	{
		// Allocate buffer
		document = (char*)malloc((size_t)sz);
		memset(document, 0x0, sz);

		// Read
		if (SDL_RWread(file, document, (size_t)sz, 1) > 0)
		{
			DebugLog("Read JSON from: " + path + " has been finished");
		}

		// Close file
		SDL_RWclose(file);
	}

	// Copy it to string
	string outDocument = document;

	// Free document
	free(document);
	document = NULL;

	return outDocument;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------