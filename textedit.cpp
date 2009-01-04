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

#include "textedit.hpp"

sfgui::TextEdit::TextEdit(sf::RenderWindow *parentWindow) : Button(parentWindow) {
	m_stdText.reserve(20);
	m_activatedCallback = NULL;
	m_deactivatedCallback = NULL;
	m_textChangedCallback = NULL;
	m_returnPressedCallback = NULL;

	m_text.SetSize(20);
	Resize(300,30);
	SetTextLeftMargin(1);
	SetTextBottomMargin(10);
	SetTextAlignment(sfgui::Left);

	// How many char max ?
	sizeChanged();
}

void sfgui::TextEdit::Resize(float w, float h) {
	sfgui::Button::Resize(w, h);
	sizeChanged();
}
void sfgui::TextEdit::sizeChanged() {
	/** If the size change, this function calculate the new max showable number of
	 * chars, update the text position. 
	 * FIXME : To non monospaced fonts, the max number of size is not correctly
	 * calculated, as it is based on the width of one character. */
	m_text.SetText("a");
	m_nbCharToShow = GetSize().x/m_text.GetRect().GetWidth();
	m_text.SetText("");
	updateTextPos();
}
void sfgui::TextEdit::Activate() {
	/** Activate the TextEdit. When the TextEdit is activated, all pressed keys are
	 * added to the TextEdit string */
	m_itemActive = true;//
	activated();        //
}
void sfgui::TextEdit::Deactivate() {
	/** Deactivate the Textedit. Key you press will no longer be added to the
	 * TextEdit (until Activate() is called) */
	m_itemActive = false;
	deactivated();
}

void sfgui::TextEdit::AddChar(char ch) {
	/** Add one char at the end of the current string */
	m_stdText.push_back(ch);
	textChanged();
}
void sfgui::TextEdit::DelChar(int pos) {
	/** Delete one char from position pos */
	if(!m_stdText.empty()) {
		m_stdText.erase(pos, 1);
		textChanged();
	}
}

void sfgui::TextEdit::SetText(std::string &text) {
	/** Set the text on the TextEdit */
	m_stdText = text;
	//FIXME : Ne pas oublier de coder l'ajout à la sf::String
}
void sfgui::TextEdit::Show() {
	/** Show the TextEdit on the parent window */
	m_parentRenderWindow->Draw(*this);
	m_parentRenderWindow->Draw(m_text);
}

/*============ Callbacks and events ==================*/
void sfgui::TextEdit::CheckEvent(sf::Event event) {
	/** Manage the events : call the needed callbacks functions */
	sfgui::Object::CheckEvent(event);
	m_Event = event;
	unsigned int MouseX = m_parentRenderWindow->GetInput().GetMouseX();
	unsigned int MouseY = m_parentRenderWindow->GetInput().GetMouseY();
	sf::Rect<int> ObjectRect(GetPosition().x, GetPosition().y, GetPosition().x+GetSize().x, GetPosition().y+GetSize().y);
	if (m_Event.Type == sf::Event::MouseButtonPressed) {
		if(ObjectRect.Contains(MouseX, MouseY)) {
			Activate();
		}
		else {
			Deactivate();
		}
	}
	if(m_itemActive) {
		if ((m_Event.Type == sf::Event::KeyPressed)) {
			if(m_Event.Key.Code == sf::Key::Back) 
				DelChar(m_stdText.size()-1);
			else if(m_Event.Key.Code == sf::Key::Space) 
				AddChar(' ');
			else if(m_Event.Key.Code == sf::Key::Comma) 
				AddChar(',');
			else if(m_Event.Key.Code == sf::Key::SemiColon) 
				AddChar(';');
			else
				AddChar(m_Event.Key.Code);
		}
	}
}	
void sfgui::TextEdit::SetTextChangedCallback(void(*textChangedCallback)(std::string &)) {
	/** Set the callback called when the text is modified (add new char, delete
	 * one...) */
	m_textChangedCallback = textChangedCallback;
}
void sfgui::TextEdit::SetReturnPressedCallback(void(*returnPressedCallback)()) {
	/** Set the callback called when the retun key is pressed (it can be
	 * used to know when the user finished his text entry for instance */
	m_returnPressedCallback = returnPressedCallback;
}
void sfgui::TextEdit::SetActivatedCallback(void(*activatedCallback)()) {
	/** Set the callback called when the TextEdit is activated (ie has focus). */
	m_activatedCallback = activatedCallback;
}
void sfgui::TextEdit::SetDeactivatedCallback(void(*deactivatedCallback)()) {
	/** Set the callback called when the TextEdit is deactivated (ie hasn't focus).
	 **/
	m_deactivatedCallback = deactivatedCallback;
}
void sfgui::TextEdit::textChanged() {
	/** If the text is modified, this function is called. It updates the sfString on the screen,
	 * and it call the textChanged callback (if exists) */
	int index = m_stdText.size() - m_nbCharToShow;
	std::string truncatedStr = m_stdText.substr((index >= 0) ? index : 0, m_nbCharToShow);
	m_text.SetText(truncatedStr);
	updateTextPos();
	if(m_textChangedCallback != NULL) {
		(*m_textChangedCallback)(m_stdText);
	}
}
void sfgui::TextEdit::activated() {
	if(m_activatedCallback != 0) {
		(*m_activatedCallback)();
	}
}
void sfgui::TextEdit::deactivated() {
	if(m_deactivatedCallback != NULL) {
		(*m_deactivatedCallback)();
	}
}

