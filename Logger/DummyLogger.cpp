#include "DummyLogger.h"


bool DummyLogger::estValide(void)
{
    return true;
}

void DummyLogger::entreeFonction(const char* nom_fonction)
{
    //
}

void DummyLogger::sortieFonction(void)
{
    //
}

void DummyLogger::debutEvenement(const char* nom_evenement)
{
    //
}

void DummyLogger::finEvenement(void)
{
    //
}

void DummyLogger::commencerBlock(const char* nom_block)
{
    //
}

void DummyLogger::terminerBlock(void)
{
    //
}

void DummyLogger::stopperLog(void)
{
    //
}

ILogger& DummyLogger::log(const std::string& msg)
{
    return *this;
}
