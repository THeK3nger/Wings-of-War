/*
 * File:   PlaneTest.cpp
 * Author: davide
 *
 * Created on May 10, 2012, 7:39:11 PM
 */

#include "PlaneTest.h"
#include "Plane.h"


CPPUNIT_TEST_SUITE_REGISTRATION(PlaneTest);

PlaneTest::PlaneTest() {
}

PlaneTest::~PlaneTest() {
}

void PlaneTest::setUp() {
    test_plane = new Plane(1, 20, 0, 0, 0);
}

void PlaneTest::tearDown() {
    delete test_plane;
}

void PlaneTest::testCanShootTo() {
    Plane target1 = Plane(2, 20, 5, 0, 0);
    Plane target2 = Plane(3, 20, -5, 0, 0);
    CPPUNIT_ASSERT(test_plane->canShootTo(target1));
    CPPUNIT_ASSERT(!(test_plane->canShootTo(target2)));
}

void PlaneTest::testGetId() {
    CPPUNIT_ASSERT(test_plane->getId() == 1);
}

void PlaneTest::testGetLastMove() {
    CPPUNIT_FAIL("Not Yet Implemented!");
}

void PlaneTest::testGetMaxHealth() {
    CPPUNIT_ASSERT(test_plane->getMaxHealth() == 20);
}

void PlaneTest::testGetPosition() {
    float* positionout = new float[3];
    test_plane->getPosition(positionout);
    CPPUNIT_ASSERT(positionout[0] == 0);
    CPPUNIT_ASSERT(positionout[1] == 0);
    CPPUNIT_ASSERT(positionout[2] == 0);
    delete positionout;
}

void PlaneTest::testInflictDamage() {
    test_plane->inflictDamage(5);
    CPPUNIT_ASSERT_EQUAL(15, test_plane->remainingHealth());
}

void PlaneTest::testMove() {
    CPPUNIT_FAIL("Not Yet Implemented!");
}

void PlaneTest::testMoveIsValid() {
    CPPUNIT_FAIL("Not Yet Implemented!");
}

void PlaneTest::testRemainingHealth() {
    CPPUNIT_ASSERT_EQUAL(20, test_plane->remainingHealth());
}

void PlaneTest::testRevertMove() {
    CPPUNIT_FAIL("Not Yet Implemented!");
}

void PlaneTest::testSetLastMove() {
    CPPUNIT_FAIL("Not Yet Implemented!");
}

