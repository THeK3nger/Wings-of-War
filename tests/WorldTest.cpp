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
    testworld = new World(100,100);
}

void WorldTest::tearDown() {
    delete testworld;
}

void WorldTest::testGetPlaneById() {
    Plane* plane1 = new Plane(100,10,1,1,0);
    Plane* plane2 = new Plane(200,10,10,10,0);
    testworld->addPlane(plane1);
    testworld->addPlane(plane2);
    Plane* result = testworld->GetPlaneById(100);
    CPPUNIT_ASSERT(plane1 == result);
    result = testworld->GetPlaneById(200);
    CPPUNIT_ASSERT(plane2 == result);
    result = testworld->GetPlaneById(300);
    CPPUNIT_ASSERT(0 == result);
}

void WorldTest::testGetHeight() {
    int height = testworld->getHeight();
    CPPUNIT_ASSERT(height == 100);
}

void WorldTest::testGetWidth() {
    int width = testworld->getWidth();
    CPPUNIT_ASSERT(width == 100);
}

