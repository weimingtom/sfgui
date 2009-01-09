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

#include "button.hpp"

sfgui::Button::Button(sf::RenderWindow *parentWindow) : Object(parentWindow) {
	/**
	 * Create a Button on the parent window.
	 */
	generalInit();
}
sfgui::Button::Button(sf::RenderWindow *parentWindow, std::string themePath) : Object(parentWindow, themePath) {
	generalInit();
}
void sfgui::Button::generalInit() {
	m_text.SetColor(sf::Color(255,255,255));
	m_text.SetSize(30);
	m_textAlignment = sfgui::Center;
	m_margin.SetMargin(2);
}





