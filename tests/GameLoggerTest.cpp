/*
 * File:   GameLoggerTest.cpp
 * Author: davide
 *
 * Created on May 16, 2012, 11:39:19 PM
 */

#include "GameLoggerTest.h"
#include "GameLogger.h"


CPPUNIT_TEST_SUITE_REGISTRATION(GameLoggerTest);

GameLoggerTest::GameLoggerTest() {
}

GameLoggerTest::~GameLoggerTest() {
}

void GameLoggerTest::setUp() {
    gl = new GameLogger("testlog.log");
}

void GameLoggerTest::tearDown() {
    delete gl;
}

void GameLogger::toLog(std::string message);

void GameLoggerTest::testToLog() {
    std::string message;
    GameLogger gameLogger;
    gameLogger.toLog(message);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

