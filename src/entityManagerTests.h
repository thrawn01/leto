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
        void testgetEntities( void ) {

            EntityManager entityManager;
            entityManager.create();
            entityManager.create();

            Entity* entity = entityManager.getEntity(1);
            TS_ASSERT_EQUALS( entity->id, 1 );

            entity = entityManager.getEntity(2);
            TS_ASSERT_EQUALS( entity->id, 2 );
           
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
            entityManager.addComponent( entity, new Component("TargetComponent"));

            // Assert we can get the component
            Component* component = entityManager.getComponent( entity, "TargetComponent");
            TS_ASSERT_EQUALS( component->name, "TargetComponent" );

        }

};

