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

void SilhouetteRenderer::Create()	
{
	//-----------------------------------------------------------------------------------------------
	// Create window
	SDL_Init(SDL_INIT_VIDEO);
	sdlWindow = SDL_CreateWindow(
		"Wonderland",
		20, 20, windowWidth, windowHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	// Create GL context for SDL
	SDL_GLContext glcontext = SDL_GL_CreateContext(sdlWindow);

	// Search to get "opengl" driver
	int oglIdx = -1;
	int nRD = SDL_GetNumRenderDrivers();

	for (int i = 0; i < nRD; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
		{
			if (!strcmp(info.name, "opengl"))
			{
				oglIdx = i;
			}
		}
	}

	// Create SDL renderer ( OpenGL )
	sdlRenderer = SDL_CreateRenderer(
		sdlWindow, oglIdx,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

}

void SilhouetteRenderer::Render()	
{
	// Draw background with solid color
	u8* canvasColor = Configuration::GetPtr()->GetCanvasColor();
	SDL_SetRenderDrawColor(sdlRenderer, canvasColor[0], canvasColor[1], canvasColor[2], canvasColor[3]);
	SDL_RenderClear(sdlRenderer);

	// Batch render
	BatchRender();

	// Update the screen!
	SDL_RenderPresent(sdlRenderer);
}

void SilhouetteRenderer::BatchRender()
{
	// Draw from batch
	for (u32 i = 0; i < Wonderlang::renderBatch.size(); ++i)
	{
		ImageEntity* entImg = Wonderlang::renderBatch[i];

		if (!entImg->isVisible)
			continue;

		// Get canvas
		Canvas* canvas = Portal::GetPtr()->GetCanvas();

		// Get canvas rect
		const rect2f canvasRect = canvas->GetCanvasRectOnScreenSpace();
		const size2f canvasScale = canvas->GetScaleOnScreenSpace();

		// Calculate dest image
		rect2f destImg;
		destImg.origin.set((f32)canvasRect.origin.data()[0] +
			entImg->position.data()[0] * canvasScale.data()[0] -
			entImg->pivot.data()[0] * canvasScale.data()[0],
			(f32)canvasRect.origin.data()[1] +
			(f32)canvasRect.size.data()[1] -
			entImg->position.data()[1] * canvasScale.data()[1] -
			entImg->pivot.data()[1] * canvasScale.data()[1]
			);

		// Apply alpha
		Uint8 alpha = (Uint8)(255.0f * entImg->alpha);
		SDL_SetTextureAlphaMod(entImg->sprite.texture, alpha);

		// Blit sprite onto screen

		// Render if type is image sprite
		if (entImg->rttiPtr == &ImageFontEntity::rtti ||
			entImg->rttiPtr == &ImageSpriteEntity::rtti ||
			entImg->rttiPtr == &ImageAtlasEntity::rtti)
		{
			ImageSpriteEntity* imgSprite = (ImageSpriteEntity*)entImg;

			SDL_Rect srcRect;
			srcRect.x = (s32)imgSprite->spriteRectCurrent.origin.data()[0];
			srcRect.y = (s32)imgSprite->spriteRectCurrent.origin.data()[1];
			srcRect.w = (s32)imgSprite->spriteRectCurrent.size.data()[0];
			srcRect.h = (s32)imgSprite->spriteRectCurrent.size.data()[1];

			destImg.size.set(
				imgSprite->spriteRectCurrent.size.data()[0] * entImg->scale * canvasScale[0],
				imgSprite->spriteRectCurrent.size.data()[1] * entImg->scale * canvasScale[1]
				);

			// Copy to SDL_Rect
			SDL_Rect destRect;
			destRect.x = (s32)destImg.origin.data()[0];
			destRect.y = (s32)destImg.origin.data()[1];
			destRect.w = (s32)destImg.size.data()[0];
			destRect.h = (s32)destImg.size.data()[1];

			// Render
			SDL_Point center;
			center.x = (int)(entImg->pivot.data()[0] * canvasScale.data()[0]);
			center.y = (int)(entImg->pivot.data()[1] * canvasScale.data()[1]);
			SDL_RendererFlip flip = (SDL_RendererFlip)entImg->flip;

			SDL_RenderCopyEx(sdlRenderer,
				entImg->sprite.texture,
				&srcRect,
				&destRect,
				entImg->radian * 180.0f / PI,
				&center,
				flip);
		}
		else if (entImg->rttiPtr == &ImageEntity::rtti)
		{
			destImg.size.set((f32)entImg->sprite.w * entImg->scale * canvasScale[0],
				(f32)entImg->sprite.h * entImg->scale * canvasScale[1]);

			// Copy to SDL_Rect
			SDL_Rect destRect;
			destRect.x = (s32)destImg.origin.data()[0];
			destRect.y = (s32)destImg.origin.data()[1];
			destRect.w = (s32)destImg.size.data()[0];
			destRect.h = (s32)destImg.size.data()[1];


			// Render
			SDL_Point center;
			center.x = (int)(entImg->pivot.data()[0] * canvasScale.data()[0]);
			center.y = (int)(entImg->pivot.data()[1] * canvasScale.data()[1]);
			SDL_RendererFlip flip = (SDL_RendererFlip)entImg->flip;

			SDL_RenderCopyEx(sdlRenderer,
				entImg->sprite.texture,
				NULL,
				&destRect,
				entImg->radian * 180.0f / PI,
				&center,
				flip);

			SDL_RenderCopy(sdlRenderer, entImg->sprite.texture, NULL, &destRect);
		}
		else
		{
			Portal::GetPtr()->GetLog()->DebugLog("Does not support with Codename: " + ImageEntity::rtti.codeName);
		}
	}

	// todo: in aspect fit mode, clip canvas
}

void SilhouetteRenderer::Destroy()
{

}
