#ifndef _H_RESOURCESFACTORY_
#define _H_RESOURCESFACTORY_

#include <map>

#include "wowcommon.h"
#include "resources/Resource.h"

class Resource;

class ResourcesFactory {
public:
    /*!
     * A pointer to a function that create the new specific resource.
     */
    typedef Resource* (*ResourceCreator)(std::string id, std::string filename, UInt scope);

    /*!
     * \brief getSingleton get the unique instance of ResourcesFactory.
     * \return ResourcesManager instance.
     */
    static ResourcesFactory& getSingleton();

    /*!
     * \brief registerProduct register a new resource type to the factory.
     * \param type the new resource type.
     * \param producer a function that produce this type.
     */
    void registerProduct(const std::string &type,
                         ResourcesFactory::ResourceCreator producer);

    /*!
     * \brief createResource create a new resource with the given data.
     * \param type Desired type.
     * \param id Desired ID.
     * \param filename Path to the resource file.
     * \param scope Desired scope.
     * \return A pointer to the new resource.
     */
    Resource* createResource(const std::string &type,
                             const std::string &id,
                             const std::string &filename,
                             const UInt scope);

    /*!
     * \brief The Registerer class is a trick to perform a semi-automatic registration.
     */
    class Registerer {
    public :
        Registerer(const std::string &type, ResourcesFactory::ResourceCreator producer) {
            ResourcesFactory::getSingleton().registerProduct(type,producer);
        }
    };

private:
    ResourcesFactory();
    ~ResourcesFactory();

    ResourcesFactory(ResourcesFactory const&);
    ResourcesFactory &operator=(const ResourcesFactory &) { return *this; }

    // Function executed on program exit.
    static void cleanUp();

    // The Singleton instance of ResourcesFactory.
    static ResourcesFactory* _instance;

    // A data structure that maps a type to the function which creates that type.
    typedef std::map<std::string,ResourceCreator> FactoryMap;
    FactoryMap _factory_map;
};

//////////////////////////////////////////////////
///// INLINE SHORTCUTS

// TODO: Fix this macro.
#define RESOURCE_FACTORY_REGISTER(type,producer) (static ResourcesFactory::Registerer _register_trick((type),(producer)))

/*!
 * \brief RESOURCES_FACTORY_CREATE is a shortcut function that create a new resource.
 * \param type Desired type.
 * \param id Desired ID.
 * \param filename Path to the resource file.
 * \param scope Desired scope.
 * \return A pointer to the new resource.
 */
inline Resource* RESOURCES_FACTORY_CREATE(const std::string &type,
                                          const std::string &id,
                                          const std::string &filename,
                                          const UInt scope)
{
    return ResourcesFactory::getSingleton().createResource(type, id,
                                                           filename, scope);
}

#endif
