#ifndef CARDSETLOADER_H
#define	CARDSETLOADER_H

#include "Plane.h"

/*!
 * This static class allow to load game data from XML file.
 *
 * This class is NOT instantiable!
 */
class CardSetLoader {
public:
    virtual ~CardSetLoader();
    
    /*!
     * Load a CardSet from an XML file.
     *
     * \param filename URI to filename containing CardSet definition.
     * \return A pointer to the CardSet defined in `filename`.
     */
    static CardSet* LoadFromFile(std::string filename);
    
private:
    CardSetLoader();
    CardSetLoader(const CardSetLoader& orig);

};

#endif	/* CARDSETLOADER_H */

