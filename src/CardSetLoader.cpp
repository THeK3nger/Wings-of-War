#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <tinyxml.h>

#include "wowcommon.h"
#include "CardSetLoader.h"

using namespace std;

CardSetLoader::CardSetLoader() {
}

CardSetLoader::CardSetLoader(const CardSetLoader& orig) {
}

CardSetLoader::~CardSetLoader() {
}

CardSet* CardSetLoader::LoadFromFile(std::string filename) {
    // Load XML file
    TiXmlDocument document(filename.c_str());
    LOGMESSAGE_PARAM_NO_ENDL("Loading CardSet Description",filename);
    if (document.LoadFile())
    {
        OK;
        float x,y,theta; // Card Movement
        CardSet* cs = new CardSet;
        TiXmlElement *pRoot, *pCard, *pMove, *pType, *pChild; // Various Node Handler
        int numcard = 0;
        int count = 0;
        
        pRoot = document.FirstChildElement("cardset");

        LOGMESSAGE_CONDITIONAL(!pRoot,"ERROR! No cardset defined in the XML file!",return 0);

        pCard = pRoot->FirstChildElement("card");

        LOGMESSAGE_CONDITIONAL(!pCard,"ERROR! No card defined in the XML file!",return 0);
        
        for( pChild = pCard; pChild; pChild = pChild->NextSiblingElement("card") )
            numcard++;
        
        cs->cards_number = numcard;
        cs->cards = new Card[numcard];
        
        while (pCard)
        {
            pMove = pCard->FirstChildElement("movement");
            LOGMESSAGE_CONDITIONAL(!pMove,"ERROR! movement tag is not optional!",return 0);
            
            x = atof(pMove->Attribute("x"));
            y = atof(pMove->Attribute("y"));
            theta = atof(pMove->Attribute("theta"));
            
            pType = pCard->FirstChildElement("type");
            LOGMESSAGE_CONDITIONAL(!pType,"ERROR! movement tag is not optional!",return 0);

            const char* type = pType->GetText();
            Card::CType ctype;
            if (strcmp(type,"L_STEER"))
            {
                ctype = Card::L_STEER;
            }
            else if (strcmp(type,"R_STEER"))
            {
                ctype = Card::R_STEER;
            }
            else
            {
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
        FAIL;
        cout << "Error while loading XML file: " << filename << endl;
    }
    
}
