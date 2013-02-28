#include <ParabolaCore/UIControl.h>

#include <iostream>

using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Base constructor of controls
UIControl::UIControl() 
	:	m_parent(NULL), 
		m_stateContext(NULL),
		m_hasFocus(false),
		m_layoutController(NULL),
		m_backgroundColor(91,91,91),
		m_topBorderColor(69,69,69),
		m_leftBorderColor(m_topBorderColor),
		m_rightBorderColor(m_topBorderColor),
		m_bottomBorderColor(m_topBorderColor),
		m_clipChildren(false),
		m_clipContents(false),
		m_visible(true),
		m_drawBorder(true),
		m_stretchForContents(false)
{
	
	m_resizeAnimation.addAnimable(this);
	m_positionAnimation.addAnimable(this);

	m_minimumDimensions = Vec2f(10,10);
	m_maximumDimensions = Vec2f(5000,5000);
};

/// Requests a tool tip text label from the control
/// If only a empty string is returned, no tooltip is shown
String UIControl::getToolTipLabel(){
	return "";
};

/// Get the number of children of this control
int UIControl::getChildCount()
{
	return static_cast<int>(m_children.size());
};

/// Get a child at a index
UIControl* UIControl::getChild(int index)
{
	return m_children[index];
};

/// Get the current size of the control
Vec2f UIControl::getSize()
{
	return Vec2f(m_bounds.width, m_bounds.height);
};

/// Set a new layout to the control
void UIControl::setLayout(UILayout* layout){
	m_layoutController = layout;

	// Perform the layouting
	m_layoutController->doLayout(this);
};

/// Get the currently assigned layout controller
/// \return NULL if there is no layout controller assigned
UILayout* UIControl::getLayout(){
	return m_layoutController;
};


/// Callback to render itself, renders children
void UIControl::draw(Renderer* renderer){

};

/// Callback to handle events
bool UIControl::onEventNotification(Event& event){
	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->onEventNotification(event);
	}
	return false;
};

/// Get bounds of the control
FloatRect UIControl::getBounds(){
	return m_bounds;
};

/// Is the control able to get input focus or not?
bool UIControl::isFocusable()
{
	return false;
};

/// Attempts focus on this control
bool UIControl::focus()
{
	// Fails to get focus if it is not focusable
	if(!isFocusable()) return false; 

	if(getContext())
	{
		getContext()->m_focusControl = this;
		m_hasFocus = true;
	}
	else
	{
		cout<<"Cant focus an element without a hierarchy"<<endl;
	}

	return true;
};

/// Check if the control currently has focus
bool UIControl::hasFocus()
{	
	return m_hasFocus;
};

/// Hierarchicly sets the context to all children
void UIControl::setContext(UIStateContext* states)
{
	m_stateContext = states;

	for(std::vector<UIControl*>::iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->setContext(states);
	}
}

/// Remove focus from the element
void UIControl::blur()
{
	m_hasFocus = false;
};

bool UIControl::onKeyPressed(Keyboard::Key key)
{

	return false;
}

bool UIControl::onTextEvent(Uint32 code)
{
	return false;
};

/// Deep clone of the control and its hierarchy
UIControl* UIControl::clone()
{
	return new UIControl(*this);
}

void UIControl::setRect(FloatRect rect)
{
	setPosition(rect.left, rect.top);
	setSize(rect.width, rect.height);
};

FloatRect UIControl::getRect()
{
	return m_bounds;
};

/// Get the position of the exact middle of this UIWindow
Vec2f UIControl::getMiddlePosition(){
	return Vec2f(m_bounds.left + m_bounds.width/2, m_bounds.top + m_bounds.height/2);
};


/// Returns the UIWindow context or NULL if not attached
UIStateContext* UIControl::getContext()
{
	return m_stateContext;
};


/// Adds a new control ... wrong API todo
void UIControl::addControl(UIControl* control){
	m_children.push_back(control);

	// Assign
	control->m_parent = this;
	control->setContext(m_stateContext);

	updateLayout();
};

/// Callback when the control is resized
void UIControl::onResize(){
	
}

/// Resizes the control over a defined time
/// The lower border of the control will become at target position
void UIControl::resizeToPoint(float x, float y, float duration){
	Vec2f size;
	size.x = x - m_bounds.left;
	size.y = y - m_bounds.top;
	// ensure min and max
	if(size.x < m_minimumDimensions.x)size.x = m_minimumDimensions.x;
	if(size.y < m_minimumDimensions.y)size.y = m_minimumDimensions.y;
	if(size.x > m_maximumDimensions.x)size.x = m_maximumDimensions.x;
	if(size.y > m_maximumDimensions.y)size.y = m_maximumDimensions.y;

	m_resizeAnimation.setDestination(size.x,size.y);
	m_resizeAnimation.setDuration(duration);
	m_resizeAnimation.stop();
	m_resizeAnimation.play();
};

void UIControl::resize(float width, float height, float duration)
{
	m_resizeAnimation.setDestination(width,height);
	m_resizeAnimation.setDuration(duration);
	m_resizeAnimation.stop();
	m_resizeAnimation.play();
};

void UIControl::reposition(float x, float y, float duration)
{
	m_positionAnimation.setDestination(x, y);
	m_positionAnimation.setDuration(duration);
	m_positionAnimation.stop();
	m_positionAnimation.play();
};



/// Making this class able to animate sizes
void UIControl::animable_set_size(float x, float y){
	setSize(x,y);
	onResize();	
};

Vec2f UIControl::animable_get_size(){
	return Vec2f(m_bounds.width, m_bounds.height);
};

void UIControl::animable_set_position(float x, float y)
{
	m_bounds.left = x;
	m_bounds.top = y;
};

Vec2f UIControl::animable_get_position()
{
	return Vec2f(m_bounds.left, m_bounds.top);
};

/// Set the position of the control
void UIControl::setPosition(float x, float y)
{
	m_bounds.left = x;
	m_bounds.top = y;

	updateLayout();
};

/// Update layout of children
void UIControl::updateLayout()
{
	if(m_layoutController)
	{
		m_layoutController->doLayout(this);
	}
}

/// Update the control
void UIControl::onUpdate(float elapsedTime){

	m_resizeAnimation.onUpdate(elapsedTime);
	m_positionAnimation.onUpdate(elapsedTime);

	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->onUpdate(elapsedTime);
	}
};

/// Get the current size of the control that encompasses all its children
FloatRect UIControl::getContentBounds()
{
	FloatRect bounds = getBounds();

	for(int i = 0; i < getChildCount(); i++)
	{
		// get bounds of the children
		FloatRect cbounds = getChild(i)->getContentBounds();

		if(getChild(i)->m_visible)
		{
			// stretch to children if needed
			if(cbounds.left < bounds.left) bounds.left = cbounds.left;
			if(cbounds.top < bounds.top) bounds.top = cbounds.top;
			if(cbounds.left + cbounds.width > bounds.left + bounds.width) bounds.width = cbounds.left + cbounds.width - bounds.left;
			if(cbounds.top + cbounds.height > bounds.top + bounds.height) bounds.height = cbounds.top + cbounds.height - bounds.top;
		}
	}
	return bounds;
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
	onResize();

	if(m_parent && m_parent->m_stretchForContents) // Goes up the tree 
	{
		float bottom = m_parent->getBounds().top + m_parent->getBounds().height;
		// warn parent to stretch
		float lowestBottom = m_parent->getBounds().top;
		for(int i = 0; i < m_parent->getChildCount(); i++)
		{
			if(m_parent->getChild(i)->getBounds().top + m_parent->getChild(i)->getBounds().height > bottom) bottom = m_parent->getChild(i)->getBounds().top + m_parent->getChild(i)->getBounds().height;
		}
		m_parent->setSize(m_parent->getBounds().width, bottom - m_parent->getBounds().top);
	}

	updateLayout();
};

/// Immediately sets the center of the control to a new position
void UIControl::setCenter(float x, float y){
	m_bounds.setCenter(x,y);
	onPositionChanged();

	updateLayout();
};

void UIControl::innerDraw(Renderer* renderer)
{
	if(!m_visible)return; // no drawing or propagation - ghost

	/// Draw the background color and borders - TODO: no debug draw
	renderer->drawDebugQuad(m_bounds.left + m_bounds.width/2, m_bounds.top + m_bounds.height/2, 0,m_bounds.width, m_bounds.height, m_backgroundColor);
	
	if(m_drawBorder)
	{
		renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top), m_topBorderColor);
		renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top + m_bounds.height), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top + m_bounds.height), m_bottomBorderColor);
		renderer->drawDebugLine(Vec2f(m_bounds.left, m_bounds.top), Vec2f(m_bounds.left, m_bounds.top + m_bounds.height), m_leftBorderColor);
		renderer->drawDebugLine(Vec2f(m_bounds.left + m_bounds.width, m_bounds.top), Vec2f(m_bounds.left + m_bounds.width, m_bounds.top + m_bounds.height), m_rightBorderColor);

	}
	
	
	draw(renderer);	

	// clip?
	if(m_clipChildren)renderer->enableClipping(FloatRect(m_bounds.left,m_bounds.top,m_bounds.width, m_bounds.height));

	// Let children render as well
	for(std::vector<UIControl*>::const_iterator it = m_children.begin(); it != m_children.end(); it++){
		(*it)->innerDraw(renderer);
	}

	if(m_clipChildren)renderer->disableClipping();
}



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