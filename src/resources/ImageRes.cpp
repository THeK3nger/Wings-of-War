#include "resources/ImageRes.h"

// This declaration is needed to perform an automatic registration.
// Unfortunately in C++ < C++11 I cannot define a static member in the definition.
ResourcesFactory::Registerer ImageRes::_register_trick("image",ImageRes::ImageResCreator);

ImageRes::ImageRes() : Resource() {

}

ImageRes::~ImageRes() {}

void ImageRes::Load() {
    _sfmlimage.LoadFromFile(_filename);
}

void ImageRes::Unload() {

}

Resource* ImageRes::ImageResCreator(std::string id, std::string filename, UInt scope) {
    ImageRes* output = new ImageRes();
    output->setFileName(filename);
    output->setScope(scope);
    output->setID(id);
    return output;
}

sf::Image& ImageRes::getSFMLImage() {
    return _sfmlimage;
}
