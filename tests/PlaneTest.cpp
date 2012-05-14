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
    test_plane = new Plane(1, 20, 0, 0, 0); // if you change x,y,theta here, you have to change the test functions too
}

void PlaneTest::tearDown() {
    delete test_plane;
}

void PlaneTest::testCanShootTo() {
    Plane target1 = Plane(2, 20, 5, 0, 0);
    Plane target2 = Plane(3, 20, -5, 0, 0);
    CPPUNIT_ASSERT(test_plane->canShootTo(&target1));
    CPPUNIT_ASSERT(!(test_plane->canShootTo(&target2)));
}

void PlaneTest::testGetId() {
    CPPUNIT_ASSERT(test_plane->getId() == 1);
}

void PlaneTest::testGetLastMove() {
    Card* test_move = new Card(Card::L_STEER,1,1,0);
    test_plane->move(test_move);
    Card::CType res_type = test_plane->getLastMove();
    CPPUNIT_ASSERT(res_type = Card::L_STEER);
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
    float* position = new float[3];
    
    float rotation = -M_PI/4;
    Card test_card(Card::R_STEER, 10, -2, rotation);
    test_plane->move(&test_card);
    test_plane->getPosition(position);
    CPPUNIT_ASSERT(position[0] == 10);
    CPPUNIT_ASSERT(position[1] == -2);
    CPPUNIT_ASSERT(floorf(position[2] * 100 + 0.5)/100 == floorf(rotation * 100 + 0.5)/100);
}

void PlaneTest::testMoveIsValid() {
    CPPUNIT_ASSERT(true);
}

void PlaneTest::testRemainingHealth() {
    CPPUNIT_ASSERT_EQUAL(20, test_plane->remainingHealth());
}

void PlaneTest::testRevertMove() {
    float* position = new float[3];
    Card test_card(Card::R_STEER, 10, -2, -M_PI/3);
    test_plane->move(&test_card);
    test_plane->revertMove(&test_card);
    test_plane->getPosition(position);
    CPPUNIT_ASSERT(position[0] == 0);
    CPPUNIT_ASSERT(position[1] == 0);
    CPPUNIT_ASSERT(position[2] == 0);
}