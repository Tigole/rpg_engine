#include "DialogBox.hpp"
#include "TextureManager.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <string>


IDialogBox::~IDialogBox()
{
	/** Nothing **/
}

/*BasicDialogBox::BasicDialogBox(int top_px, int left_px, unsigned int width_px, unsigned int height_px)
	: m_hide_flag(false),
	m_drawable()
{
	/** Nothing ** /
}*/

BasicDialogBox::BasicDialogBox()
	:m_drawable(),
	m_background(),
	m_hide_flag(true)
{
	/** Nothing **/
}

BasicDialogBox::BasicDialogBox(std::unique_ptr<IGUIBackground>& background)
	:m_drawable(),
	m_background(nullptr),
	m_hide_flag(true)
{
	setBackground(background);
}
BasicDialogBox::BasicDialogBox(std::unique_ptr<IGUIBackground>& background, unsigned int left_px, unsigned int top_px)
	:m_drawable(),
	m_background(nullptr),
	m_hide_flag(false)
{
	setBackground(background);
	setScreenPosition(left_px, top_px);
}

BasicDialogBox::BasicDialogBox(std::unique_ptr<IGUIBackground>& background, unsigned int left_px, unsigned int top_px, unsigned int width_px, unsigned int height_px)
	:m_drawable(),
	m_background(nullptr),
	m_hide_flag(false)
{
	setBackground(background);
	setScreenPosition(left_px, top_px);
	setDimensions(width_px, height_px);
}

void BasicDialogBox::setBackground(std::unique_ptr<IGUIBackground>& new_background)
{
	m_background.reset(new_background.release());
	m_hide_flag = m_hide_flag || (m_background == nullptr);
}

void BasicDialogBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (m_hide_flag == false)
	{
		//states.blendMode = sf::BlendMode(sf::BlendMode::SrcColor, sf::BlendMode::DstColor);
		target.draw(*m_background, states);
		for (auto& a : m_drawable)
			target.draw(*a, states);
	}
	else
	{
		/** Nothing **/
	}
}

void BasicDialogBox::hide(bool hide)
{
	m_hide_flag = hide || (m_background == nullptr);
}

void BasicDialogBox::setScreenPosition(unsigned int left_px, unsigned int top_px)
{
	m_background->setScreenPosition(top_px, left_px);
}

void BasicDialogBox::setDimensions(unsigned int width_px, unsigned int height_px)
{
	m_background->setDimensions(width_px, height_px);
}

sf::Vector2u BasicDialogBox::getInsideDimensions(void) const
{
	sf::Vector2u l_ret(0, 0);

	if (m_background != nullptr)
		l_ret = m_background->getUsableDimensions();

	return l_ret;
}