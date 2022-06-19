//
//  ofParameterSerialiser.h
//  ofxBBCUtils
//
//  Created by Adam Hinshaw on 14/5/22.
//
/*
 
 Save and load a collection of ofParameters to disk as xml or json
 
 Core code taken from ofxGui
 
 TODO: this could just extend ofParameterGroup
 
 */

#ifndef ofParameterSerialiser_h
#define ofParameterSerialiser_h


#include "ofParameter.h"
#include "ofParameterGroup.h"

class ofParameterSerialiser {
    
    ofParameterGroup group;
    
    std::string filename;
    
public:
    
    //------------------------------------------------------------------------------
    ofParameterSerialiser() {
        setName("ofParameterSerialiser");
        filename = "ofparams_serialised";
    }
    
    //------------------------------------------------------------------------------
    ~ofParameterSerialiser() {
        
    }
    
    //------------------------------------------------------------------------------
    void setFilename( const std::string _filename  ) {
        filename = _filename;
    }
    
    //------------------------------------------------------------------------------
    void setName( const std::string name ) {
        // set the name of the group that will be saved as rot
        group.setName(name);
    }
    
    //------------------------------------------------------------------------------
    /* Add parameters of groups to save */
    template< typename T > // ofAbstractParameter
    void addParameter( ofParameter<T> & p ){
        group.add(p);
    }
    
    //------------------------------------------------------------------------------
    /* Generic Add - works with group or param */
    template< typename T >
    void add( ofParameter<T> & p ){
       group.add(p);
    }
    
    //------------------------------------------------------------------------------
    void addGroup( ofParameterGroup & _group ){
         group.add(_group);
    }
    
    //------------------------------------------------------------------------------
    void saveToFile( std::string _filename = ""){
        
        if(_filename.empty()) {
            _filename = filename;
        }
        
        auto extension = ofToLower( ofFilePath::getFileExt(_filename) );
        if(extension == "xml"){
            ofXml xml;
            if( ofFile(_filename, ofFile::Reference).exists() ){
                xml.load(_filename);
            }
            saveTo(xml);
            xml.save(filename);
            
        }else if(extension == "json"){
            ofJson json = ofLoadJson(_filename);
            saveTo(json);
            ofSavePrettyJson(_filename, json);
            
        }else{
            ofLogError("ofParameterSerialiser") << extension << " not recognized, only .xml and .json supported by now";
        }
    }
    
    //------------------------------------------------------------------------------
    void loadFromFile( std::string _filename = "" ){
        
        if(_filename.empty()) {
            _filename = filename;
        }
    
        auto extension = ofToLower(ofFilePath::getFileExt(_filename));
        if(extension == "xml"){
            ofXml xml;
            xml.load(_filename);
            loadFrom(xml);
            
        }else if(extension == "json"){
            ofFile jsonFile(_filename);
            ofJson json = ofLoadJson(jsonFile);
            loadFrom(json);
        }else{
            ofLogError("ofParameterSerialiser") << extension << " not recognized, only .xml and .json supported by now";
        }
    }
    
    //------------------------------------------------------------------------------
    template<class T>
    void saveTo(T & serializer){
        ofSerialize(serializer, group);
    }
    
    //------------------------------------------------------------------------------
    template<class T>
    void loadFrom(T & serializer){
        ofDeserialize(serializer, group);
    }
    
};


#endif /* ofParameterSerialiser_h */
