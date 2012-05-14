#ifndef CARDTEST_H
#define	CARDTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../Card.h"

class CardTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CardTest);

    CPPUNIT_TEST(testGetCardType);
    CPPUNIT_TEST(testGetMovement);

    CPPUNIT_TEST_SUITE_END();

public:
    CardTest();
    virtual ~CardTest();
    void setUp();
    void tearDown();

private:
    void testGetCardType();
    void testGetMovement();
    
    Card* test_card;

};

#endif	/* CARDTEST_H */

