#ifndef _ILOGGER_H
#define _ILOGGER_H 1

#include <string>
#include <sstream>
#include <fstream>
#include <stack>

#include "Miscellaneous.hpp"

class ILogger;

ILogger& log();

class ILogger
{
public:
    ILogger();
    virtual ~ILogger();

    virtual bool mt_Is_Valid(void) = 0;
    virtual void mt_Entrance_Function(const char* function_name) = 0;
    virtual void mt_Exit_Function(void) = 0;
    virtual void mt_On_Event(const char* event_name) = 0;
    virtual void mt_Stop_Event(void) = 0;
    virtual void mt_Start_Block(const char* block_name) = 0;
    virtual void mt_End_Block(void) = 0;
    virtual void mt_Stop_Log(void) = 0;
    virtual ILogger& mt_Log(const std::string& msg) = 0;
    ILogger& mt_Log(bool b);
    ILogger& mt_Log(const char* msg);
    ILogger& mt_Log(char* msg);
    template<typename T>
    ILogger& mt_Log(const T& nombre)
    {
        return mt_Log(misc::fn_Number_To_String(nombre));
    }

// Documentation
    /** \class ILogger
        \brief Classe used to log information for debugging purpose using markers.
    **/
};

class Logger : public ILogger
{
public:
    Logger(const std::string& fichier);
    virtual ~Logger();

    bool mt_Is_Valid(void);
    virtual void mt_Entrance_Function(const char* function_name);
    virtual void mt_Exit_Function(void);
    virtual void mt_On_Event(const char* nom_evenement);
    virtual void mt_Stop_Event(void);
    virtual void mt_Start_Block(const char* nom_balise);
    virtual void mt_End_Block(void);
protected:
    const std::string m_file_name;
    std::ofstream m_file;

    virtual void mt_Format_Entrance_Function(const char* function_name) = 0;
    virtual void mt_Format_Exit_Function(const char* function_name) = 0;
    virtual void mt_Format_On_Evenement(const char* event_name) = 0;
    virtual void mt_Format_Stop_Evenement(const char* event_name) = 0;
    virtual void mt_Format_Start_Block(const char* block_name) = 0;
    virtual void mt_Format_End_Block(const char* block_name) = 0;
    void mt_Unstack_Entries_For_Stop_Log(void);
private:
    std::stack<std::string> m_functions, m_events, m_blocks;
    std::stack<void (Logger::*)(void)> m_stack_entries;
    void mt_Manage_Format_Entrance(const char* name, std::stack<std::string>& stack, void (Logger::*function)(const char*));
    void mt_Manage_Format_Exit(std::stack<std::string>& stack, void (Logger::*function)(const char*));

// Documentation
    /** \class Logger
        \brief Concretise partiellement et implemente la methode estValide
    **/
};

template<typename T>
ILogger& operator<<(ILogger& log, const T& msg)
{
    return log.mt_Log(msg);
}
/** \fn template<typename T> ILogger& operator<<(ILogger& log, const T& msg)
    \brief Surcharge de l'operateur d'insertion pour le log
    \param[in, out] log Le log
    \param[in] msg la donnee a log
    \return log.
**/

#endif // _ILOGGER_H
