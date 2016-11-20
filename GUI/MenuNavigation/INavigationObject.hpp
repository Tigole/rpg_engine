#ifndef _INAVIGATION_OBJECT_HPP
#define _INAVIGATION_OBJECT_HPP 1

class MenuNavigation;

class INavigationObject
{
public:
	virtual ~INavigationObject(){}
	virtual void place(int top_px, int left_px, int width_px, int height_px) = 0;
	virtual int callback(MenuNavigation* parent) = 0;
};

#endif // !_INAVIGATION_OBJECT_HPP