#include <stdlib.h>
#include <map>

#include <tinyxml.h>

#include "wowcommon.h"
#include "resources/Resource.h"
#include "resources/ResourcesManager.h"

using namespace std;

//////////////////////////////////////////////////
///// SINGLETON IMPLEMENTATION
ResourcesManager* ResourcesManager::_instance = 0;

ResourcesManager::ResourcesManager() : _current_scope(0), _resources_count(0) {
    atexit(&cleanUp);
}

ResourcesManager::~ResourcesManager() { }

ResourcesManager &ResourcesManager::getSingleton() {
    if (!_instance) _instance = new ResourcesManager();
    return *_instance;
}

void ResourcesManager::cleanUp() {
    delete _instance;
    _instance = 0;
}

//////////////////////////////////////////////////
///// RESOURCES MANAGER
const UInt ResourcesManager::GLOBAL_SCOPE = 0;

Resource* ResourcesManager::findByID(string id) {
    map<string,Resource*>::iterator it;
    it = _resources[GLOBAL_SCOPE].find(id);
    if (it!=_resources[GLOBAL_SCOPE].end()) return it->second;
    it = _resources[_current_scope].find(id);
    if (it!=_resources[_current_scope].end()) return it->second;
}

void ResourcesManager::clear() {

}

void ResourcesManager::loadResourcesFromXML(string filename) {
    TiXmlDocument document(filename.c_str());
    LOGMESSAGE_PARAM_NO_ENDL("Loading Assets from file",filename);

    if (document.LoadFile()) {
        OK;
        TiXmlElement *pRoot, *pRes; // Various Node Handler
        pRoot = document.FirstChildElement("assets");
        LOGMESSAGE_CONDITIONAL(!pRoot,"ERROR! No assets defined in the XML file!",return);
        pRes = pRoot->FirstChildElement("resource");
        LOGMESSAGE_CONDITIONAL(!pRes,"ERROR! No resource defined in the XML file!",return);

        string id;
        string type;
        string filename;
        UInt scope;
        while (pRes) {
            id = pRes->Attribute("id");
            scope = atoi(pRes->Attribute("source"));

            type = pRes->Attribute("type");

            filename = pRes->GetText();
            // TODO: ResourceFactory(type,id,scope,filename);
        }

    }
}
