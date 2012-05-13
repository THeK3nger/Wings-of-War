/*
 * File:   WorldTest.h
 * Author: davide
 *
 * Created on May 13, 2012, 4:02:42 PM
 */

#ifndef WORLDTEST_H
#define	WORLDTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../World.h"

class WorldTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(WorldTest);

    CPPUNIT_TEST(testGetPlaneById);
    CPPUNIT_TEST(testGetHeight);
    CPPUNIT_TEST(testGetWidth);

    CPPUNIT_TEST_SUITE_END();

public:
    WorldTest();
    virtual ~WorldTest();
    void setUp();
    void tearDown();

private:
    void testGetPlaneById();
    void testGetHeight();
    void testGetWidth();
    
    World* testworld;

};

#endif	/* WORLDTEST_H */

