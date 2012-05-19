#include <iostream>

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
        TiXmlElement *pRoot, *pCard;
        pRoot = document.FirstChildElement("cardset");
        pCard = pRoot->FirstChildElement("card");
        while (pCard)
        {
            cout << pCard->Attribute("x") << endl;
            pCard = pCard->NextSiblingElement("card");
        }
    }
    else
    {
        cout << "Error XML Loading" << endl;
    }
    
}
