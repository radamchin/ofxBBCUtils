/*
    Config (Singleton), extends ofxXMLSettings 
    Loads app configuration properties from xml file.
*/

#pragma once

#ifndef BBC_CONFIG
#define BBC_CONFIG

#include "XmlSettingsEx.h"

#define CONFIG_GET(_key, _attr, _def) bbc::utils::Config::instance()->getAttribute("config:"_key, _attr, _def)

namespace bbc {
	namespace utils {
        
        class Config : public XmlSettingsEx {
            
            public:
                static string data_file_path;
                
                static Config* instance(); // pointer to itself
                
                bool load_success;
                           
            protected:
                Config(); // protected constuctor
        
        };
        
    }
}

#endif