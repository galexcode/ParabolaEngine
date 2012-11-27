#include <ParabolaCore/UIControl.h>

PARABOLA_NAMESPACE_BEGIN

/// Base constructor of controls
UIControl::UIControl(){

};

/// Callback to render itself, renders children
void UIControl::draw(Renderer* renderer){
	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->draw(renderer);
	}
};

/// Adds a new control ... wrong API todo
void UIControl::addControl(UIControl* control){
	m_children.push_back(control);
};

/// Returns true when the control is subject of being layout in a grid or other organization form
/// Most controls don't implement this function, as their default behavior is to respond to layouts always
bool UIControl::respondsToLayouts(){
	return true;
};

/// Immediately sets the new size of the control 
void UIControl::setSize(float width, float height){
	m_bounds.width = width;
	m_bounds.height = height;
};

/// Immediately sets the center of the control to a new position
void UIControl::setCenter(float x, float y){
	m_bounds.setCenter(x,y);
	onPositionChanged();
};

/// Immediately sets the center of the control to a new position
void UIControl::setCenter(Vec2f position){
	setCenter(position.x, position.y);
};

/// Callback when the position of the control changed, for updating nested objects
void UIControl::onPositionChanged(){

};

/// Define a new name for this control
void UIControl::setName(const String& name){
	m_name = name;
};

/// Get the name of the control
String UIControl::getName(){
	return m_name;
};

PARABOLA_NAMESPACE_END