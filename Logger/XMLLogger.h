#ifndef _XML_LOGGER_H
#define _XML_LOGGER_H 1

#include "ILogger.h"

class XMLLogger : public Logger
{
public:
    XMLLogger(const std::string& file_path, const std::string& root);
    ~XMLLogger();

    virtual void mt_Stop_Log(void);
    virtual ILogger& mt_Log(const std::string& msg);

protected:
    virtual void mt_Format_Entrance_Function(const char* nom_fonction);
    virtual void mt_Format_Exit_Function(const char* nom_fonction);
    virtual void mt_Format_On_Evenement(const char* nom_evenement);
    virtual void mt_Format_Stop_Evenement(const char* nom_evenement);
    virtual void mt_Format_Start_Block(const char* nom_block);
    virtual void mt_Format_End_Block(const char* nom_block);
    //
    void mt_Write_Charactere(char caractere);
    void mt_Write_Tab(void);
    void mt_Start_Mark(const char* balise, const char* nom);
    void mt_End_Mark(const char* balise, const char* nom);
    std::string m_root;
    int m_tab_counter;
    bool m_write_tab;

// Documentation
    /** \class XMLLogger
        \brief Classe permettant de creer un m_log au forma xml
        \author Sylvain JANNIERE
        \date 26/05/2016
    **/
// public
    /** \fn XMLLogger(const std::string& fichier, const std::string& racine)
        \brief Constructeur
        \param[in] fichier Le chemin du fichier dans lequel ecrire
        \param[in] racine La racine du document
        \details Ecrit l'en-tete xml dans le fichier
    **/
    /** \fn ~XMLLogger()
        \brief Si le document n'est pas ferme, appelle \e stopperLog
    **/
    /** \fn virtual void stopperLog(void)
        \brief Ferme proprement le document
        \details appelle la methode \e depilerEntreesPourStopperLog puis ferme la racine et enfin le fichier
    **/
    /** \fn virtual ILogger& m_log(const std::string& msg)
        \brief Permet de log du texte en gerant l'indentation
        \param[in] msg Le message a ecrire dans le document
    **/

// protected
    /** \fn virtual void mettreEnFormeEntreeFonction(const char* nom_fonction)
        \brief Ecrit la chaine '<fonction nom="nom_fonction">' dans le fichier en respectant l'indentation.
        \param[in] nom_fonction Le nom de la fonction
    **/
    /** \fn virtual void mettreEnFormeSortieFonction(const char* nom_fonction)
        \brief Ecrit la chaine '<fonction nom="nom_fonction">' dans le fichier en respectant l'indentation.
        \param[in] nom_fonction Le nom de la fonction
    **/
    /** \fn virtual void mettreEnFormeDebutEvenement(const char* nom_evenement)
        \brief Ecrit la chaine '<fonction nom="nom_evenement">' dans le fichier en respectant l'indentation.
        \param[in] nom_evenement Le nom de l'evenement
    **/
    /** \fn virtual void mettreEnFormeFinEvenement(const char* nom_evenement)
        \brief Ecrit la chaine '<fonction nom="nom_evenement">' dans le fichier en respectant l'indentation.
        \param[in] nom_evenement Le nom de l'evenement
    **/
    /** \fn virtual void mettreEnFormeCommencerBlock(const char* nom_block)
        \brief Ecrit la chaine '<fonction nom="nom_block">' dans le fichier en respectant l'indentation.
        \param[in] nom_block Le nom du block
    **/
    /** \fn virtual void mettreEnFormeTerminerBlock(const char* nom_block)
        \brief Ecrit la chaine '<block nom="nom_block">' dans le fichier en respectant l'indentation.
        \param[in] nom_block Le nom du block
    **/
    /** \fn void ecrireTab(void)
        \brief Indente le document
    **/
    /** \fn void debutBalise(const char* balise, const char* nom)
        \brief Standardise l'ecriture d'une balise
        \param[in] balise Le nom de la balise
        \param[in] nom La valeur de l'attribut "nom"
        \details Formate de la facon suivante : '<balise nom="nom">'
    **/
    /** \fn void finBalise(const char* balise, const char* nom)
        \brief Standardise l'ecriture de la fin d'une balise
        \param[in] balise Le nom de la balise
        \param[in] nom La valeur de l'attribut "nom" qui sera ecrit en commentaire
        \details Formate de la facon suivante : '</balise> <!-- nom -->'
    **/
    /** \var std::string m_racine
        \brief La racine du document
    **/
    /** \var int m_compteur_tab
        \brief Le compteur pour l'indentation du fichier
    **/
    /** \var bool m_ecrire_tab
        \brief Permet de savoir s'il est necessaire d'indenter le document
    **/
};

#endif // _XML_LOGGER_H
