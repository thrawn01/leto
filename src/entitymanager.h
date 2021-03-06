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
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include "entity.h"
#include "component.h"
#include "shared_list.hpp"

typedef shared_list<Entity>::iterator EntityIterator;
typedef shared_list<Entity> EntityList;

/*!
 * Manages the entity component data structure
 */
class EntityManager : boost::noncopyable {
    
    public:
        // Constructor / Destructor
        EntityManager(): entitySeq(0) { }
        ~EntityManager() { }
       
        // Create a new entity and add it to the collection
        Entity* create( );

        // Remove and delete this entity from the collection
        bool erase( Entity* );

        // Return an entity with id of
        Entity* getEntity( int );

        // Return a component of a specific type
        Component* getComponent( Entity*, const std::string& );
        
        // Returns true if the entity has this component
        bool hasComponent( Entity*, const std::string&  );

        // Add a component to an entity
        bool addComponent( Entity*, Component* );

        // Remove a component from an entity
        bool removeComponent( Entity*, Component* );
        bool removeComponent( Entity*, const std::string& );

        // return the total count of entities
        int count() { return entities.size(); }

        // Return the all entities that have this component
        EntityList select( const std::string& );

        // Return all entities that pass the truth test
        EntityList select_func( boost::function<bool (Entity* e)> f );
        
        // Return the first entity that has this component
        Entity* find( const std::string& );

        // Return the first entity that passes the truth test
        Entity* find_func( boost::function<bool (Entity* e)> f );

        // Entity Collection
        shared_list<Entity> entities;
        // Entity Collection Sequence
        int entitySeq;
};

/*!
 * Call back used by select(const std::string&)
 */
struct MatchComponent { 
    std::string name; 
    
    MatchComponent(const std::string& _name): name(_name) { }

    bool operator()( Entity* e) { 
        if( e->components[name] ) {
            return true;
        }
        return false;
    }; 
};

#endif // ENTITYMANAGER_INCLUDE_H
