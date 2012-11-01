#ifndef _H_RESOURCESMANAGER_
#define _H_RESOURCESMANAGER_
#include <map>

#include "wowcommon.h"
#include "resources/Resource.h"
#include "ResourcesManager.h"

/*!
 * \brief The ResourcesManager class is a singleton class used to manage, load
 * and store any resource you need.
 *
 * Resources are completely defined by user through inheritance from Resource
 * class and ResourceFactory registration.
 *
 * Resources are separated into *scope*. When the ResourceManager change scope
 * it loads every resource in the new scope and unload every resource in the
 * previous scope.
 *
 * The GLOBAL_SCOPE is a special scope that is always loaded (useful for
 * common resources).
 */
class ResourcesManager {
public:
    /*!
     * \brief GLOBAL_SCOPE is a constant for the global scope. It's usually zero.
     */
    const static UInt GLOBAL_SCOPE;

    /*!
     * \brief getSingleton get the unique instance of ResourcesManager.
     * \return ResourcesManager instance.
     */
    static ResourcesManager& getSingleton();

    /*!
     * \brief findByID retrieve a Resource by ID in the current scope (or global).
     * \param id the desired id.
     * \return a resource with the given id.
     */
    Resource* findByID(std::string id);

    /*!
     * \brief clear Destroy every resource in the ResourcesManager.
     * claear function DESTROY every pointer in the resource manager so
     * pay attention! It should be used only on program shutdown.
     */
    void clear();
    // TODO: make clear private and integrate it in a shutdown function?

    /*!
     * \brief setScope set the current scope.
     * \param scope the new scope.
     */
    void setScope(UInt scope);

    /*!
     * \brief getScope returns the current scope.
     * \return the current scope.
     */
    UInt getScope();

    /*!
     * \brief getResourcesCount returns the number of Resources in the Manager.
     * \return the number o Resources.
     */
    UInt getResourcesCount();

    /*!
     * \brief loadResourcesFromXML load resources from XML file.
     *
     * The XML format is:
     *
     *    <assets>
     *        <resource id="resid" type="restype" scope="rescope">RESOURCE_PATH</resource>
     *        ....
     *    </assets>
     *
     * \param filename the resource filename.
     */
    void loadResourcesFromXML(std::string filename);

private:
    // Singleton Instance
    static ResourcesManager* _instance;

    UInt _current_scope;
    UInt _resources_count;

    // Mappa Scope -> ID -> Resource
    // Store Resources
    typedef std::map<UInt, std::map<std::string,Resource*> > ResourceTable;
    ResourceTable _resources;

    // Only ResourcesManager can build ResourceManager.
    ResourcesManager();
    ~ResourcesManager();

    // Not Copyable
    ResourcesManager(ResourcesManager const&);
    ResourcesManager& operator=(ResourcesManager const&);

    // Function executed on program exit.
    static void cleanUp();

    // Load/Unload all the resources in scope `scope`.
    void loadScope(UInt scope);
    void unloadScope(UInt scope);
};

#endif
