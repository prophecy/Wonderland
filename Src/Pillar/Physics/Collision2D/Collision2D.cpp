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

#include "Collision2D.h"
#include "../../Library/Library.h"

bool Collision2D::IsCollid(	ColliderSphere sphereA, 
							ColliderSphere sphereB	)
{
	vector2f deltaPoint	= sphereA.position - sphereB.position;
	f32 radiousSum	= sphereA.radious + sphereB.radious;

	if (std::sqrt(	deltaPoint.data()[0] * deltaPoint.data()[0] + 
					deltaPoint.data()[1] * deltaPoint.data()[1] ) > radiousSum )
		return false;

	return true;
}

bool Collision2D::IsCollid(	ColliderBoundingBox boundingBoxA, 
							ColliderBoundingBox boundingBoxB	)
{
	vector2f boxASize	= ( boundingBoxA.pointB - boundingBoxA.pointA ) / 2;
	vector2f boxACenter	= ( boundingBoxA.pointA + boundingBoxA.pointB ) / 2;
	vector2f boxBSize	= ( boundingBoxB.pointB - boundingBoxB.pointA ) / 2;
	vector2f boxBCenter	= ( boundingBoxB.pointA + boundingBoxB.pointB ) / 2;

	// If length.x > width
	if (	abs ( boxACenter.data()[0] - boxBCenter.data()[0] ) > 
			abs ( boxASize.data()[0] ) + abs (boxBSize.data()[0] ) )
		return false;
	// If length.y > height
	if (	abs ( boxACenter.data()[1] - boxBCenter.data()[1] ) > 
			abs ( boxASize.data()[1] ) + abs (boxBSize.data()[1] ) )
		return false;
	
	return true;
}

bool Collision2D::IsCollid(	ColliderSphere sphere,
							ColliderPoint	point	)
{
	vector2f deltaPoint	= sphere.position - point.position;

	if ( std::sqrt( deltaPoint.data()[0] * deltaPoint.data()[0] + 
					deltaPoint.data()[1] * deltaPoint.data()[1] ) > sphere.radious )
		return false;

	return true;
}

bool Collision2D::IsCollid(	ColliderBoundingBox boundingBox,
							ColliderPoint	point	)
{
	vector2f boxSize	= boundingBox.pointB - boundingBox.pointA;
	vector2f boxCenter	= ( boundingBox.pointA + boundingBox.pointB ) / 2;

	// If length.x > width
	if (	std::abs ( boxCenter.data()[0] - point.position.data()[0] ) > 
			std::abs ( boxSize.data()[0] / 2 ) )
		return false;
	// If length.y > height
	if (	std::abs ( boxCenter.data()[1] - point.position.data()[1] ) > 
			std::abs ( boxSize.data()[1] / 2 ) )
		return false;

	return true;
}

bool Collision2D::IsCollid(	ColliderSphere sphere, 
							ColliderBoundingBox boundingBox	)
{
	return false;
}
