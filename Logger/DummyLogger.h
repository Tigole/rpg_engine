#ifndef DUMMY_LOGGER_H
#define DUMMY_LOGGER_H 1

#include "ILogger.h"

class DummyLogger : public ILogger
{
public:
    virtual bool estValide(void);
    virtual void entreeFonction(const char* nom_fonction);
    virtual void sortieFonction(void);
    virtual void debutEvenement(const char* nom_evenement);
    virtual void finEvenement(void);
    virtual void commencerBlock(const char* nom_block);
    virtual void terminerBlock(void);
    virtual void stopperLog(void);
    virtual ILogger& log(const std::string& msg);

// Documentation
    /** \class DummyLogger
        \brief Objet ne realisant pas d'enregistrement
    **/
};

#endif // DUMMY_LOGGER_H
