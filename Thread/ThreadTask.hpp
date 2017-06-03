#ifndef _THREAD_TASK_HPP
#define _THREAD_TASK_HPP 1

#include <SFML/System.hpp>

class ThreadTask
{
public:
	ThreadTask();
	virtual ~ThreadTask();

	void start(void);
	bool hasStarted(void) const;
	bool isDone(void) const;

protected:
	void done(void);
	virtual void work(void) = 0;

	sf::Thread m_thread;
	bool m_started;
	bool m_done;
};

#endif // _THREAD_TASK_HPP
