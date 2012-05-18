#ifndef CARDSETLOADER_H
#define	CARDSETLOADER_H

#include "Plane.h"


class CardSetLoader {
public:
    CardSetLoader();
    CardSetLoader(const CardSetLoader& orig);
    virtual ~CardSetLoader();
    
    static CardSet* LoadFromFile(std::string filename);
    
private:

};

#endif	/* CARDSETLOADER_H */

