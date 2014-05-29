/*
	Extends ofxXMLSettings
*/

#include "XmlSettingsEx.h"

namespace bbc {
    namespace utils {
        
        XmlSettingsEx::XmlSettingsEx() {
            
        }
        
        XmlSettingsEx::~XmlSettingsEx() {
            // kill helpers?
        }
        
        ofXml* XmlSettingsEx::getXMLNode(const string& tag, int which) {
            // Return a node as new ofXML object for parsing.
            TiXmlElement *elem = getElementForAttribute(tag, which);
            
            if (elem) {
                helper_xml.loadFromBuffer( makeString(elem) );
            }else{
                helper_xml.clear();
            }
            return &helper_xml;
        }
        
        XmlSettingsEx* XmlSettingsEx::getXmlSettingsExNode(const string& tag, int which) {
            TiXmlElement *elem = getElementForAttribute(tag, which);
            
            XmlSettingsEx *xmls_ex = new XmlSettingsEx();
            
            if(elem) xmls_ex->loadFromBuffer( makeString(elem) );
            
            return xmls_ex;
        }
        
        bool XmlSettingsEx::validNode(const TiXmlNode* node, const string & named) {
            return (!isComment(node)) && (node->ValueStr() == named);
        }
        
        ofxXmlSettings* XmlSettingsEx::getXMLSettingsNode(const string& tag, int which) {
            // Return a node as new ofxXMLSettings object for parsing.
            TiXmlElement *elem = getElementForAttribute(tag, which);
            
            if (elem) {
                helper_xmls.loadFromBuffer( makeString(elem) );
            }else{
                helper_xmls.clear();
            }
            return &helper_xmls;
        }
        
        TiXmlElement* XmlSettingsEx::getNode(const string& tag, int which) {            
            return getElementForAttribute(tag, which);
        }
        
        string XmlSettingsEx::getXMLString(const string& tag, int which) {
            TiXmlElement* elem = getElementForAttribute(tag, which);
            if (elem) return makeString(elem);            
            return "";
        }
        
        void XmlSettingsEx::copyToString(const TiXmlNode* elem, string& str) {
            str = makeString(elem);
        }
                
        string XmlSettingsEx::makeString(const TiXmlElement* elem) {
            TiXmlPrinter printer;
            elem->Accept(&printer);            
            return printer.CStr();
        }
        
        string XmlSettingsEx::makeString(const TiXmlNode* node) {
            TiXmlPrinter printer;
            node->Accept(&printer);
            return printer.CStr();
        }
        
        string XmlSettingsEx::makeString(const ofxXmlSettings* xml) {
            TiXmlPrinter printer;
            xml->doc.Accept(&printer);
            return printer.CStr();
        }
        
        bool XmlSettingsEx::isComment(const TiXmlNode* node) {
            return node->Type() == TiXmlNode::COMMENT; // NodeType::
        }
        
    }
}