/****************************
* Auteur :Tanguy Arnaud
* Date : 31 décembre 2008
* Version : 1.0
*
* Copyright (C) 2008 TANGUY Arnaud
* 
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 ******************************/

#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include <SFML/Graphics.hpp>
#include "object.hpp"
#include "constantes.hpp"
#include "margin.hpp"
#include <string>

namespace sfgui {

/**
 * \brief A push button
 *
 * This class represents a push button graphic item. 
 * It's certainly one of the most used graphic item, as it provides a simple way to give
 * order to an application (like yes/no buttons...).
 * It provides some signals (call some useful callbacks) like clicked, mouseHover...
 */
class Button : public Object
{
	protected:
	sf::String m_text; 
	int m_textAlignment;
	sfgui::Margin m_margin;
	void updateTextPos();
	void generalInit();
	sf::Font *m_font;

	public:
	Button(sf::RenderWindow *parentWindow);
	Button(sf::RenderWindow *parentWindow, std::string themePath); 
	~Button();
	std::string getText() { /** Get the button text */ return m_text.GetText(); }
	void SetText(std::string text);
	std::string GetText();
	void SetTextColor(sf::Color &);
	sf::Color GetTextColor();
	void SetTextSize(float);
	float GetTextSize();
	void SetTextFont(sf::Font &);
	sf::Font GetTextFont();
	void SetTextAlignment(int);
	void SetTextMargin(float);
	void SetTextLeftMargin(float);
	void SetTextRightMargin(float);
	void SetTextTopMargin(float);
	void SetTextBottomMargin(float);
	void SetPosition(float x, float y);
	void Move(float x, float y);
	void Show();	
};
}


#endif

