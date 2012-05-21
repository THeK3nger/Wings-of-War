#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <tinyxml.h>

#include "CardSetLoader.h"

using namespace std;

CardSetLoader::CardSetLoader() {
}

CardSetLoader::CardSetLoader(const CardSetLoader& orig) {
}

CardSetLoader::~CardSetLoader() {
}

CardSet* CardSetLoader::LoadFromFile(std::string filename) {
    TiXmlDocument document(filename.c_str());
    if (document.LoadFile())
    {
        float x,y,theta;
        Card* tmpcard;
        CardSet* cs = new CardSet;
        TiXmlElement *pRoot, *pCard, *pMove, *pType, *pChild;
        int numcard = 0;
        int count = 0;
        
        pRoot = document.FirstChildElement("cardset");
        pCard = pRoot->FirstChildElement("card");
        
        for( pChild = pRoot->FirstChildElement("card"); pChild; pChild = pChild->NextSiblingElement("card") )
        numcard++;
        
        cs->cards_number = numcard;
        cs->cards = new Card[numcard];
        
        while (pCard)
        {
            pMove = pCard->FirstChildElement("movement");
            
            x = atof(pMove->Attribute("x"));
            y = atof(pMove->Attribute("y"));
            theta = atof(pMove->Attribute("theta"));
            
            pType = pCard->FirstChildElement("type");
            const char* type = pType->GetText();
            Card::CType ctype;
            if (strcmp(type,"L_STEER"))
            {
                cout << "LSTEER" << endl;
                ctype = Card::L_STEER;
            }
            else if (strcmp(type,"R_STEER"))
            {
                cout << "RSTEER" << endl;
                ctype = Card::R_STEER;
            }
            else
            {
                cout << "DRITTO!" << endl;
                ctype = Card::STRAIGHT;
            }
            cs->cards[count].setType(ctype);
            cs->cards[count].setMovement(x,y,theta);
            count++;
            pCard = pCard->NextSiblingElement("card");
        }
        return cs;
    }
    else
    {
        cout << "Error XML Loading" << endl;
    }
    
}
