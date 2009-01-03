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
sfgui::Button::~Button() {
}

void sfgui::Button::SetPosition(float x, float y) {
	/** Set the button position. Adjust the text position to keep the text in the
	 * choosen position (center, left, right...) */
	Object::SetPosition(x,y);
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
void sfgui::Button::Move(float x, float y) {
	/** Move the button and adjust the text position */
	SetPosition(GetPosition().x + x, GetPosition().y + y);
}
void sfgui::Button::updateTextPos() {
	/** This function is called internally when the position of the button is
	 * changed, when text changed (...) to adapt the text position so that it stays
	 * to the right alignment */
	SetPosition(GetPosition().x, GetPosition().y);
}

void sfgui::Button::Show() {
	/** Display the button on the parent window */
	m_parentRenderWindow->Draw(*this);
	m_parentRenderWindow->Draw(m_text);
}

void sfgui::Button::SetText(std::string text) {
	/**
	 * Set the button text.
	 */
	m_text = sf::String(text);
	// Default SFML Font
	m_text.SetFont(sf::Font::GetDefaultFont());
	updateTextPos();
}
std::string sfgui::Button::GetText() {
	return m_text.GetText();
}

void sfgui::Button::SetTextColor(sf::Color &color) {
	m_text.SetColor(color);
}
sf::Color sfgui::Button::GetTextColor() {
	return m_text.GetColor();
}
void sfgui::Button::SetTextFont(sf::Font &font) {
	m_text.SetFont(font);
}
sf::Font sfgui::Button::GetTextFont() {
	return m_text.GetFont();
}
void sfgui::Button::SetTextSize(float size) {
	/** Set size of the text */
	m_text.SetSize(size);
	updateTextPos();
}
float sfgui::Button::GetTextSize() {
	return m_text.GetSize();
}

void sfgui::Button::SetTextAlignment(int al) {
	/** This set the position of the text on the button. You should use one of the
	 * following constant value sfgui::LEFT, sfgui::RIGHT, sfgui::CENTER */
	m_textAlignment  = al;
	updateTextPos();
}
void sfgui::Button::SetTextMargin(float margin) {
	/** Set the global margin. The text will be spaced from the button each border by a
	 * number of pixels. */
	if(margin*2 < GetSize().x && margin*2 < GetSize().y) {
		m_margin.SetMargin(margin);
		updateTextPos();
	} else {
		std::cout<<"Error : margin not set, it is bigger than the object !";
	}
}
void sfgui::Button::SetTextLeftMargin(float margin) {
	/** Set the left margin. Text will be spaced from the left border of the button
	 * */
	if(margin < GetSize().x) {
		m_margin.Left = margin;
		updateTextPos();
	} else {
		std::cerr<<"Error : margin not set, it is bigger than the object !";
	}
}
void sfgui::Button::SetTextRightMargin(float margin) {
	/** Set the right margin. Text will be spaced form the right border of the
	 * button. */
	if(margin < GetSize().x) {
		m_margin.Right = margin;
		updateTextPos();
	} else {
		std::cerr<<"Error : margin not set, it is bigger than the object !";
	}
}
void sfgui::Button::SetTextTopMargin(float margin) {
	/** Set the top margin. Text will be spaced from the top border of the button.
	 * */
	if(margin < GetSize().y) {
		m_margin.Top = margin;
		updateTextPos();
	} else {
		std::cerr<<"Error : margin not set, it is bigger than the object !";
	}
}
void sfgui::Button::SetTextBottomMargin(float margin) {
	/** set the bottom margin. Text will be spaced from the bottom border of the
	 * button */
	if(margin < GetSize().y) {
		m_margin.Bottom = margin;
		updateTextPos();
	} else {
		std::cerr<<"Error : margin not set, it is bigger than the object !";
	}
}

