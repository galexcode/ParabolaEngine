#include "ParabolaCore/SoundPlayer.h"
#include "ParabolaCore/SoundSharedDevice.h"

#include <iostream>

PARABOLA_NAMESPACE_BEGIN

/// Private constructor - only instance able by GameCore.
SoundPlayer::SoundPlayer(GameCore *parent, const String &name){
	std::cout<<"Created a sound player"<<std::endl;

	myIdentification = -1; //invalid
	myName = name;

	SoundSharedDevice::sign(this);
};

/// Safely destroys all sounds associated and removes itself from the shared device.
SoundPlayer::~SoundPlayer(){
	std::cout<<"Removed a sound player"<<std::endl;

	SoundSharedDevice::unsign(this);
};

/// Starts streaming a music from a file
bool SoundPlayer::playMusic(const String &fileName){
	bool r;
	sf::Music *m = new sf::Music();
	r = m->OpenFromFile(fileName);
	myMusicList.push_back(m);
	return r;
};


/// Starts playing a sound
bool SoundPlayer::playSound(const String &fileName){
	return false;
};


/// Iterates the sound list, removing finished sounds.
void SoundPlayer::refreshSoundList(){

};

/// Iterates the music list, while removing items if necessary
void SoundPlayer::refreshMusicList(){
	
};

PARABOLA_NAMESPACE_END