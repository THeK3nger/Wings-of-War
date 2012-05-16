/*
 * File:   GameLoggerTest.h
 * Author: davide
 *
 * Created on May 16, 2012, 11:39:19 PM
 */

#ifndef GAMELOGGERTEST_H
#define	GAMELOGGERTEST_H

#include <cppunit/extensions/HelperMacros.h>

class GameLoggerTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(GameLoggerTest);

    CPPUNIT_TEST(testToLog);

    CPPUNIT_TEST_SUITE_END();

public:
    GameLoggerTest();
    virtual ~GameLoggerTest();
    void setUp();
    void tearDown();

private:
    void testToLog();
    
    GameLogger* gl;
};

#endif	/* GAMELOGGERTEST_H */

