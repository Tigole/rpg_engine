#ifndef LOGGABLE_H
#define LOGGABLE_H 1

#include "ILogger.h"

class Loggable
{
public:
    Loggable(ILogger& log);
    virtual ~Loggable();

protected:
    ILogger& m_log;

// Documentation
    /** \class Loggable
        \brief Classe de base pour log un programme
        \date 26/04/2016 Creation
        \author Sylvain JANNIERE
    **/
// public
    /** \fn Loggable(ILogger& log)
        \brief Constructeur
        \param[in] log Reference sur le log a utiliser
    **/
    /**
        \fn virtual ~Loggable()
        \brief Destructeur
    **/
// protected
    /** \var ILogger& m_log
        \brief Le log pour enregistrer des informations.
    **/
};

#endif // LOGGABLE_H
