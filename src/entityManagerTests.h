/*  This file is part of the Ollie Test Suite
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
 *  Copyright (C) 2007 Derrick J. Wippler <thrawn01@gmail.com>
 **/

#include "cxxtest/TestSuite.h"
#include <iostream>
#include <fstream>
#include <errno.h>

#include "entitymanager.h"

using namespace std;

// --------------------------------
//  Unit Test for leto.cpp
// --------------------------------
class EntityManagerTests : public CxxTest::TestSuite {

    public: 

        // --------------------------------
        // --------------------------------
        void testCreate( void ) {

            EntityManager entityManager;
            Entity* entity = entityManager.create();
            TS_ASSERT_EQUALS( entity->id, 1 );
           
        }

        // --------------------------------
        // --------------------------------
        void testManageEntities( void ) {

            EntityManager entityManager;
            entityManager.create();
            entityManager.create();

            Entity* entity = entityManager.getEntity(1);
            TS_ASSERT_EQUALS( entity->id, 1 );

            entity = entityManager.getEntity(2);
            TS_ASSERT_EQUALS( entity->id, 2 );
            TS_ASSERT_EQUALS( entityManager.count(), 2 );
         
            // Remove the entity from the colleciton
            TS_ASSERT_EQUALS( entityManager.erase( entity ), true );
            TS_ASSERT_EQUALS( entityManager.count(), 1 );

        }

        // --------------------------------
        // --------------------------------
        void testNoComponent( void ) {

            EntityManager entityManager;
            Entity* entity = entityManager.create();
            TS_ASSERT_EQUALS( entity->id, 1 );

            // Entity has no components
            TS_ASSERT_EQUALS( entityManager.hasComponent( entity, "TargetComponent" ), false );
            TS_ASSERT_EQUALS( entityManager.getComponent( entity, "TargetComponent" ), (Component*)0 );
        
        }

        // --------------------------------
        // --------------------------------
        void testComponentManagement( void ) {

            EntityManager entityManager;

            // Create an entity
            Entity* entity = entityManager.create();
            TS_ASSERT_EQUALS( entity->id, 1 );

            // Add a Component
            entityManager.addComponent( entity, new Component("Target"));
            entityManager.addComponent( entity, new Component("Health"));

            // Assert we can get the component
            Component* component = entityManager.getComponent( entity, "Target");
            TS_ASSERT_EQUALS( component->name, "Target" );

            entityManager.removeComponent( entity, "Target");
            TS_ASSERT_EQUALS( entityManager.getComponent( entity, "Target"), (Component*)0 );

            component = entityManager.getComponent( entity, "Health");
            TS_ASSERT_EQUALS( component->name, "Health" );
            entityManager.removeComponent( entity, component );
            TS_ASSERT_EQUALS( entityManager.getComponent( entity, "Health"), (Component*)0 );

        }

        // --------------------------------
        // --------------------------------
        void testSelectMethods( void ) {

            EntityManager entityManager;

            // Create some entities
            Entity* entity = entityManager.create();
            TS_ASSERT_EQUALS( entity->id, 1 );
            entityManager.addComponent( entity, new Component("Enemy"));
            entityManager.addComponent( entity, new Component("Health"));
            entityManager.addComponent( entity, new Component("Rifle"));

            entity = entityManager.create();
            TS_ASSERT_EQUALS( entity->id, 2 );
            entityManager.addComponent( entity, new Component("Enemy"));
            entityManager.addComponent( entity, new Component("Health"));
            entityManager.addComponent( entity, new Component("Pistol"));

            entity = entityManager.create();
            TS_ASSERT_EQUALS( entity->id, 3 );
            entityManager.addComponent( entity, new Component("Player"));
            entityManager.addComponent( entity, new Component("Health"));
            entityManager.addComponent( entity, new Component("Knife"));

            // Select all the entities that have the 'Enemy' Component
            EntityList list = entityManager.select( "Enemy" );
            // Found 2 enemies
            TS_ASSERT_EQUALS( list.size(), 2 );

            // Find the only Player entity
            entity = entityManager.find("Player");
            TS_ASSERT_EQUALS( entity->id, 3 );
            // Ensure this entity has the player component
            TS_ASSERT( entity->components["Player"].get() != (Component*)0 );
        }
};

