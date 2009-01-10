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

#include "checkbox.hpp"

sfgui::Checkbox::Checkbox(sf::RenderWindow *parentWindow) : Object(parentWindow) {
	SetTheme("data/checkbox/");
	Resize(300,300);
	m_state=false;
	m_checkedCallback = NULL;
	m_uncheckedCallback = NULL;
}
void sfgui::Checkbox::Show() {
	m_parentRenderWindow->Draw(*this);
	m_parentRenderWindow->Draw(m_text);
}

sfgui::Checkbox::Checkbox(sf::RenderWindow *parentWindow, std::string text, bool state) : sfgui::Object(parentWindow) {
	std::cout<<text;
	if(state) {
	};
}

/* =========== Acessors =================*/
bool sfgui::Checkbox::IsChecked() {
	/**  Returns the current state : true if checked, false if not.
	 */
	return m_state;
}
/* ============= Mutators ============ */
void sfgui::Checkbox::SetState(bool state) {
	/** Set the CheckBox state : true for checked, false for unchecked */
	if (state) {
		if(!m_state) {
			Clicked();
		}
	} else {
		if(m_state) Clicked();
	}

}
void sfgui::Checkbox::CheckEvent(sf::Event Event) {
	/**
	 * Call the callbacks functions if needed on the given Event.
	 */
	m_Event= Event;
	ManageMouse();
}
void sfgui::Checkbox::ManageMouse() {
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
}
void sfgui::Checkbox::Clicked() {
	/** Switch the TextBox state. 
	 */
	if(m_state==true) {
		if (m_uncheckedCallback != NULL) {
			(*m_uncheckedCallback)();
		}
		SetBackground(BackgroundNormal);
		m_state=false;

	} else {
		if (m_checkedCallback != NULL) {
			(*m_checkedCallback)();
		}
		SetBackground(BackgroundClicked);
		m_state=true;
	}
}
void sfgui::Checkbox::SetCheckedCallback(void(*checkedCallback)()) {
	/** Set the callback function called when the state is changed to checked
	 */
	m_checkedCallback = checkedCallback;
}
void sfgui::Checkbox::SetUncheckedCallback(void(*uncheckedCallback)()) {
	/** Set the callback function called when the state is changed to unchecked
	 */
	m_uncheckedCallback = uncheckedCallback;
}
void sfgui::Checkbox::checked(){
	/**  Automatically called. Call the checkedCallback if it exists.
	 */
	if(m_checkedCallback != NULL) {
		(*m_checkedCallback)();
	}
}
void sfgui::Checkbox::unchecked() {
	/**  Automatically called. Call the uncheckedCallback if it exists.
	 */
	if (m_uncheckedCallback != NULL) {
		(*m_uncheckedCallback)();
	}
}
