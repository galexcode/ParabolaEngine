#ifndef ForgeLayer_h__
#define ForgeLayer_h__

#include "Platform.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Forge
	\class ForgeWorldLayer
	\brief Subdividision of the world by layers
*/
class PARABOLA_API ForgeWorldLayer{
public:
	/// Constructs the layer
	ForgeWorldLayer();

	/// Construct directly with a name
	ForgeWorldLayer(const String &name);

	/// Get the name of this layer
	String getName();

	/// Render the layer of the world
	void render();

private:
	/// Hidden flag: sets visibility of this layer.
	bool m_hidden;
	/// Layer name
	String m_name;
};

PARABOLA_NAMESPACE_END
#endif // ForgeLayer_h__
