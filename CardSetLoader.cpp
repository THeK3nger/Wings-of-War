#include <iostream>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "CardSetLoader.h"

XERCES_CPP_NAMESPACE_USE

using namespace std;
using namespace xercesc;

CardSetLoader::CardSetLoader() {
}

CardSetLoader::CardSetLoader(const CardSetLoader& orig) {
}

CardSetLoader::~CardSetLoader() {
}

CardSet* CardSetLoader::LoadFromFile(std::string filename) {
    //TODO: Exception Handling...
    XMLPlatformUtils::Initialize();
    XercesDOMParser* parser = new XercesDOMParser();
    
    parser->setValidationScheme(XercesDOMParser::Val_Auto);
    parser->setDoNamespaces(false);
    parser->setDoSchema(false);
    
    parser->parse(filename.c_str());
    if (parser->getErrorCount() != 0)
    {
        std::cerr << "Parsing " << filename;
        std::cerr << " error count: " << parser->getErrorCount() << std::endl;
    }
    else
    {
        DOMNode *pDoc = parser->getDocument();
        const XMLCh* type = pDoc->getNodeName();
    }
}
