/*
 * File:   WoWBrainTest.cpp
 * Author: davide
 *
 * Created on May 14, 2012, 5:46:28 PM
 */

#include "WoWBrainTest.h"
#include "WoWBrain.h"


CPPUNIT_TEST_SUITE_REGISTRATION(WoWBrainTest);

WoWBrainTest::WoWBrainTest() {
}

WoWBrainTest::~WoWBrainTest() {
}

void WoWBrainTest::setUp() {
    // Create Plane
    Plane* aiplane = new Plane(1,10,0,0,0);
    Plane* enemy   = new Plane(2,10,0,0,0);
    
    // Create world
    World* world = new World(300,300);
    
    // Create Cards
    Card* straight = new Card(Card::STRAIGHT,10,0,0);
    Card* left = new Card(Card::L_STEER,5,-5,0.78);
    Card* right = new Card(Card::R_STEER,5,5,-0.78);
    CardSet* card_set = new CardSet;
    card_set->cards = new Card[3];
    card_set->cards_number = 3;
    card_set->cards[0]=*straight;
    card_set->cards[1]=*left;
    card_set->cards[2]=*right;
    
    aiplane->setCardSet(card_set);
    enemy->setCardSet(card_set);
    world->addPlane(aiplane);
    world->addPlane(enemy);
    ai = new WoWBrain(aiplane,world);
}

void WoWBrainTest::tearDown() {
    delete ai;
}

void WoWBrainTest::testComputeHeuristic() {
    CPPUNIT_ASSERT(false);
}

void WoWBrainTest::testGetAIPlane() {
    CPPUNIT_ASSERT(false);
}

void WoWBrainTest::testNextValidMoves() {
    CPPUNIT_ASSERT(false);
}

void WoWBrainTest::testReturnBestCards() {
    std::vector<Card*> result;
    result = ai->returnBestCards(20);
    Plane* aiplane = ai->getAIPlane();
    aiplane->move(result[0]);
    CPPUNIT_ASSERT(aiplane->getLastMove() == Card::STRAIGHT);
}

