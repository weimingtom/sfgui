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

/*!
 * \file checkbox.hpp
 * \brief Class which provides checkbox buttons 
 * \author TANGUY Arnaud <arn.tanguy@gmail.com>
 * \date 2009 
 * \version 0.1
 */


#ifndef __CHECKBOX_HPP__
#define __CHECKBOX_HPP__

#include "object.hpp"

namespace sfgui {
	/**
	 * \brief Class which provides checkbox buttons
	 *
	 * A checkbox is a special sort of button. When you click on it, the state is changed. 
	 * When you click again, the states becomes the default one.
	 * It can be usefull for asking multiple-choice question.
	 */
	class Checkbox : public sfgui::Object
	{
	public:
		Checkbox(sf::RenderWindow *parentWindow);
		Checkbox(sf::RenderWindow *parentWindow, std::string text, bool state=false);
		void Show();
		void CheckEvent(sf::Event);
		void SetCheckedCallback(void(*)());
		void SetUncheckedCallback(void(*)());
		void ManageMouse();
		void Clicked();

		/* Acessors */
		bool IsChecked();
		/* Mutators */
		void SetState(bool);
	private:
		bool m_state; ///< The curent state of the checkbox (clicked or not)

		void (*m_checkedCallback)(); 
		void (*m_uncheckedCallback)();

		void checked();
		void unchecked();
	};
}


#endif

