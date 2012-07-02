#include "ParabolaCore/ContentBank.h"

PARABOLA_NAMESPACE_BEGIN

/// Creates a loose content bank, destroys its resources on destruction
ContentBank::ContentBank() : myLoader(this){

};

/// Private constructor - only friends can instance ContentBank
ContentBank::ContentBank(GameCore *parent, const String &name) : myLoader(this){
	myName = name;
	myLoadOnRequest = false;
};

/// Loads the entries of the ContentList into memory
/// All resources will be known as its alias
/// Resources with aliases already loaded are ignored, and a log warning is issued
/// Alias of a resource is also what identifies the resource in a search
void ContentBank::loadContentList(ContentList &list, bool storeList){

};

/// Unloads all resources that have entry in the ContentList
/// When unloading the list, the alias will be used to locate all the resources that belong to the list
void ContentBank::unloadContentList(ContentList &list){

};

/// Create a sound buffer
/*void ContentBank::createSoundBuffer(const String &name){
	sf::SoundBuffer *ss = new sf::SoundBuffer();
	ss->loadFromFile(name);
	mySoundResources[name] = ss;
};*/

/// Get a sound buffer
/*sf::SoundBuffer* ContentBank::getSoundBuffer(const String &name){
	return mySoundResources.find(name)->second;
};*/

/// Temp
/// Creates a texture from a file
Texture* ContentBank::createTexture(const String &fileName, const String &alias){
	String name;
	if(alias.empty())name = fileName;
	else name = alias;

	std::map<String, Texture*>::iterator it = myTextureResources.find(name);
	if(it == myTextureResources.end()){
		myTextureResources[name] = new Texture();
		myTextureResources[name]->loadFromFile(fileName);
		return myTextureResources[name];
	}
	else{		
		return myTextureResources[name];
	}
};

/// Temp
/// Get the texture
Texture* ContentBank::getTexture(const String &texture_name){
	return myTextureResources[texture_name];
};

PARABOLA_NAMESPACE_END