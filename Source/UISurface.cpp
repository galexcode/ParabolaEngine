#include <ParabolaCore/UISurface.h>

PARABOLA_NAMESPACE_BEGIN

void UISurface::draw(Renderer* renderer){
	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->draw(renderer);
	}
};

/// Returns a control in the hierarchy with the name, or NULL if not found - TODO: recursive iterative
UIControl* UISurface::getControlByName(const String& name){
	UIControl* control = NULL;
	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		if((*it)->getName() == name) return (*it); // the surface returned something
	}

	return NULL; // Nothing found.
};

/// Callback to handle an event
bool UISurface::onEventNotification(Event& event){
	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->onEventNotification(event);
	}

	return true;
};

/// Set the unique name of this surface
void UISurface::setName(const String& name){
	m_name = name;
};

/// Get the unique name of this surface
String UISurface::getName(){
	return m_name;
};

PARABOLA_NAMESPACE_END