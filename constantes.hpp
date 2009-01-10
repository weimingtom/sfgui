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
 * \file 
 * \brief 
 * \author TANGUY Arnaud <arn.tanguy@gmail.com>
 * \date 2009 
 * \version 0.1
 *
 */


#ifndef __CONSTANTES_HPP__
#define __CONSTANTES_HPP__

namespace sfgui {

	/** This enumeration defines the position of an item (such as text). It is used
	 * by widget to define autoposition (like Button which has SetTextPosition...)
	 * */
	enum { Left, ///< Object is on the left
		Right, ///< Object is on the right 
		Center ///< Object is centered
	};
}


#endif

