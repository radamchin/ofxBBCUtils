/*
    Extension of ofXMLSettings
 
    Adds methods to get at node structures and other utilities
    
    Adam Hinshaw
 
 */

#pragma once

#ifndef BBC_XML_SETTINGS_EX
#define BBC_XML_SETTINGS_EX

#include "ofxXmlSettings.h"
#include "ofXml.h"

namespace bbc {
	namespace utils {
        
        class XmlSettingsEx : public ofxXmlSettings {
            
            public:
            
                XmlSettingsEx();
                ~XmlSettingsEx();
                
                string getXMLString(const string& tag, int which = 0);
                
                XmlSettingsEx* getXmlSettingsExNode(const string& tag, int which = 0);
                ofxXmlSettings* getXMLSettingsNode(const string& tag, int which = 0);
            
                int		getAttributeN(const string& tag, const string& attribute, int defaultValue, int which = 0);
                double	getAttributeN(const string& tag, const string& attribute, double defaultValue, int which = 0);
                string	getAttributeN(const string& tag, const string& attribute, const string& defaultValue, int which = 0);
            
                ofXml* getXMLNode(const string& tag, int which = 0);
            
                TiXmlElement* getNode(const string& tag, int which = 0);
            
                bool validNode(const TiXmlNode* node, const string & named);
            
                void copyToString(const TiXmlNode* elem, string& str);
                
                string makeString(const TiXmlElement* elem);
                string makeString(const TiXmlNode* node);
                string makeString(const ofxXmlSettings* xml);
                
                bool isComment(const TiXmlNode* node);
                
            protected:
                
                ofxXmlSettings helper_xmls; // Used to return nodes etc.
                ofXml helper_xml; // Used to return nodes etc.
            
        };
        
    }
}

#endif