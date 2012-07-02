#ifndef PARABOLA_APPLICATION_CORE_H
#define PARABOLA_APPLICATION_CORE_H

#include "Platform.h"
#include "Strings.h"
#include "StringList.h"
#include "InputEvent.h"
#include <vector>

#include <stdio.h>

PARABOLA_NAMESPACE_BEGIN

namespace ApplicationSettings{
	enum PlatformType{
		Desktop = 0,
		Mobile
	};
};

class ScopedFile;

class PARABOLA_API Application{
public:
	Application();

	int myWindowWidth, myWindowHeight;

	bool m_running;

	/// True while the application is alive
	bool running();


	std::vector<InputEvent> pendingEvents;

	static int getPlatformType();

	ScopedFile* getAssetFile(String &path);

	StringList getAssetList(String path);

	String myDataDirectory;
	String myExternalStorageDirectory;

	static Application* myInstance;
	int myPlatformType;

	class MobileServices{
	public:
		static void sendTextMessage(String number, String content);
	};

#ifdef PARABOLA_ANDROID
	
#endif
};


PARABOLA_NAMESPACE_END

#endif