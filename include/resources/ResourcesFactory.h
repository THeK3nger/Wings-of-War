#ifndef _H_RESOURCESFACTORY_
#define _H_RESOURCESFACTORY_

#include <map>

#include "wowcommon.h"
#include "resources/Resource.h"

class ResourcesFactory {
public:
    typedef Resource* (*ResourceCreator)(std::string id, std::string filename, UInt scope);

    static ResourcesFactory& getSingleton();

    void registerProduct(const std::string &type,
                         ResourcesFactory::ResourceCreator producer);
    Resource* createResource(const std::string &type,
                             const std::string &id,
                             const std::string &filename,
                             const UInt scope);

private:
    ResourcesFactory();
    ~ResourcesFactory();

    ResourcesFactory(ResourcesFactory const&);
    ResourcesFactory &operator=(const ResourcesFactory &) { return *this; }

    static void cleanUp();

    static ResourcesFactory* _instance;

    typedef std::map<std::string,ResourceCreator> FactoryMap;
    FactoryMap _factory_map;
};

//////////////////////////////////////////////////
///// INLINE SHORTCUTS
inline void RESOURCES_FACTORY_REGISTER(const std::string &type,
                                      ResourcesFactory::ResourceCreator producer)
{
    ResourcesFactory::getSingleton().registerProduct(type,producer);
}

inline Resource* RESOURCES_FACTORY_CREATE(const std::string &type,
                                          const std::string &id,
                                          const std::string &filename,
                                          const UInt scope)
{
    return ResourcesFactory::getSingleton().createResource(type, id,
                                                           filename, scope);
}

#endif
