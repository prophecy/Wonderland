#ifndef __WONDER_APP_H__
#define __WONDER_APP_H__

#include "AppInclude.h"

class WonderApp : public IApplication
{
	virtual void Create();
	virtual void Destroy();
	virtual void Start();
	virtual void Stop();
	virtual void Resume();
	virtual void Pause();
};

#endif // __WONDER_APP_H__