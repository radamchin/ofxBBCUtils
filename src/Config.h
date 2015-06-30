/*
    Config (Singleton), extends ofxXMLSettings 
    Loads app configuration properties from xml file.
*/

#pragma once

#ifndef BBC_CONFIG
#define BBC_CONFIG

#include "XmlSettingsEx.h"

#define CONFIG_GET(_key, _attr, _default) bbc::utils::Config::instance()->getAttribute("config:"_key, _attr, _default)
#define CONFIG_GET_FROM_INDEX(_key, _attr, _default, _which) bbc::utils::Config::instance()->getAttributeN("config:"_key, _attr, _default, _which)

namespace bbc {
	namespace utils {
        
        class Config : public XmlSettingsEx {
            
            public:
                static string data_file_path;
                
                static Config* instance(); // pointer to itself
                
                bool load_success;
                           
            protected:
                Config(); // hidden constuctor
        
        };
        
    }
}

#endif
