# Wonderland

Wonderland is cross-platform C++ framework which should be suitable to integrate
 with somewhat low-level system. Such a cross-platfrom mobile plugin,
 or work behind framework for game.

Wonderland runs under several basic concepts; task, event, entity.

**Task is the behaviour**  
**Event is message**  
**Entity is object** 

Wonderland has it own memory management **WonderPtr**  
**It is a smart pointer to handle**  
 This make you can move your on-memory allocated data from one place to another
 in runtime. (At lest in theory :) ). You can event implement your own
 memory management strategy, memory pool for example, 
 without affecting to the application codebase.

## Getting Started

**Allocate Application**

It is the first step to allocate Application. 
You process can have only 1 application.

```
WonderPtr<MyApplication> myApplication;
myApplication.Alloc();
```
This is application sample code.

```
class MyApplication : public IApplication
{
public:
    
    virtual void Create()
    {
        WonderPtr<MainScene> mainScene = CreateElement<MainScene>();
        sceneManager->SetNextScene(sceneManager->AddScene(mainScene));
    }
    
    virtual void Destroy() {}
    virtual void Start() {}
    virtual void Stop() {}
    virtual void Resume() {}
    virtual void Pause() {}
};
```

Please notice **Create** function, you will see how to allocate the scene.
The scene allocation is required here, 
because Wonderland starts the first scene 
right after the application is started.

Now, you have the application for your system. Next, 
you need to start things up.

Wonderland does things by plugins.

Wonderland plugin initializes Application, 
and start the first scene.
It is good idea that 
you create WonderlandPlugin as the last plugin.

Here is how to create the plugin.
```
WonderPtr<WonderlandPlugin> wonderlandPlugin;
wonderlandPlugin.Alloc();
wonderlandPlugin->Create(myApplication);
```

You do not need to declare and implement WonderlandPlugin
 by your self (Unless you really know what you want to do.).

Later, Wonderland should have fundamantal plugins 
in the arsenal. For example, IosPlugin, AndroidPlugin, 
GamePlugin, etc.

Now you should be able to code in Wonderland.

## Let's make some stuff

In Wonderland, 
One (And only one) application can have many scenes, 
one scen can have many tasks, events, and entities.

Here is an scene sample code
```
class MainScene : public IScene
{
public:
    virtual void Create()
    {
        // Allocate task
        WonderPtr<MyTask> myTask = CreateElement<MyTask>();
        
        // Bind task
        BindTask(MyTask);

        // Allocate entity
        WonderPtr<MyEntity> myEntity = CreateElement<MyEntity>();

        // Add entity
        AddEntity(myEntity);
    }
    
    virtual void Destroy() {}
    virtual void Start() {}
    virtual void Stop() {}
    virtual void Resume() {}
    virtual void Pause() {}
};
```

This scene shows example to allocate task and entity.
Please remember that: **"Task is behavior"** and **"Entity is object"**.