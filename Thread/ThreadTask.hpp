#ifndef _THREAD_TASK_HPP
#define _THREAD_TASK_HPP 1

#include <SFML/System.hpp>

class ThreadTask
{
public:
	ThreadTask();
	virtual ~ThreadTask();

	void mt_Start(void);
	bool mt_Has_Started(void) const;
	bool mt_Is_Done(void) const;

protected:
	void mt_Done(void);
	virtual void mt_Work(void) = 0;

	sf::Thread m_thread;
	bool m_started;
	bool m_done;
};

#endif // _THREAD_TASK_HPP
