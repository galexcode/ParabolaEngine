#include "ParabolaCore/SoundSharedDevice.h"
#include "ParabolaCore/SoundPlayer.h"

PARABOLA_NAMESPACE_BEGIN
unsigned long SoundSharedDevice::nextID = 0;
std::map<unsigned long, SoundPlayer*> SoundSharedDevice::myPlayerStorage;

/// Signs the player as valid
void SoundSharedDevice::sign(SoundPlayer *player){
	if(player){
		player->myIdentification = ++nextID;
		myPlayerStorage[player->myIdentification] = player;
	}
};

/// Removes the player from the list
void SoundSharedDevice::unsign(SoundPlayer *player){
	if(player){
		myPlayerStorage.erase(myPlayerStorage.find(player->myIdentification));
		player->myIdentification = -1; //invalid
	}
};

PARABOLA_NAMESPACE_END