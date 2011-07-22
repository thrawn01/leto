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

#ifndef SHARED_LIST_INCLUDE_H
#define SHARED_LIST_INCLUDE_H

#include <list>
#include <boost/shared_ptr.hpp>

    template <class T>
    class shared_list : public std::list<boost::shared_ptr<T> > {
        
        typedef std::list<boost::shared_ptr<T> > base;

        public:
            void push_back( T* value) {
                base::push_back(boost::shared_ptr<T>(value));
            }
            void push_back( boost::shared_ptr<T> value) {
                base::push_back(value);
            }

    };


#endif // SHARED_LIST_INCLUDE_H
