/****************************
 * Auteur :Tanguy Arnaud <arn.tanguy@gmail.com>
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

sfgui::TextEdit::TextEdit(sf::RenderWindow *parentWindow) : Object(parentWindow) {
	m_stdText.reserve(20);
	m_activatedCallback = NULL;
	m_deactivatedCallback = NULL;
	m_textChangedCallback = NULL;
	m_returnPressedCallback = NULL;

	m_text.SetSize(20);
	Resize(300,30);
	SetTextLeftMargin(4);
	SetTextRightMargin(4);
	SetTextBottomMargin(10);
	SetTextAlignment(sfgui::Left);

	updateTextPos();
}

void sfgui::TextEdit::Resize(float w, float h) {
	sfgui::Object::Resize(w, h);
	updateTextRect();
}
void sfgui::TextEdit::Activate() {
	/** Activate the TextEdit. When the TextEdit is activated, all pressed keys are
	 * added to the TextEdit string */
	m_itemActive = true;
	activated();        
}
void sfgui::TextEdit::Deactivate() {
	/** Deactivate the Textedit. Key you press will no longer be added to the
	 * TextEdit (until Activate() is called) */
	m_itemActive = false;
	deactivated();
}

void sfgui::TextEdit::AddChar(char ch) {
	/** Add one char at the end of the current string */
	//Old function
	//m_stdText.push_back(ch);
	//m_cursorPosition++;
	//textChanged();
	//m_stdText.push_back(ch);
	std::string strToAdd(1,ch);
	m_stdText.insert(m_cursorPosition, strToAdd);
	m_cursorPosition++;
	textChanged();
}
void sfgui::TextEdit::DelChar(int pos) {
	/** Delete one char from position pos */
	if(!m_stdText.empty()) {
		charDeleted(pos, m_stdText[pos]);
		m_stdText.erase(pos, 1);
		if(m_cursorPosition>m_stdText.size()) {
			m_cursorPosition = m_stdText.size();
		}
		textChanged();
	}
}

void sfgui::TextEdit::SetText(std::string text) {
	/** Set the text on the TextEdit */
	m_stdText = text;
	m_cursorPosition = m_stdText.size();
	textChanged();
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
			else if(m_Event.Key.Code == sf::Key::Delete) {
				//Delete the char under cursor
				std::cerr<<m_cursorPosition<<std::endl;
				DelChar(m_cursorPosition);
			}
			else if(m_Event.Key.Code == sf::Key::Left) {
				//If left key, move the cursor left, and the text if
				//needed
				if(m_cursorPosition-1 < m_stdText.size()) {
					m_cursorPosition--;
				}
				updateTextRect();
			}
			else if(m_Event.Key.Code == sf::Key::Right) {
				if(m_cursorPosition+1 <= m_stdText.size())
					m_cursorPosition++;
				updateTextRect();
			}
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
void sfgui::TextEdit::SetCharDeletedCallback(void(*callback)(unsigned int, char)) {
	/** Set the callback called when a character is deleted in the TextEdit. 
	 * The callbacks is called whith two params : the position of the deleted char,
	 * and the char itself
	 **/
	m_charDeletedCallback = callback;
}
void sfgui::TextEdit::updateTextRect() {
	//XXX : A little heavy, if someone have a better idea, please contact me...
	//This add characters to m_text until it reach the TextEdit size. 
	std::string trucatedStrInv;
	unsigned int i= m_cursorPosition;
	do {
		std::cout<<"i : "<<i<<std::endl;
		trucatedStrInv.push_back(m_stdText[i]);
		m_text.SetText(trucatedStrInv);
		if(m_text.GetRect().GetWidth() >= GetSize().x-(m_margin.Right+m_margin.Left+5)) {
			break;
		}
		i--;
	} while (i <= m_stdText.size());
	//But the resulting text is inversed, so put it in the right order
	std::string trucatedStr; trucatedStr.reserve(trucatedStrInv.size());
	for(int i=trucatedStrInv.size(); i>0; i--) {
		trucatedStr.push_back(trucatedStrInv[i]);
	}
	m_text.SetText(trucatedStr);
	updateTextPos();
}
void sfgui::TextEdit::textChanged() {
	/** If the text is modified, this function is called. It updates the sf::String on the screen,
	 * and it call the textChanged callback (if exists) */
	updateTextRect();

	//Call the callback function
	if(m_textChangedCallback != NULL) {
		(*m_textChangedCallback)(m_stdText);
	}
}
void sfgui::TextEdit::charDeleted(unsigned int pos, char ch) {
	if(m_charDeletedCallback != 0) {
		(*m_charDeletedCallback)(pos, ch);
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

