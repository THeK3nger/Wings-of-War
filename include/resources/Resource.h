#ifndef _H_RESOURCE_
#define _H_RESOURCE_

#include "wowcommon.h"

#include <string>

#include "resources/ResourcesFactory.h"

// Forward Declaration
class ResourcesFactory;

/*!
 * \brief The Resource class represents a generic resource for the game.
 */
class Resource {
public:
    Resource() {}
    virtual ~Resource();

    /*!
     * \brief Load load the represented resource.
     */
    virtual void Load() = 0;

    /*!
     * \brief Unload load the represented resource.
     */
    virtual void Unload() = 0;

    // SET AND GET
    void setID(std::string);
    std::string getID();

    void setFileName(std::string new_filename);
    std::string getFileName();

    void setType(std::string new_type);
    std::string getType();

    void setScope(UInt new_scope);
    UInt getScope();

    bool isLoaded();
    void setLoaded();

protected:
    std::string _id;
    std::string _filename;
    std::string _type;
    UInt _scope;
    bool _loaded;
};

#endif
