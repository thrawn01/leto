/*  This file is part of the Leto libraries
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 *
 *  Copyright (C) 2011 Derrick J. Wippler <thrawn01@gmail.com>
 **/

#ifndef COMPONENT_INCLUDE_H
#define COMPONENT_INCLUDE_H

#include "component.h"
#include "shared_list.hpp"

/*!
 * Represents a Component
 */
class Component {
    
    public:
        // Constructor / Destructor
        Component( const std::string& _name): name(_name) { }
        ~Component() { }

        std::string name;
};

#endif // COMPONENT_INCLUDE_H
