#ifndef _GUI_MANAGER_LOADER_HPP
#define _GUI_MANAGER_LOADER_HPP 1

#include <string>
#include <vector>

#include "GameStates/GameStateTypes.hpp"
#include "GUI_Element.hpp"

class GUI_Element;
class XMLFileLoader;
class GUI_Manager;
class XML_Element;
class GUI_Interface;

class GUI_Manager_Interface_Loader
{
public:
	~GUI_Manager_Interface_Loader();
	void mt_Prepare(const std::string& file_name, XMLFileLoader& loader, GUI_Manager* target);

private:
	bool mt_Load_Button(const XML_Element& button);
	bool mt_Load_Interface(const XML_Element& element);
	bool mt_Finalize_Interface(const XML_Element& element);

	GUI_Manager* m_target;
	GUI_Interface* m_interface;
	GameStateType m_game_state;
	std::vector<GUI_Element*> m_elements;
};

class GUI_Manager_Style_Loader
{
public:
	~GUI_Manager_Style_Loader();
	void mt_Prepare(const std::string& file_name, XMLFileLoader& loader, GUI_Manager* target);

private:
	bool mt_Load_Style(const XML_Element& style);
	bool mt_Load_State(const XML_Element& state);
	bool mt_Load_Element(const XML_Element& element);
	bool mt_Load_Text(const XML_Element& text);
	bool mt_Load_Background(const XML_Element& background);

	bool mt_Finalize_State(const XML_Element& state);

	void mt_Load_Color(const XML_Element& element, sf::Color& color);

	void mt_Reset_Style(void);

	GUI_Manager* m_target;
	std::string m_style_id;
	GUI_Element_State m_state_id;
	GUI_Style m_style;
};

#endif // !_GUI_MANAGER_LOADER_HPP