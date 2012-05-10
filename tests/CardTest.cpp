#include "CardTest.h"
#include "Card.h"


CPPUNIT_TEST_SUITE_REGISTRATION(CardTest);

CardTest::CardTest() {
}

CardTest::~CardTest() {
}

void CardTest::setUp() {
    Card::CType type = Card::STRAIGHT;
    float mov_x = 1;
    float mov_y = 2;
    float mov_theta = 0;
    this->test_card = new Card(type, mov_x, mov_y, mov_theta);
}

void CardTest::tearDown() {
    delete this->test_card;
}

void CardTest::testCard() {
    Card::CType type;
    float mov_x;
    float mov_y;
    float mov_theta;
    Card card(type, mov_x, mov_y, mov_theta);
}

void CardTest::testGetCardType() {
    Card::CType result = this->test_card->getCardType();
    CPPUNIT_ASSERT(result == Card::STRAIGHT);
}

void CardTest::testGetMovement() {
    float* outMove = new float[3];
    test_card->getMovement(outMove);
    CPPUNIT_ASSERT(outMove[0] == 1);
    CPPUNIT_ASSERT(outMove[1] == 2);
    CPPUNIT_ASSERT(outMove[2] == 0);
    delete outMove;
}

