#ifndef MINIMAL_BUILD

#include "ParabolaCore/SoundPlayer.h"
#include "ParabolaCore/SoundSharedDevice.h"
#include "ParabolaCore/ContentBank.h"

#include <iostream>

PARABOLA_NAMESPACE_BEGIN

/// Private constructor - only instance able by GameCore.
SoundPlayer::SoundPlayer(GameCore *parent, const String &name){
	std::cout<<"Created a sound player"<<std::endl;

	myIdentification = -1; //invalid
	myName = name;
	myContentBank = NULL;

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
	r = m->openFromFile(fileName);
	myMusicList.push_back(m);
	return r;
};

/// Associate a content bank
void SoundPlayer::setContentBank(ContentBank* contentBank){
	myContentBank = contentBank;
};


/// Starts playing a sound
bool SoundPlayer::playSound(const String &fileName){
	if(myContentBank){
		sf::Sound *s = new sf::Sound(*myContentBank->getSoundBuffer(fileName));
		s->play();
		mySoundList.push_back(s);
	}
	return true;
};


/// Iterates the sound list, removing finished sounds.
void SoundPlayer::refreshSoundList(){

};

/// Iterates the music list, while removing items if necessary
void SoundPlayer::refreshMusicList(){
	
};



PARABOLA_NAMESPACE_END
#endif