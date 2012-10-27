#include "wowcommon.h"
#include "resources/Resource.h"

using namespace std;

void Resource::setID(std::string new_id) { _id = new_id; }
string Resource::getID() { return _id; }

void Resource::setFileName(string new_filename) { _filename = new_filename; }
string Resource::getFileName() { return _filename; }

void Resource::setScope(UInt new_scope) { _scope = new_scope; }
UInt Resource::getScope() { return _scope; }

void Resource::setType(RESOURCE_TYPE new_type) { _type = new_type; }
RESOURCE_TYPE Resource::getType() { return _type; }

bool Resource::isLoaded() { return _loaded; }
void Resource::setLoaded() { _loaded = true; }

