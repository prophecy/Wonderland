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

#include "Canvas.h"
#include "../Foundation/Portal/Portal.h"

void Canvas::SetupParameter(const size2f* canvasSize, 
							const size2f* screenSize, 
							CanvasMode mode)
{
	_canvasSize	= *canvasSize;
	_screenSize	= *screenSize;

	if ( mode == CanvasMode::CanvasModeAspectFit ||
		mode == CanvasMode::CanvasModeAspectFill)
	{
		_SetupParametersForAspect(canvasSize, screenSize, mode);
	}
	else
	{
		_SetupParametersForStretch(canvasSize, screenSize);
	}
}

const point2f	Canvas::GetScreenPointFromCanvasPoint(const point2f* canvasPoint)
{
	return _canvasOriginOnScreenSpace + _canvasSizeOnScreenSpace;
}

const point2f	Canvas::GetCanvasPointFromScreenPoint(const point2f* screenPoint)
{
	point2f screenPointDif	= *screenPoint - _canvasOriginOnScreenSpace;
	point2f pointOut;
	pointOut.data()[0]	= screenPointDif.data()[0] / _scaleOnScreenSpace[0];
	pointOut.data()[1]	= screenPointDif.data()[1] / _scaleOnScreenSpace[1];
	return pointOut;
}

const size2f Canvas::GetScreenSize()
{
	return _screenSize;
}

const size2f Canvas::GetCanvasSize()
{
	return _canvasSize;
}

const rect2f Canvas::GetCanvasRect()
{
	rect2f canvasRect;
	canvasRect.origin	= _canvasOriginOnScreenSpace;
	canvasRect.size		= _canvasSize;
	return canvasRect;
}

const rect2f Canvas::GetCanvasRectOnScreenSpace()
{
	rect2f rectOut;
	rectOut.origin	= _canvasOriginOnScreenSpace;
	rectOut.size	= _canvasSizeOnScreenSpace;
	return rectOut;
}

const size2f Canvas::GetScaleOnScreenSpace()
{
	return _scaleOnScreenSpace;
}

void Canvas::_SetupParametersForStretch(const size2f* canvasSize, const size2f* screenSize)
{
	// Calculate canvas parameters
	_canvasOriginOnScreenSpace.set(0,0);
	_canvasSizeOnScreenSpace	= *screenSize;
	_scaleOnScreenSpace.data()[0] =  screenSize->data()[0] / canvasSize->data()[0];
	_scaleOnScreenSpace.data()[1] =  screenSize->data()[1] / canvasSize->data()[1];

	// Write log
	Log* log	= Portal::GetPtr()->GetLog();
	log->DebugLog("_SetupParametersForStretch.FINISH");
	_WriteLog(canvasSize, screenSize, 
			&_canvasOriginOnScreenSpace, 
			&_canvasSizeOnScreenSpace,
			&_scaleOnScreenSpace);
}


void Canvas::_SetupParametersForAspect(	const size2f* canvasSize, const size2f* screenSize,
										CanvasMode mode)
{
	// Ratio
	f32 ratioScreen	= screenSize->data()[0] / screenSize->data()[1];
	f32 ratioCanvas	= canvasSize->data()[0] / canvasSize->data()[1];

	// Initialize i and j
	u32 i;
	u32 j;

	// Check for fitting width
	if ( ( ratioCanvas > ratioScreen && mode == CanvasMode::CanvasModeAspectFit ) ||
		 ( ratioCanvas <= ratioScreen && mode == CanvasMode::CanvasModeAspectFill ) )
	{
		i	= 0;
		j	= 1;
	}
	else
	{
		i	= 1;
		j	= 0;
	}

	// Calculate canvas parameters
	_canvasOriginOnScreenSpace.data()[i]	= 0;
	_canvasSizeOnScreenSpace.data()[i]		= screenSize->data()[i];
	_scaleOnScreenSpace[i]	= screenSize->data()[i] / canvasSize->data()[i];
	_scaleOnScreenSpace[j]	= _scaleOnScreenSpace[i];
	_canvasSizeOnScreenSpace.data()[j]		= canvasSize->data()[j] * _scaleOnScreenSpace[j];
	_canvasOriginOnScreenSpace.data()[j]	= ( screenSize->data()[j] - _canvasSizeOnScreenSpace.data()[j] ) * 0.5f;
	
	// Write log
	Log* log	= Portal::GetPtr()->GetLog();
	std::string modeName	= mode == CanvasMode::CanvasModeAspectFill ? "AspectFill" : "AspectFit";
	log->DebugLog("_SetupParametersForAspect." + modeName APPEND_STR(".FINISH"));
	_WriteLog(canvasSize, screenSize, 
			&_canvasOriginOnScreenSpace, 
			&_canvasSizeOnScreenSpace,
			&_scaleOnScreenSpace);
}

size2f Canvas::_InverseSize(size2f size)
{
	size2f sizeOut;
	sizeOut.data()[0]	= size.data()[1];
	sizeOut.data()[1]	= size.data()[0];
	return sizeOut;
}

void Canvas::_WriteLog(	const size2f* canvasSize, const size2f* screenSize,
						const size2f* canvasOriginOnScreenSpace,
						const size2f* canvasSizeOnScreenSpace,
						const size2f* scaleOnScreenSpace)
{
	Log* log	= Portal::GetPtr()->GetLog();
	log->DebugLog("canvasSize: "
					APPEND_STR(TO_STR(canvasSize->data()[0]))
					APPEND_STR(",")
					APPEND_STR(TO_STR(canvasSize->data()[1]))
					);
	log->DebugLog("screenSize: "
					APPEND_STR(TO_STR(screenSize->data()[0]))
					APPEND_STR(",")
					APPEND_STR(TO_STR(screenSize->data()[1]))
					);
	log->DebugLog("_canvasOriginOnScreenSpace: "
					APPEND_STR(TO_STR(canvasOriginOnScreenSpace->data()[0]))
					APPEND_STR(",")
					APPEND_STR(TO_STR(canvasOriginOnScreenSpace->data()[1]))
					);
	log->DebugLog("_canvasSizeOnScreenSpace: "
				APPEND_STR(TO_STR(canvasSizeOnScreenSpace->data()[0]))
				APPEND_STR(",")
				APPEND_STR(TO_STR(canvasSizeOnScreenSpace->data()[1]))
				);
	log->DebugLog("_scaleOnScreenSpace: "
				APPEND_STR(TO_STR(scaleOnScreenSpace->data()[0]))
				APPEND_STR(",")
				APPEND_STR(TO_STR(scaleOnScreenSpace->data()[1]))
				);
}