//========================================================================
/**@file	/home/arnaud/programmation/sfml/sfgui/tooltip.hpp
 * @author	TANGUY Arnaud <arn.tanguy@gmail.com>
 * @version	0.1
 * @date
 *	Created:	sam 10 jan 2009 20:26:31 CET \n
 *	Last Update:	sam 10 jan 2009 20:26:31 CET
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

/*------------------------------------------------------------------------
 * Description:	A tooltip object used by all the Objects inherited classes
 * 
 *------------------------------------------------------------------------
 * TODO:	
 *========================================================================
 */

#ifndef _HOME_ARNAUD_PROGRAMMATION_SFML_SFGUI_TOOLTIP_HPP__
#define _HOME_ARNAUD_PROGRAMMATION_SFML_SFGUI_TOOLTIP_HPP__

#include "object.hpp"

class Tooltip : public sfgui::Object {
public:
	Tooltip(sf::RenderWindow *);
};

#endif // _HOME_ARNAUD_PROGRAMMATION_SFML_SFGUI_TOOLTIP_HPP__
