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
GLuint h_uColorScale = -1;

GLuint h_texUnit0;
GLuint h_aTexCoord;
GLuint h_aColor;

GLuint texVbo = -1;
GLuint colVbo = -1;

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

	InitGL("Resource/Shader/texture.vert", "Resource/Shader/texture.frag");

	h_uColorScale = glGetUniformLocation(gProgramID, "uColorScale");

	// Texture (Sampler2D)
	SDL_Surface *surface;
	
	if ((surface = IMG_Load("Resource/Image/SpartanShield.png")))
	{
		GLuint h_texture = -1;

		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &h_texture);
		glBindTexture(GL_TEXTURE_2D, h_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			surface->pixels);

		h_texUnit0 = glGetUniformLocation(gProgramID, "texUnit0");
		h_aTexCoord = glGetAttribLocation(gProgramID, "aTexCoord");
		h_aColor = glGetAttribLocation(gProgramID, "aColor");

		// Create texture VBO
		GLfloat sqTex[8] =
		{
			0, 1,
			1, 1,
			1, 0,
			0, 0,
		};

		glGenBuffers(1, &texVbo);
		glBindBuffer(GL_ARRAY_BUFFER, texVbo);
 		glBufferData(
 			GL_ARRAY_BUFFER,
 			8 * sizeof(GLfloat),
 			sqTex,
 			GL_STATIC_DRAW);

		// Create color VBO
		static GLfloat sqCol[12] = {
			1, 0, 0,
			0, 1, 1,
			0, 0, 1,
			1, 0, 0,
		};

		glGenBuffers(1, &colVbo);
		glBindBuffer(GL_ARRAY_BUFFER, colVbo);
		glBufferData(
			GL_ARRAY_BUFFER,
			12 * sizeof(GLfloat),
			sqCol,
 			GL_STATIC_DRAW);
	}
	else
	{
		DebugLog("Texture file not found!");
	}
}

void SilhouetteRenderer::Render()	
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Bind program
	glUseProgram(gProgramID);
	
	//Enable
	glEnableVertexAttribArray(gVertexPos2DLocation);
	glEnableVertexAttribArray(h_aTexCoord);
	glEnableVertexAttribArray(h_aColor);
	glEnable(GL_BLEND);

	// Blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	// Manipulate vertex by mouse button
	glUniform1f(h_uColorScale, g_obj_scale);

	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);

	// Texture
	glBindBuffer(GL_ARRAY_BUFFER, texVbo);
	glVertexAttribPointer(h_aTexCoord,
		2, GL_FLOAT, GL_FALSE, 0, 0);

	// Color
	glBindBuffer(GL_ARRAY_BUFFER, colVbo);
	glVertexAttribPointer(h_aColor,
	 	3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

	//Disable
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(h_aColor);
	glDisableVertexAttribArray(h_aTexCoord);
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
				gVertexPos2DLocation = glGetAttribLocation(gProgramID, "aVertex");
				if (gVertexPos2DLocation == -1)
				{
					DebugLog("aVertex is not a valid glsl program variable!");
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