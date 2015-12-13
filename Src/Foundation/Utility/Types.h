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

#ifndef __TYPES_H__
#define __TYPES_H__

#define WONDERLAND_PLATFORM_NONE		0
#define WONDERLAND_PLATFORM_WINDOWS		1
#define WONDERLAND_PLATFORM_IOS			2
#define WONDERLAND_PLATFORM_ANDROID		3

#define WONDERLAND_ACTIVE_PLATFORM		WONDERLAND_PLATFORM_NONE

#define MEM_POOL_DEBUG

#if defined( __APPLE_CC__)
// Device                                                     Simulator
// Both requiring OS version 5.0 or greater
#   if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 50000 || __IPHONE_OS_VERSION_MIN_REQUIRED >= 30000
#		undef WONDERLAND_ACTIVE_PLATFORM	
#       define WONDERLAND_ACTIVE_PLATFORM	WONDERLAND_PLATFORM_IOS
#	endif
#elif defined( __WIN32__ ) || defined( _WIN32 )
#	undef WONDERLAND_ACTIVE_PLATFORM
#	define WONDERLAND_ACTIVE_PLATFORM	WONDERLAND_PLATFORM_WINDOWS
#elif defined( __ANDROID__ )
#	undef WONDERLAND_ACTIVE_PLATFORM
#	define WONDERLAND_ACTIVE_PLATFORM	WONDERLAND_PLATFORM_ANDROID
#endif 

// Include
#	include <string>
#	include <vector>
#	include <deque>
#	include <map>
#	include <set>
#	include <list>

// Include for Windows
#if WONDERLAND_ACTIVE_PLATFORM == WONDERLAND_PLATFORM_WINDOWS 
#	include <windows.h>
#endif 

// Typedef
#if WONDERLAND_ACTIVE_PLATFORM == WONDERLAND_PLATFORM_WINDOWS

#if _WIN64
    typedef unsigned __int64	addr;
#else
    typedef unsigned __int32	addr;
#endif

	typedef __int8              s8;
	typedef __int16             s16;
	typedef __int32             s32;
	typedef __int64             s64;
	typedef unsigned __int8     u8;
	typedef unsigned __int16    u16;
	typedef unsigned __int32    u32;
	typedef unsigned __int64    u64;

	typedef volatile u8         vu8;
	typedef volatile u16        vu16;
	typedef volatile u32        vu32;
	typedef volatile u64        vu64;
	typedef volatile s8         vs8;
	typedef volatile s16        vs16;
	typedef volatile s32        vs32;
	typedef volatile s64        vs64;

	typedef float               f32;
	typedef double              f64;
	typedef volatile f32        vf32;
	typedef volatile f64        vf64;

	typedef size_t				size_t;

#elif WONDERLAND_ACTIVE_PLATFORM == WONDERLAND_PLATFORM_IOS

#if __x86_64__ || __ppc64__
    typedef	unsigned long		addr;
#else
    typedef	unsigned int		addr;
#endif

	typedef	unsigned char		s8;
	typedef short int			s16;
	typedef int					s32;
	typedef long long			s64;
	typedef unsigned char		u8;
	typedef unsigned short int	u16;
	typedef unsigned int		u32;
	typedef unsigned long long  u64;
	
	typedef volatile u8         vu8;
	typedef volatile u16        vu16;
	typedef volatile u32        vu32;
	typedef volatile u64        vu64;
	typedef volatile s8         vs8;
	typedef volatile s16        vs16;
	typedef volatile s32        vs32;
	typedef volatile s64        vs64;
	
	typedef float               f32;
	typedef double              f64;
	typedef volatile f32        vf32;
	typedef volatile f64        vf64;
	
	typedef size_t				size_t;

#elif WONDERLAND_ACTIVE_PLATFORM == WONDERLAND_PLATFORM_ANDROID
	typedef	unsigned char		s8;
	typedef short int			s16;
	typedef int					s32;
	typedef long long			s64;
	typedef unsigned char		u8;
	typedef unsigned short int	u16;
	typedef unsigned int		u32;
	typedef unsigned long long  u64;

	typedef volatile u8         vu8;
	typedef volatile u16        vu16;
	typedef volatile u32        vu32;
	typedef volatile u64        vu64;
	typedef volatile s8         vs8;
	typedef volatile s16        vs16;
	typedef volatile s32        vs32;
	typedef volatile s64        vs64;

	typedef float               f32;
	typedef double              f64;
	typedef volatile f32        vf32;
	typedef volatile f64        vf64;
	
	typedef size_t				size_t;

#endif

// bool
#ifndef BOOL
	typedef int                 BOOL;
#endif  // BOOL

// TRUE
#ifndef TRUE
#	define TRUE					1
#endif  // TRUE

// FALSE
#ifndef FALSE
#	define FALSE				0
#endif  // FALSE

// INVALID
#ifndef INVALID
#	define INVALID				-1
#endif // INVALID

#ifndef NULL
#	ifdef  __cplusplus
#		define NULL				0
#	else   // __cplusplus
#		define NULL				((void *)0)
#	endif  // __cplusplus
#endif  // NULL

// Constance
const f32 PI	= 3.14159265358979323846f;
const f32 PI_2	= 1.57079632679489661923f;
const f32 PI_4	= 0.785398163397448309616f;

#endif  // __TYPES_H__
