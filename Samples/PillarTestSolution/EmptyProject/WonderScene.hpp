#ifndef __SCENE_WELCOME_HPP_
#define __SCENE_WELCOME_HPP_

#include "IScene.h"
#include "IEntity.h"
#include "ITask.h"
#include "IEvent.h"

// --------------------------------------------------------------------------------

class LoginViewEntity : public IEntity
{
};

class ListViewEntity : public IEntity
{
};

class RestfulEntity : public IEntity
{
};

class RequestEvent : public IEvent
{

};

class EventHandlerTask : public ITask
{
	virtual void Create() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual void Destroy() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual void Start() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual void OnTask() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual void Stop() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual void OnEvent(IEvent* evt, s32 code, std::string message) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual void OnEvent(IEvent* evt, s8* data) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}
};

// --------------------------------------------------------------------------------

class SceneWelcome : public IScene
{
	virtual void Create()
	{
		WonderPtr<LoginViewEntity> loginView = CreateElement<LoginViewEntity>();
		AddEntity(loginView);
		loginView->BindTask(CreateElement<EventHandlerTask>());
	}

	virtual void Destroy() { }

	virtual void Start() { }

	virtual void Stop() { }

	virtual void Resume() { }

	virtual void Pause() { }

};


#endif // __SCENE_MAIN_MENU_H__