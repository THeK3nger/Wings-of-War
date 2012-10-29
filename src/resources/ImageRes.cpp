#include "resources/ImageRes.h"

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

