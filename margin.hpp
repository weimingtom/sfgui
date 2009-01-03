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
 * \file margin.hpp
 * \brief A simple struct for margin
 * \author TANGUY Arnaud <arn.tanguy@gmail.com>
 * \date 2009 
 * \version 0.1
 */


#ifndef __MARGIN_HPP__
#define __MARGIN_HPP__

namespace sfgui {

/** \brief Struct which contains margin values 
 *
 * This struc contains the pixel spacing from each border of an object. The function
 * SetMargin is provided for convenience as it set all the margin with the same value.
 */
struct Margin
{
	float Left; ///< Left margin value
	float Right; ///< Right margin value
	float Top; ///< Top margin value
	float Bottom; ///< Bottom margin value
	void SetMargin(float);
};
}


#endif

