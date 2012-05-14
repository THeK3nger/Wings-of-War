/*
 * File:   PlaneTest.h
 * Author: davide
 *
 * Created on May 10, 2012, 7:39:11 PM
 */

#ifndef PLANETEST_H
#define	PLANETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../Plane.h"

class PlaneTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(PlaneTest);

    CPPUNIT_TEST(testCanShootTo);
    CPPUNIT_TEST(testGetId);
    CPPUNIT_TEST(testGetLastMove);
    CPPUNIT_TEST(testGetMaxHealth);
    CPPUNIT_TEST(testGetPosition);
    CPPUNIT_TEST(testInflictDamage);
    CPPUNIT_TEST(testMove);
    CPPUNIT_TEST(testMoveIsValid);
    CPPUNIT_TEST(testRemainingHealth);
    CPPUNIT_TEST(testRevertMove);
    
    CPPUNIT_TEST_SUITE_END();

public:
    PlaneTest();
    virtual ~PlaneTest();
    void setUp();
    void tearDown();

private:
    void testCanShootTo();
    void testGetId();
    void testGetLastMove();
    void testGetMaxHealth();
    void testGetPosition();
    void testInflictDamage();
    void testMove();
    void testMoveIsValid();
    void testRemainingHealth();
    void testRevertMove();
    void testSetLastMove();
    void testSetCardSet();
    
    Plane* test_plane;

};

#endif	/* PLANETEST_H */

