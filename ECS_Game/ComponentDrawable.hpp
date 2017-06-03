#ifndef _COMPONENT_DRAWABLE_HPP
#define _COMPONENT_DRAWABLE_HPP 1

class sf::RendererWindow;

class ComponentDrawable : public ECS_Component
{
public:
	ComponentDrawable(const ECS_ComponentId& id) : ECS_Component(id){}
	virtual ~ComponentDrawable(){}

	virtual void updatePosition(int x, int y) = 0;
	virtual void getSize(int& x, int& y) = 0;
	virtual void draw(sf::RendererWindow* window) = 0;
};

#endif // _COMPONENT_DRAWABLE_HPP
