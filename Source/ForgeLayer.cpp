#include <ParabolaCore/ForgeLayer.h>

PARABOLA_NAMESPACE_BEGIN

/// Constructs the layer
ForgeWorldLayer::ForgeWorldLayer() : m_hidden(false), m_name("null"){

};

/// Construct directly with a name
ForgeWorldLayer::ForgeWorldLayer(const String &name) : m_hidden(false), m_name(name){

};

/// Get the name of this layer
String ForgeWorldLayer::getName(){
	return m_name;
};

/// Render the layer of the world
void ForgeWorldLayer::render(){
	if(!m_hidden) return; // no rendering

	//render graph
};

PARABOLA_NAMESPACE_END