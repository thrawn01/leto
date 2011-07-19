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

#ifndef ENTITYMANAGER_INCLUDE_H
#define ENTITYMANAGER_INCLUDE_H

#include <assert.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>

#include "entity.h"
#include "component.h"

/*!
 * Manages the entity component data structure
 */
class EntityManager {
    
    public:
        // Constructor / Destructor
        EntityManager();
        ~EntityManager();
       
        // Create a new entity and add it to the collection
        bool create();

        // Remove this entity from the Collection
        bool remove( Entity& );

        // Get an entity 
        Entity getEntity(int);

        // Return all the components for this entity
        boost::ptr_vector<Component> getComponents( Entity& );

        // Return a component of a specific type
        Component& getComponent( Entity&, std::string& );
        
        // Returns true if the entity has this component
        bool hasComponent( Entity&, std::string&  );

        // Add a component to an entity
        bool addComponent( Entity&, Component& );

        // Remove a component from an entity
        bool removeComponent( Entity&, Component& );
        bool removeComponent( Entity&, std::string& );

        // return the total count of entities
        int count();

        /* 
        // Return all entities that have this component
        boost::ptr_vector<Entity> select( std::string& );

        // Return all entities the function returns true for
        boost::ptr_vector<Entity> select( **func() );

        // Return the first entity that passes the truth test
        boot::ptr_vector<Entity> find( **func() );
        */

        // Get Error messages generated by this class or subclass
        virtual std::string mGetError( void ) { std::string msg = _streamErrorMsg.str(); _streamErrorMsg.str(""); return msg; }
        std::string mGetWarning( void ) { return _streamWarningMsg.str(); }

        // Set Warning messages for this class or subclass
        void mSetWarning( const std::string& msg ) { _streamWarningMsg.str(msg); }

        // Set Error messages for this class or subclass
        void mSetError( const std::string& msg ) { _streamErrorMsg.str(msg); }

        // Clear the stream then return a reference to it so we can set it
        std::stringstream& mSetError() { _streamErrorMsg.str(""); return _streamErrorMsg; }

        // Clear the stream then return a reference to it so we can set it
        std::stringstream& mSetWarning() { _streamWarningMsg.str(""); return _streamWarningMsg; }

        // The Error String
        std::stringstream _streamErrorMsg;

        // The warning message
        std::stringstream _streamWarningMsg;
};

#endif // ENTITYMANAGER_INCLUDE_H