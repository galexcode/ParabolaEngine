#ifndef ForgeWorldRegion_h__
#define ForgeWorldRegion_h__

#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Forge
	\class ForgeWorldRegion
*/
class PARABOLA_API ForgeWorldRegion{
public:
	
private:
	Vec2<Uint64> m_globalIndex;
	Vec2f m_worldPosition;
};

PARABOLA_NAMESPACE_END
#endif // ForgeWorldRegion_h__
