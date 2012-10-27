#ifndef _H_RESOURCESMANAGER_
#define _H_RESOURCESMANAGER_
#include <map>

#include "wowcommon.h"
#include "resources/Resource.h"
#include "ResourcesManager.h"

class ResourcesManager {
public:
    const static UInt GLOBAL_SCOPE;

    static ResourcesManager& getSingleton();

    Resource* findByID(std::string id);

    void clear();

    void setScope(UInt scope);
    UInt getScope();

    UInt getResourcesCount();

    void loadResourcesFromXML(std::string filename);

private:
    static ResourcesManager* _instance;
    UInt _current_scope;
    UInt _resources_count;

    // Mappa Scope -> ID -> Resource
    typedef std::map<UInt, std::map<std::string,Resource*> > ResourceTable;
    ResourceTable _resources;

    ResourcesManager();
    ~ResourcesManager();

    // not copyable
    ResourcesManager(ResourcesManager const&);
    ResourcesManager& operator=(ResourcesManager const&);

    static void cleanUp();
    void loadScope(UInt scope);
    void unloadScope(UInt scope);
};

#endif
