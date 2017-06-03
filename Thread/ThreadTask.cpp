#include "Thread/ThreadTask.hpp"

ThreadTask::ThreadTask()
 :	m_thread(&ThreadTask::work, this),
	m_started(false),
	m_done(true)
{}

ThreadTask::~ThreadTask()
{}

void ThreadTask::start(void)
{
	if ((m_done == true) && (m_started == false))
	{
		m_started = true;
		m_done = false;
		m_thread.launch();
	}
}

bool ThreadTask::hasStarted(void) const
{
	return m_started;
}

bool ThreadTask::isDone(void) const
{
	return m_done;
}

void ThreadTask::done(void)
{
	m_done = true;
}
