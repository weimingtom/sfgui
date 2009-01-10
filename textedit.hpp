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

#ifndef __TEXTEDIT_HPP__
#define __TEXTEDIT_HPP__

#include "object.hpp"

namespace sfgui {

/**
 * \brief A single line text entry
 *
 * This class provides a single line text entry widget. Thanks to this class, the user
 * can enter text directly in the application, and usefull callbacks are provided, like
 * textChangedCallback, returnPressedCallback.
 *
 * <h2>Small tutorial</h2>
 * If you want to enter text, you must have the item activated. You can activate it by
 * calling the Activate() function (when user click on the TextEdit, this function is
 * automatically called). <br /> 
 * If you want to stop typing text in the widget, you must call the Deactivate()
 * function. <br />
 * <b>Important : you must call the CheckEvent function in the event loop. If you don't,
 * the widget will just be shown, but won't work as he uses internally events to get the
 * typed text, clicks...</b> */
class TextEdit : public sfgui::Object {
public:
	TextEdit(sf::RenderWindow *parentWindow);
	void SetText(std::string );
	void Resize(float, float);

	void AddChar(char);
	void DelChar(int);

	void Activate();
	void Deactivate();

	void CheckEvent(sf::Event Event);
	void SetTextChangedCallback(void(*)(std::string &));
	void SetReturnPressedCallback(void(*)());
	void SetActivatedCallback(void(*)());
	void SetDeactivatedCallback(void(*)());
	void SetCharDeletedCallback(void(*)(unsigned int, char));
	
	enum Mode { ModePassword, ModeNormal };
	void SetMode(int mode);

	void Show();

private:
	std::string m_stdText;
	bool m_itemActive; /**< If true, user can enter text (textedit has focus), if
	false, it is disabled */
	unsigned int m_cursorPosition; /**< Position of the cursor in the string **/
	bool m_showStars; /**< Used to know if text must be replaced by stars */

	void (*m_textChangedCallback)(std::string &); //< The textchanged callback function pointer
	void (*m_deactivatedCallback)(); //< Callback called when the TextEdit is deactivated
	void (*m_activatedCallback)(); //< Callback called when the TextEdit is activated
	void (*m_returnPressedCallback)(); //< The return key pressed callback function pointer
	void (*m_charDeletedCallback)(unsigned int, char); //< When a character is deleted, use this callback

	void textChanged();  
	void charDeleted(unsigned int, char);
	void deactivated();
	void activated();

	void updateTextRect();
};
}
#endif

