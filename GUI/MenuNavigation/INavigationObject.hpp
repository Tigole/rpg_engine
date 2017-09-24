#ifndef _INAVIGATION_OBJECT_HPP
#define _INAVIGATION_OBJECT_HPP 1

class MenuNavigation;

class INavigationObject
{
public:
	virtual ~INavigationObject(){}
	virtual void mt_Place(int top_px, int left_px, int width_px, int height_px) = 0;
	virtual int mt_Callback(MenuNavigation* parent) = 0;
};

#endif // !_INAVIGATION_OBJECT_HPP
