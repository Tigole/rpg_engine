#ifndef _WINDOW_HPP
#define _WINDOW_HPP 1

#include <string>

class Window
{
public:
	Window(const std::string& title);
	virtual ~Window();

	void beginDraw(void);
	void endDraw(void);

	void update(void);
};

#endif // _WINDOW_HPP
