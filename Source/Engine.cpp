#include <ParabolaCore/Engine.h>
#include <ParabolaCore/GameCore.h>
#include <ParabolaCore/Renderer.h>

#include <ParabolaCore/View.h>

PARABOLA_NAMESPACE_BEGIN
	
Engine::Engine()
: mCurrentApp(NULL)
, mRenderer(NULL)
{
	
};

Engine::~Engine()
{
	delete mRenderer;
};

void Engine::execute(GameCore* app)
{
	mCurrentApp = app;

	if(mCurrentApp)
	{
		mCurrentApp->m_creator = this;
		mCurrentApp->onCreate();
	}
}

void Engine::init()
{
	// stub code
	mSurface.create();

	// Attempt to initialize the renderer
	mRenderer = Renderer::createAutomaticRenderer(mSurface.window);
}

void Engine::update()
{
	// Check for removal first
	if(mCurrentApp && mCurrentApp->mCloseRequested)
	{
		mCurrentApp = NULL;
	}

	if(mCurrentApp)
	{
		// Poll events
		Event event;
		while(mSurface.window->pollEvent(event))
		{
			mCurrentApp->onEvent(event);
		}

		// Perform the update
		mCurrentApp->innerUpdate(mStepClock.getElapsedTime());
		mStepClock.reset();

		// Draw a frame
		if(mRenderer)
		{
			View mView;
			mView.setRect(0,0, mSurface.window->getWidth(), mSurface.window->getHeight());
			mRenderer->pushView(mView);
			mRenderer->clear();
			mCurrentApp->innerRender();
			mRenderer->display();
			mSurface.window->swapBuffers();
		}
	}
};

/// Get the current renderer
Renderer* Engine::getRenderer()
{
	return mRenderer;
}

PARABOLA_NAMESPACE_END

