#include "stdlib.h"

#include "resources/ResourcesFactory.h"

using namespace std;

//////////////////////////////////////////////////
///// SINGLETON IMPLEMENTATION
ResourcesFactory* ResourcesFactory::_instance = 0;

ResourcesFactory::ResourcesFactory() {
    atexit(&cleanUp);
}

ResourcesFactory::~ResourcesFactory() { }

ResourcesFactory &ResourcesFactory::getSingleton() {
    if (!_instance) _instance = new ResourcesFactory();
    return *_instance;
}

void ResourcesFactory::cleanUp() {
    delete _instance;
    _instance = 0;
}

//////////////////////////////////////////////////
///// RESOURCES FACTORY

void ResourcesFactory::registerProduct(const string &type,
                                       ResourcesFactory::ResourceCreator producer)
{
    _factory_map[type] = producer;
}

Resource* ResourcesFactory::createResource(const string &type,
                                           const string &id,
                                           const string &filename,
                                           const UInt scope)
{
    ResourcesFactory::ResourceCreator theMaker;
    FactoryMap::iterator it = _factory_map.find(type);
    if ( it != _factory_map.end()) {
        theMaker = it->second;
        return theMaker(id,filename,scope);
    }
    return 0;
}
