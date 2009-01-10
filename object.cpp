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
	/** Load the default background images */
	generalInit();
	SetTheme("data/button/");
}
sfgui::Object::Object(sf::RenderWindow *parentWindow, std::string themePath) : m_parentRenderWindow(parentWindow) {
	/** Construct a graphic object which uses a custom theme instead of the default
	 * one. Instead of changing the theme by SetTheme, it's recomanded to use this
	 * constructor, as it directly loads the right images (it avoid loading images
	 * twices). */
	generalInit();
	SetTheme(themePath);
}
void sfgui::Object::generalInit() {
	/** Initialise the parts shared by all constructors */
	m_mouseHoverCallback = NULL;
	m_text.SetSize(30);
	m_textAlignment = sfgui::Center;
	m_clickCallback = NULL;
	m_isVisible = true;
	m_font = new sf::Font(sf::Font::GetDefaultFont());
}
sfgui::Object::~Object() {
	/** Delete all the pointers, free the image map... */
	delete m_font;
	if(m_Images.size() != 0) {
		std::map<int, sf::Image *>::iterator it;
		for(it=m_Images.begin(); it != m_Images.end(); it++) {
			delete (*it).second;
		}
		m_Images.clear();
	}
}

void sfgui::Object::SetPosition(float x, float y) {
	/** Set the button position. Adjust the text position to keep the text in the
	 * choosen position (center, left, right...) */
	sf::Sprite::SetPosition(x,y);
	sf::Vector2<float> buttonSize(GetSize());
	sf::Rect<float> textRect(m_text.GetRect());
	sf::Vector2<float> textPos;
	if(m_textAlignment == sfgui::Left) {
		textPos.x = x+m_margin.Left;
		textPos.y = y+m_margin.Top+buttonSize.y/2 - textRect.GetHeight()/2;
	}
	else if(m_textAlignment == sfgui::Right) {
		textPos.x = x+buttonSize.x-(textRect.GetWidth()+m_margin.Right);
		textPos.y = y+m_margin.Top+buttonSize.y/2 - (textRect.GetHeight()/2 + m_margin.Bottom);
	}
	else {
		// If not set or is sfgui::CENTER, center the text
		textPos.x = x+m_margin.Left+buttonSize.x/2 - (textRect.GetWidth()/2+m_margin.Right);
		textPos.y = y+m_margin.Top+buttonSize.y/2 - (textRect.GetHeight()/2+m_margin.Bottom);
	}
	m_text.SetPosition(textPos);
}
void sfgui::Object::Move(float x, float y) {
	/** Move the button and adjust the text position */
	SetPosition(GetPosition().x + x, GetPosition().y + y);
}
void sfgui::Object::updateTextPos() {
	/** This function is called internally when the position of the button is
	 * changed, when text changed (...) to adapt the text position so that it stays
	 * to the right alignment */
	SetPosition(GetPosition().x, GetPosition().y);
}
void sfgui::Object::Show() {
	/** Display the object on the parent window if the Object is visible.
	 * \see SetVisible*/
	if (m_isVisible) {
		m_parentRenderWindow->Draw(*this);
		m_parentRenderWindow->Draw(m_text);
	}
}
void sfgui::Object::SetVisible(bool state) {
	/** Set the visibility of the Object : true if visible, false if not
	 */
	m_isVisible = state;
}

void sfgui::Object::SetText(std::string text) {
	/**
	 * Set the button text.
	 */
	int oldTextSize = m_text.GetSize();
	m_text = sf::String(text);
	sfgui::Object::SetTextSize(oldTextSize);
}
std::string sfgui::Object::GetText() {
	return m_text.GetText();
}
void sfgui::Object::SetTextColor(sf::Color &color) {
	m_text.SetColor(color);
}
sf::Color sfgui::Object::GetTextColor() {
	return m_text.GetColor();
}
void sfgui::Object::SetTextFont(sf::Font &font) {
	/** Set the text font.
	 * <b>Warning : </b> For some inherited widets (such as TextEdit) a non
	 * monospaced font will cause problems (like text getting out of the font...).
	 * It is because SFML doesn't provide function to get charachter width (so it is
	 * based on a constant one, wich is get from one character). */
	m_text.SetFont(font);
}
sf::Font sfgui::Object::GetTextFont() {
	return m_text.GetFont();
}
void sfgui::Object::SetTextSize(int size) {
	/** Set size of the text */
	m_text.SetSize(size);
	updateTextPos();
}
float sfgui::Object::GetTextSize() {
	return m_text.GetSize();
}

void sfgui::Object::SetTextAlignment(int al) {
	/** This set the position of the text on the button. You should use one of the
	 * following constant value sfgui::LEFT, sfgui::RIGHT, sfgui::CENTER */
	m_textAlignment  = al;
	updateTextPos();
}

void sfgui::Object::SetTextMargin(float margin) {
	/** Set the global margin. The text will be spaced from the button each border by a
	 * number of pixels. */
	if(margin*2 < GetSize().x && margin*2 < GetSize().y) {
		m_margin.SetMargin(margin);
		updateTextPos();
	} else {
		std::cout<<"Error : margin not set, it is bigger than the object !";
	}
}
void sfgui::Object::SetTextLeftMargin(float margin) {
	/** Set the left margin. Text will be spaced from the left border of the button
	 * */
	if(margin < GetSize().x) {
		m_margin.Left = margin;
		updateTextPos();
	} else {
		std::cerr<<"Error : margin not set, it is bigger than the object !";
	}
}
void sfgui::Object::SetTextRightMargin(float margin) {
	/** Set the right margin. Text will be spaced form the right border of the
	 * button. */
	if(margin < GetSize().x) {
		m_margin.Right = margin;
		updateTextPos();
	} else {
		std::cerr<<"Error : margin not set, it is bigger than the object !";
	}
}
void sfgui::Object::SetTextTopMargin(float margin) {
	/** Set the top margin. Text will be spaced from the top border of the button.
	 * */
	if(margin < GetSize().y) {
		m_margin.Top = margin;
		updateTextPos();
	} else {
		std::cerr<<"Error : margin not set, it is bigger than the object !";
	}
}
void sfgui::Object::SetTextBottomMargin(float margin) {
	/** set the bottom margin. Text will be spaced from the bottom border of the
	 * button */
	if(margin < GetSize().y) {
		m_margin.Bottom = margin;
		updateTextPos();
	} else {
		std::cerr<<"Error : margin not set, it is bigger than the object !";
	}
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
	
	//If a theme is already loaded, free all the images
	if(m_Images.size() != 0) {
		std::map<int, sf::Image *>::iterator it;
		for(it=m_Images.begin(); it != m_Images.end(); it++) {
			delete (*it).second;
		}
		m_Images.clear();
	}

	sf::Vector2<float> oldSize = GetSize();
	sf::Image *Img = new sf::Image;
	if(Img->LoadFromFile(dir+"normal.png")) {
		m_Images[BackgroundNormal] = Img;
	} else {
		std::cerr<<"Warning : Unable to load file "+dir+"button.png";
	}
	Img = new sf::Image;
	if(Img->LoadFromFile(dir+"clicked.png")) {
		m_Images[BackgroundClicked] = Img ;
	} else {
		std::cerr<<"Warning : Unable to load file "+dir+"button_clicked.png";
	}
	Img = new sf::Image;
	if(Img->LoadFromFile(dir+"hover.png")) {
		m_Images[BackgroundHover] = Img ;
	} else {
		std::cerr<<"Warning : Unable to load file "+dir+"button_hover.png";
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
	 * Object::BackgroundHover ... \see sfgui::Object::ButtonStates for the complete
	 * list of backgrounds values*/
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
	if(m_Images.count(BackgroundHover)) {
		SetBackground(BackgroundHover);
	}
	if(m_mouseHoverCallback != NULL)
		(*m_mouseHoverCallback)();
}
void sfgui::Object::MouseNotHover() {
	/** Called when the mouse is not above the button. It restores the default
	 * button theme */
	SetBackground(BackgroundNormal);
}
