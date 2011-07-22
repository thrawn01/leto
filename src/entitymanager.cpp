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

#include <entitymanager.h>

/*!
 * Create a new entity object and add it to the collection
 */
Entity* EntityManager::create( ) {
    Entity* entity = new Entity(++entitySeq);
    entities.push_back(entity);
    return entity;
}


/*!
 * Return the all entities that have this component
 */
/*boost::ptr_list<Entity> EntityManager::select( const std::string& _name ) {
    MatchComponent match;
    match.name = _name;
    return select( boost::ref(match) );
}*/

/*!
 * Return all entities that pass the truth test
 */
EntityList EntityManager::select( boost::function<bool (Entity* e)> callBack ) {
    EntityList returnValues;
    
    for( EntityIterator it = entities.begin(); it != entities.end(); ++it ) {
        if(callBack(it->get())) {
            returnValues.push_back(it->get());
        }
    }
    return returnValues;
}


/*!
 * Add an component to the entity
 */
bool EntityManager::addComponent( Entity* entity, Component* component ) { 
    entity->components[component->name] = boost::shared_ptr<Component>(component);
}

/*!
 * Get a Component from this entity
 */
Component* EntityManager::getComponent( Entity* entity, const std::string& name ) {
    return entity->components[name].get();
}

/*!
 * Returns true if the entity has this component
 */
bool EntityManager::hasComponent( Entity* entity, const std::string& name ) {
    return (bool)entity->components[name].get();
}

/*!
 * Return an entity with id of
 */
Entity* EntityManager::getEntity( int _id ) {
    for( EntityIterator it = entities.begin(); it != entities.end(); ++it ) {
        if(it->get()->id == _id) {
            return it->get();
        }
    }
    return (Entity*)0;
}

