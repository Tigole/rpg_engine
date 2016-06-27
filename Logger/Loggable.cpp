#include "Loggable.h"

Loggable::Loggable(ILogger& log)
 :  m_log(log)
{}

Loggable::~Loggable()
{}
