#include <ParabolaCore/UIWindow.h>
#include <ParabolaCore/Text.h>

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Construct the window
UIWindow::UIWindow() : m_timeSinceLastMouseMovement(0.f){
	m_surfaces.push_back(new UISurface());
};

/// Creates a new surface, which is underneath the relativeSurface specified
UISurface* UIWindow::createSurfaceBelow(UISurface* relativeSurface, const String& name){
	if(!relativeSurface) return NULL;

	for(std::vector<UISurface*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		if((*it) == relativeSurface){
			// This where where to insert
			UISurface* surface = new UISurface();
			surface->setName(name);
			m_surfaces.insert(it, surface);
			return surface;
		}
	}

	return NULL;
};

/// Get a surface by its name
UISurface* UIWindow::getSurfaceByName(const String& name){
	for(std::vector<UISurface*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		if((*it)->getName() == name){
			return (*it);
		}
	}
	return NULL;
};

/// Sets new boundaries to this UIWindow
void UIWindow::setDimensions(Rect<float> dimensions){
	m_bounds = dimensions;
};

/// Get the position of the exact middle of this UIWindow
Vec2f UIWindow::getMiddlePosition(){
	return Vec2f(m_bounds.left + m_bounds.width/2, m_bounds.top + m_bounds.height/2);
};

/// Get the surface closer to the user
UISurface* UIWindow::getTopSurface(){
	if(m_surfaces.empty()) return NULL;
	else{
		return m_surfaces[0];
	}
};

/// Returns a control in the hierarchy with the name, or NULL if not found
UIControl* UIWindow::getControlByName(const String& name){
	UIControl* control = NULL;
	for(std::vector<UISurface*>::const_iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		control = (*it)->getControlByName(name);
		if(control != NULL) return control; // the surface returned something
	}

	return NULL; // Nothing found.
};

/// Draw the UI
void UIWindow::draw(Renderer* renderer){
	for(std::vector<UISurface*>::reverse_iterator it = m_surfaces.rbegin(); it != m_surfaces.rend(); it++){
		(*it)->draw(renderer);
	}

	if(m_showingToolTip){
		Text t;
		t.setString("tool tip");
		renderer->draw(t);
	}
};

/// Update the state of the ui
void UIWindow::update(float elapsedTime){
	m_timeSinceLastMouseMovement += elapsedTime;
	if(m_timeSinceLastMouseMovement >= 1.2f){
		// time to show a tool tip
		m_showingToolTip = true;
	}
};

/// Pushes a new event through the ui system
bool UIWindow::pushEvent(Event& event){

	/// Tooltip related
	if(event.type == Event::MouseMoved){ m_timeSinceLastMouseMovement = 0.f; m_showingToolTip = false;}

	for(std::vector<UISurface*>::const_iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++){
		if(!(*it)->onEventNotification(event)){
			return false; // no propagation of the event for lower layers if the surface returns false
		}
	}
	return true;
};

PARABOLA_NAMESPACE_END