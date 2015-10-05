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

/*
-----------------------------------------------------------------------------

OGRE (www.ogre3d.org) is made available under the MIT License.

Copyright (c) 2000-2013 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "Log.h"
#include <time.h>
#include <iostream>
#include <iomanip>
#include <algorithm>

#if WONDERLAND_ACTIVE_PLATFORM == WONDERLAND_PLATFORM_WINDOWS
#	define LOGV(TAG, MSG)	{}
#	define LOGD(TAG, MSG)	{ std::cerr << message << std::endl; }
#	define LOGI(TAG, MSG)	{}
#	define LOGW(TAG, MSG)	{}
#	define LOGE(TAG, MSG)	{}
#elif WONDERLAND_ACTIVE_PLATFORM == WONDERLAND_PLATFORM_ANDROID
#	include <android/log.h>
#	define LOGV(TAG, MSG) __android_log_print(ANDROID_LOG_VERBOSE, TAG, "%s", MSG)
#	define LOGD(TAG, MSG) __android_log_print(ANDROID_LOG_DEBUG  , TAG, "%s", MSG)
#	define LOGI(TAG, MSG) __android_log_print(ANDROID_LOG_INFO   , TAG, "%s", MSG)
#	define LOGW(TAG, MSG) __android_log_print(ANDROID_LOG_WARN   , TAG, "%s", MSG)
#	define LOGE(TAG, MSG) __android_log_print(ANDROID_LOG_ERROR  , TAG, "%s", MSG)
#elif WONDERLAND_ACTIVE_PLATFORM == WONDERLAND_PLATFORM_IOS
#endif // WONDERLAND_ACTIVE_PLATFORM == ...

//-----------------------------------------------------------------------
Log::Log()
{
}
//-----------------------------------------------------------------------
void Log::Create( const std::string& name, bool debuggerOuput, bool suppressFile )
{
	mLogLevel	= LL_NORMAL;
	mDebugOut	= debuggerOuput,
	mSuppressFile	= suppressFile;
	mTimeStamp	= true;
	mLogName	= name;

	if (!mSuppressFile)
	{
		mfpLog.open(name.c_str());
	}
}
//-----------------------------------------------------------------------
void Log::Destroy()
{
	if (!mSuppressFile)
	{
		mfpLog.close();
	}
}
//-----------------------------------------------------------------------
Log::~Log()
{
}
//-----------------------------------------------------------------------
void Log::DebugLog( const std::string& message, LogMessageLevel lml, bool maskDebug )
{
	if ((mLogLevel + lml) >= OGRE_LOG_THRESHOLD)
	{
		for( mtLogListener::iterator i = mListeners.begin(); i != mListeners.end(); ++i )
			(*i)->MessageLogged( message, lml, maskDebug, mLogName );

		if (mDebugOut && !maskDebug)
			LOGD(mLogName.c_str(), message.c_str());

		// Write time into log
		if (!mSuppressFile)
		{
			if (mTimeStamp)
			{
				struct tm pTime;
				time_t ctTime; time(&ctTime);
				
				time_t tStore;
				errno_t err = localtime_s( &pTime, &tStore);
				mfpLog << std::setw(2) << std::setfill('0') << pTime.tm_hour
					<< ":" << std::setw(2) << std::setfill('0') << pTime.tm_min
					<< ":" << std::setw(2) << std::setfill('0') << pTime.tm_sec
					<< ": ";
			}
			mfpLog << message << std::endl;

			// Flush stcmdream to ensure it is written (incase of a crash, we need log to be up to date)
			mfpLog.flush();
		}
	}
}
	
//-----------------------------------------------------------------------
void Log::SetTimeStampEnabled(bool timeStamp)
{
		
	mTimeStamp = timeStamp;
}

//-----------------------------------------------------------------------
void Log::SetDebugOutputEnabled(bool debugOutput)
{
		
	mDebugOut = debugOutput;
}

//-----------------------------------------------------------------------
void Log::SetLogDetail(LoggingLevel ll)
{
		
	mLogLevel = ll;
}

//-----------------------------------------------------------------------
void Log::AddListener(LogListener* listener)
{
		
	mListeners.push_back(listener);
}

//-----------------------------------------------------------------------
void Log::RemoveListener(LogListener* listener)
{
		
	mListeners.erase(std::find(mListeners.begin(), mListeners.end(), listener));
}
//---------------------------------------------------------------------
Log::Stream Log::GetStream(LogMessageLevel lml, bool maskDebug) 
{
	return Stream(this, lml, maskDebug);

}