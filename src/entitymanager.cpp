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
EntityList EntityManager::select( const std::string& _name ) {
    MatchComponent match(_name);
    return select_func( boost::ref(match) );
}

/*!
 * Return all entities that pass the truth test
 */
EntityList EntityManager::select_func( boost::function<bool (Entity* e)> callBack ) {
    EntityList returnValues;
    
    for( EntityIterator it = entities.begin(); it != entities.end(); ++it ) {
        if(callBack(it->get())) {
            returnValues.push_back(*it);
        }
    }
    return returnValues;
}

/*!
 * Return the first entity that has this component
 */
Entity* EntityManager::find( const std::string& _name ) {
    MatchComponent match(_name);
    return find_func( boost::ref(match) );
}

/*!
 * Return the first entity that passes the truth test
 */
Entity* EntityManager::find_func( boost::function<bool (Entity* e)> callBack ) {
    
    for( EntityIterator it = entities.begin(); it != entities.end(); ++it ) {
        if(callBack(it->get())) {
            return it->get();
        }
    }
    return (Entity*)0;
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
 * Removes a component from an entity by name
 */
bool EntityManager::removeComponent( Entity* entity, const std::string& name ) {
    if( hasComponent( entity, name ) ) {
        entity->components.erase(name);
        return true;
    }
    return false;
}

/*!
 * Removes a component from an entity by pointer 
 */
bool EntityManager::removeComponent( Entity* entity, Component* component ) {
    if( hasComponent( entity, component->name ) ) {
        entity->components.erase(component->name);
        return true;
    }
    return false;
}

/*!
 * Remove and delete entity from the collection
 */
bool EntityManager::erase( Entity *entity ) {
    for( EntityIterator it = entities.begin(); it != entities.end(); ++it ) {
        if(it->get() == entity) {
            entities.erase(it);
            return true;
        }
    }
    return false;
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

