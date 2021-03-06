#include <stdlib.h>
#include <map>

#include <tinyxml.h>

#include "wowcommon.h"
#include "resources/Resource.h"
#include "resources/ResourcesManager.h"
#include "resources/ResourcesFactory.h"

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
    FAIL;
    LOGMESSAGE_PARAM("ERROR loading resources in scope",_current_scope);
    LOGMESSAGE_PARAM("Resource not found in the current scope!",id);
    return 0;
}

void ResourcesManager::clear() {
    // Map clear always call destructon on its contents but if they are pointers.
    // We have to manually delete all this pointers.
    ResourceTable::iterator scope_it;
    for (scope_it = _resources.begin(); scope_it != _resources.end();scope_it++) {
        map<string,Resource*>::iterator it;
        for (it = (*scope_it).second.begin();it != (*scope_it).second.end();it++) {
            delete (*it).second;
        }
    }
    _resources.clear();
    _resources_count = 0;
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
            scope = atoi(pRes->Attribute("scope"));

            type = pRes->Attribute("type");

            filename = pRes->GetText();
            _resources[scope][id] = RESOURCES_FACTORY_CREATE(type,id,filename,scope);
            _resources_count++;
            pRes = pRes->NextSiblingElement("resource");
        }
    }

    loadScope(ResourcesManager::GLOBAL_SCOPE);
}

void ResourcesManager::loadScope(UInt scope) {
    LOGMESSAGE_PARAM("Loading scope: ",scope);
    map<string,Resource*>::iterator it;
    for (it = _resources[scope].begin();it != _resources[scope].end();it++) {
        (*it).second->Load();
    }
}

void ResourcesManager::unloadScope(UInt scope) {
    map<string,Resource*>::iterator it;
    for (it = _resources[scope].begin();it != _resources[scope].end();it++) {
        (*it).second->Unload();
    }
}

void ResourcesManager::setScope(UInt scope) {
    UInt prev_scope = _current_scope;
    if (prev_scope) {
        unloadScope(prev_scope);
    }
    _current_scope = scope;
    loadScope(scope);
}

UInt ResourcesManager::getScope() {
    return _current_scope;
}
