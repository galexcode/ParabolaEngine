#include "ParabolaCore/ForgeWorld.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN
	
/// Construct
ForgeWorld::ForgeWorld() : m_streamPolicy(ForgeWorld::OnDemand){

};

/// Draw the world
void ForgeWorld::render(){
	for(unsigned int i = 0; i < m_layers.size(); i++){
		m_layers[i].render();
	}
};

/// Changes the current stream policy for this world
void ForgeWorld::setStreamPolicy(StreamPolicy policy){
	m_streamPolicy = policy;
};

/// Create a new layer to the world
ForgeWorldLayer* ForgeWorld::createLayer(const String& name){
	m_layers.push_back(ForgeWorldLayer(name));
	return &m_layers.back();
};

/// Get a layer pointer by its name
ForgeWorldLayer* ForgeWorld::getLayerByName(const String &name){
	return NULL;
};


/// Get a layer by its index
ForgeWorldLayer* ForgeWorld::getLayer(int index){
	return &m_layers[index];
};

/// Get the amount of layers in this world
int ForgeWorld::getLayerCount(){
	return static_cast<int>(m_layers.size());
};


/// Saves the world to a file
bool ForgeWorld::saveToFile(const String& fileName){

	return false;
};

PARABOLA_NAMESPACE_END
