/*
 * File:   WoWBrainTest.h
 * Author: davide
 *
 * Created on May 14, 2012, 5:46:28 PM
 */

#ifndef WOWBRAINTEST_H
#define	WOWBRAINTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../WoWBrain.h"

class WoWBrainTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(WoWBrainTest);

    CPPUNIT_TEST(testComputeHeuristic);
    CPPUNIT_TEST(testGetAIPlane);
    CPPUNIT_TEST(testNextValidMoves);
    CPPUNIT_TEST(testReturnBestCards);

    CPPUNIT_TEST_SUITE_END();

public:
    WoWBrainTest();
    virtual ~WoWBrainTest();
    void setUp();
    void tearDown();

private:
    void testComputeHeuristic();
    void testGetAIPlane();
    void testNextValidMoves();
    void testReturnBestCards();
    
    WoWBrain* ai;

};

#endif	/* WOWBRAINTEST_H */

