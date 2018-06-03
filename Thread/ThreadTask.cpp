#include "Thread/ThreadTask.hpp"

ThreadTask::ThreadTask()
 :	m_thread(&ThreadTask::mt_Work, this),
	m_started(false),
	m_done(true)
{}

ThreadTask::~ThreadTask()
{}

void ThreadTask::mt_Start(void)
{
	if ((m_done == true) && (m_started == false))
	{
		m_started = true;
		m_done = false;
		m_thread.launch();
	}
}

bool ThreadTask::mt_Has_Started(void) const
{
	return m_started;
}

bool ThreadTask::mt_Is_Done(void) const
{
	return m_done;
}

void ThreadTask::mt_Done(void)
{
	m_done = true;
}

void ThreadTask::mt_Wait_For_Ending(int sleep_milliseconds) const
{
	sf::Time l_sleeping_duration(sf::milliseconds(sleep_milliseconds));
	while (mt_Is_Done() == false)
	{
		sf::sleep(l_sleeping_duration);
	}
}