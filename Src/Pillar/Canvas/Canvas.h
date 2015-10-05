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

#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "../Library/Library.h"
#include "CanvasMode.h"

class Configuration;

class Canvas
{
public:

	void	SetupParameter(	const size2f* canvasSize, 
							const size2f* screenSize, 
							CanvasMode mode);
	const point2f	GetScreenPointFromCanvasPoint(const point2f* canvasPoint);
	const point2f	GetCanvasPointFromScreenPoint(const point2f* screenPoint);
	const size2f	GetScreenSize();
	const size2f	GetCanvasSize();
	const rect2f	GetCanvasRect();
	const rect2f	GetCanvasRectOnScreenSpace();
	const size2f	GetScaleOnScreenSpace();

private:
	void	_SetupParametersForStretch(const size2f* canvasSize, const size2f* screenSize);
	void	_SetupParametersForAspect(	const size2f* canvasSize, const size2f* screenSize,
										CanvasMode mode);
	size2f	_InverseSize(size2f size);
	void	_WriteLog(	const size2f* canvasSize, const size2f* screenSize,
						const size2f* canvasOriginOnScreenSpace,
						const size2f* canvasSizeOnScreenSpace,
						const size2f* scaleOnScreenSpace);
private:
	size2f		_canvasSize;
	size2f		_screenSize;
	point2f		_canvasOriginOnScreenSpace;
	size2f		_canvasSizeOnScreenSpace;
	size2f		_scaleOnScreenSpace;
};

#endif // __CANVAS_H__