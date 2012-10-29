#ifndef _H_IMAGERES_
#define _H_IMAGERES_

#include <SFML/Graphics.hpp>
#include "resources/Resource.h"
#include "resources/ResourcesFactory.h"

class ImageRes : public Resource {
public:
    ImageRes();
    ~ImageRes();

    void Load();
    void Unload();

    static Resource* ImageResCreator(std::string id, std::string filename, UInt scope);
    sf::Image& getSFMLImage();

private:
    sf::Image _sfmlimage;
    static ResourcesFactory::Registerer _register_trick;
};

#endif
