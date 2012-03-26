#include "ParabolaCore/ContentBank.h"

PARABOLA_NAMESPACE_BEGIN

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

/// Get a sound buffer
sf::SoundBuffer* ContentBank::getSoundBuffer(const String &name){
	return NULL;
};

/// Temp
/// Creates a texture from a file
Texture* ContentBank::createTexture(const String &fileName, const String &alias){
	String name;
	if(alias.empty())name = fileName;
	else name = alias;

	std::map<String, Texture*>::iterator it = myTextureResources.find(name);
	if(it == myTextureResources.end()){
		myTextureResources[name] = new Texture();
		myTextureResources[name]->LoadFromFile(fileName);
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