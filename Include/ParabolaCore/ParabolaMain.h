#ifndef PARABOLA_APPLICATION_H
#define PARABOLA_APPLICATION_H

#include "Platform.h"
#include "Strings.h"
#include "Application.h"
#include "InputEvent.h"
#include <stdio.h>

pE::Application myApp; 

extern void applicationStartup();
extern void applicationUpdate();
extern void applicationCleanup();

#ifdef PARABOLA_ANDROID

#if !defined ANDROID_PACKAGE_NAME || !defined ANDROID_ACTIVITY_NAME
#error Cannot build for Android platform without specifying the ANDROID_PACKAGE_NAME and ANDROID_ACTIVITY_CLASS
#endif

#include "AndroidJNI.h"
#include <android/keycodes.h>

void android_init(){
	// first register in the application the interface
	//pE::Application::myInstance->jniEnv = jEnv;
	static bool alreadyStarted = false;

	if(!alreadyStarted){ 
		applicationStartup();
		alreadyStarted = true;
	}
	else{
		pE::InputEvent ev;
		ev.type = pE::InputEvent::Resume;
		myApp.pendingEvents.push_back(ev);
	}
	
}

void android_render(){
	applicationUpdate(); 
}

void android_resize(int w, int h){ 
	myApp.myWindowWidth = w; 
	myApp.myWindowHeight = h;

	pE::InputEvent ev;
	ev.type = pE::InputEvent::Resized;
	myApp.pendingEvents.push_back(ev);
}

void android_keydown(int key){
	pE::String sd = "Keypressed: " + pE::String::number(key);

	pE::InputEvent ev;
	ev.type = pE::InputEvent::KeyPressed;

	switch(key){
		case AKEYCODE_A: ev.key.code = pE::Keyboard::A;break;
		case AKEYCODE_S: ev.key.code = pE::Keyboard::S;break;
		case AKEYCODE_D: ev.key.code = pE::Keyboard::D;break;
		case AKEYCODE_W: ev.key.code = pE::Keyboard::W;break;
	}

	
	myApp.pendingEvents.push_back(ev);
}

void android_touchdown(float x, float y){
	pE::InputEvent ev;
	ev.type = pE::InputEvent::TouchPressed;
	ev.x = x;
	ev.y = y;
	myApp.pendingEvents.push_back(ev); 
}

void android_touchup(float x, float y){
	pE::InputEvent ev;
	ev.type = pE::InputEvent::TouchReleased;
	ev.x = x;
	ev.y = y;
	myApp.pendingEvents.push_back(ev); 
}

void android_touchmove(float x, float y){
	pE::InputEvent ev;
	ev.type = pE::InputEvent::TouchMoved;
	ev.x = x;
	ev.y = y;
	myApp.pendingEvents.push_back(ev); 
}

#elif defined PARABOLA_WINDOWS

	int main(int argc, char** argv){
		applicationStartup();

		while(myApp.running()){
			applicationUpdate();
		}
		applicationCleanup();
		return 0;
	}
#endif

#endif