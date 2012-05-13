/*
 * File:   WorldTest.cpp
 * Author: davide
 *
 * Created on May 13, 2012, 4:02:42 PM
 */

#include "WorldTest.h"
#include "World.h"


CPPUNIT_TEST_SUITE_REGISTRATION(WorldTest);

WorldTest::WorldTest() {
}

WorldTest::~WorldTest() {
}

void WorldTest::setUp() {
}

void WorldTest::tearDown() {
}

void WorldTest::testGetPlaneById() {
    int id;
    World world;
    Plane* result = world.GetPlaneById(id);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void WorldTest::testGetHeight() {
    World world;
    float result = world.getHeight();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void WorldTest::testGetWidth() {
    World world;
    float result = world.getWidth();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

