#ifndef UIState_h__
#define UIState_h__

#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN

class UIState{
public:
	UIState(){
		m_allowsToolTips = true; // in mobile there are none for instance
	}

	bool m_allowsToolTips;


	/// Does the user interface system use animation globally?
	bool m_allowAnimation;
};

PARABOLA_NAMESPACE_END
#endif // UIState_h__
