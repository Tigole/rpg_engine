#ifndef _XML_LOGGER_H
#define _XML_LOGGER_H 1

#include "ILogger.h"

class XMLLogger : public Logger
{
public:
    XMLLogger(const std::string& file_path, const std::string& root);
    ~XMLLogger();

    virtual void stopLog(void);
    virtual ILogger& log(const std::string& msg);

protected:
    virtual void FormatEntranceFunction(const char* nom_fonction);
    virtual void FormatExiteFunction(const char* nom_fonction);
    virtual void FormatOnEvenement(const char* nom_evenement);
    virtual void FormatStopEvenement(const char* nom_evenement);
    virtual void FormatStartBlock(const char* nom_block);
    virtual void FormatEndBlock(const char* nom_block);
    //
    void writeCharactere(char caractere);
    void writeTab(void);
    void startMark(const char* balise, const char* nom);
    void endMark(const char* balise, const char* nom);
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
