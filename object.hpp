/****************************
 * Auteur :Tanguy Arnaud
 * Date : 
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

#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "error.hpp"
#include <map>


/** \namespace sfgui
 * \brief All graphics widgets
 *
 * This namespace contains all the graphics widgets */
namespace sfgui {

/*! 
 * \brief A simple graphic item
 *
 * This is a very simple object, which is rather useless. It's mostly present to be used
 * as parent by other graphics items classes.
 * This class create a sf::Sprite which represent a graphic item. There are some basic
 * functions to set the general appearance like setBackground.
 * This class can handle some common events which are possibly used by all widgets like
 * clicks, mouse over...
 */
class Object : public sf::Sprite
{
private:
	/* Callback function called when user click on the button */
	void (*m_clickCallback)(); ///< Pointer to the click callback function
	void (*m_mouseHoverCallback)(); /**< Pointer to the callback function called
					when mouse is hover the button */
protected:
	sf::RenderWindow *m_parentRenderWindow; ///< Pointer to the parent sf::RenderWindow
	sf::Image *m_BackgroundImg; ///< Curent background image
	std::map<int, sf::Image *> m_Images;
	enum ButtonStates {BackgroundNormal, BackgroundClicked, BackgroundHover}; 
	sf::Event m_Event; ///< Copy of the current sfml event 

public:
	Object(sf::RenderWindow *parentWindow);
	~Object();
	// throw sfgui::Error if error
	void SetTheme(std::string); //set a background from an image path
	void SetBackground(int background); 


	/** Callbacks **/
	void CheckEvent(sf::Event Event);
	void SetClickCallback(void(*)());
	void SetMouseHoverCallback(void(*)());
	void ManageMouse();
	void Clicked(); 
	void MouseHover();
	void MouseNotHover();
};
}

#endif

