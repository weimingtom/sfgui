/**
 * Test de classe
 */
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

#include "object.hpp"

sfgui::Object::Object(sf::RenderWindow *parentWindow) : m_parentRenderWindow(parentWindow) {
	/**
	 * Construct a simple graphic object */
	m_BackgroundImg = new sf::Image;
	m_mouseHoverCallback = NULL;
	m_clickCallback = NULL;
	 /** Load the default background images */
	SetTheme("data/button/");
}
sfgui::Object::~Object() {
	delete m_BackgroundImg;
}

void sfgui::Object::SetTheme(std::string dir) {
	/**
	 * Load a background theme from a directory containing the right png images :
	 * <ul>
         * 	<li>button.png is the normal background</li>
	 * 	<li>button_clicked.png is the clicked background</li>
	 * 	<li>button_hover.png is the background showed when mouse is above the
	 * 	button</li>
	 * </ul>
	 */
	sf::Vector2<float> oldSize = GetSize();
	sf::Image *Img = new sf::Image;
	if(Img->LoadFromFile(dir+"button.png")) {
		m_Images[BackgroundNormal] = Img;
	} else {
		throw sfgui::Error(("Warning : Unable to load file "+dir+"button.png").c_str());
	}
	Img = new sf::Image;
	if(Img->LoadFromFile(dir+"button_clicked.png")) {
		m_Images[BackgroundClicked] = Img ;
	} else {
		throw sfgui::Error(("Warning : Unable to load file "+dir+"button_clicked.png").c_str());
	}
	Img = new sf::Image;
	if(Img->LoadFromFile(dir+"button_hover.png")) {
		m_Images[BackgroundHover] = Img ;
	} else {
		throw sfgui::Error(("Warning : Unable to load file "+dir+"button_hover.png").c_str());
	}
	m_BackgroundImg = m_Images[BackgroundNormal];
	SetImage(*m_BackgroundImg);
	Resize(oldSize.x, oldSize.y);
}
void sfgui::Object::SetBackground(int background) {
	/** Set a background from an image which is already loaded int this object.
	 * <b>Throws : </b>when an error occurs, like image index doesn't exists, it
	 * throw a sfgui::Error 
	 * \param background It is the num of the background. It must one of the
	 * followings values : Object::BackgroundNormal, Object::BackgroundClicked,
	 * Object::BackgroundHover */
	if(m_Images.count(background) == 0) {
		throw sfgui::Error(("Warning : there is no image for index ")+background);
	} else {
		sf::Vector2<float> oldSize = GetSize();
		m_BackgroundImg = m_Images[background];
		SetImage(*m_BackgroundImg);
		Resize(oldSize.x, oldSize.y);
	}

}

void sfgui::Object::SetClickCallback(void(*clickCallBack)()) {
	/**
	 * Set a pointer to the callback function called when the user click on this
	 * object */
	m_clickCallback = clickCallBack;
}
void sfgui::Object::SetMouseHoverCallback(void(*mouseHoverCallback)()) {
	/**
	 * Set a pointer to the callback function called when the mouse is hover the
	 * button.
	 */
	m_mouseHoverCallback = mouseHoverCallback;
}
void sfgui::Object::CheckEvent(sf::Event Event) {
	/**
	 * Call the callbacks functions if needed on the given Event.
	 */
	m_Event= Event;
	ManageMouse();
}
void sfgui::Object::ManageMouse() {
	/**
	 * Manage the mouse events.
	 */
	unsigned int MouseX = m_parentRenderWindow->GetInput().GetMouseX();
	unsigned int MouseY = m_parentRenderWindow->GetInput().GetMouseY();
	sf::Rect<int> ObjectRect(GetPosition().x, GetPosition().y, GetPosition().x+GetSize().x, GetPosition().y+GetSize().y);
	if (m_Event.Type == sf::Event::MouseButtonPressed) {
		if(ObjectRect.Contains(MouseX, MouseY)) {
			Clicked();
		}

	}
	if(m_Event.Type == sf::Event::MouseButtonReleased) {
		if(ObjectRect.Contains(MouseX, MouseY)) {
			SetBackground(BackgroundHover);
		}
	}
	if(m_Event.Type == sf::Event::MouseMoved) {
		MouseX = m_parentRenderWindow->GetInput().GetMouseX();
		MouseY = m_parentRenderWindow->GetInput().GetMouseY();
		if(ObjectRect.Contains(MouseX, MouseY)) {
			MouseHover();
		}
		else {
			MouseNotHover();
		}
	}
}

void sfgui::Object::Clicked() {
	/** Call the click callback function. It's automatically called by checkEvent,
	 * but you can also call it yourself if needed.
	 */
	SetBackground(BackgroundClicked);
	if(m_clickCallback != NULL)
		(*m_clickCallback)();
}
void sfgui::Object::MouseHover() {
	/** Called when the mouse is above the button */
	SetBackground(BackgroundHover);
	if(m_mouseHoverCallback != NULL)
		(*m_mouseHoverCallback)();
}
void sfgui::Object::MouseNotHover() {
	/** Called when the mouse is not above the button. It restores the default
	 * button theme */
	SetBackground(BackgroundNormal);
}
