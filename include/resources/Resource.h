#include "wowcommon.h"

#include <string>

typedef enum {
    RESOURCE_NULL,
    RESOURCE_GRAPH,
    RESOURCE_AUDIO,
    RESOURCE_FONT
} RESOURCE_TYPE;

/*!
 * \brief The Resource class represents a generic resource for the game.
 */
class Resource {
public:
    Resource() : _id(0), _scope(0), _type(RESOURCE_NULL) {}
    virtual ~Resource();
    virtual void Load() = 0;
    virtual void Unload() = 0;

    void setID(UInt);
    UInt getID();

    void setFileName(std::string new_filename);
    std::string getFileName();

    void setType(RESOURCE_TYPE new_type);
    RESOURCE_TYPE getType();

    void setScope(UInt new_scope);
    UInt getScope();

    bool isLoaded();
    void setLoaded();

protected:
    UInt _id;
    std::string _filename;
    RESOURCE_TYPE _type;
    UInt _scope;
    bool _loaded;
};
