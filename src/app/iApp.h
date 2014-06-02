/*
 
    iApp: InstalationApp
 
    Collection of utils for running an application in interactive installation type environment
    
    Adam Hinshaw 17 May 2014
 
 
 */

#pragma once

#include "ofMain.h"
#include "ofEvents.h"

#include "BBCUtils.h" // at moment to get at the custom round method for WIN32

///using namespace bbc::utils;

class iApp : public ofBaseApp{
    
	public:
        iApp(string _app_name = "", string _app_version = "");
    
        static string app_name;
        static string app_version;
    
        void setup();
        void update(ofEventArgs& args);
        void draw(ofEventArgs & args);
        
        void keyPressed(ofKeyEventArgs & key);
        void keyReleased(ofKeyEventArgs & key);
    
        void mouseMoved( ofMouseEventArgs & mouse );
        void mouseDragged( ofMouseEventArgs & mouse );
        void mousePressed( ofMouseEventArgs & mouse );
        void mouseReleased( ofMouseEventArgs & mouse );
    
        void windowResized(ofResizeEventArgs & resize);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
        void drawCalibration(int alpha = 255);
    
        void exit(ofEventArgs & args);
    
    protected:
    
        bool auto_hide_cursor;
        bool cursor_visible;
    
        void logHeader(const string& _name, const string& _version);
        void logFooter(const string& _name, const string& _version);
    
    
        int cursor_duration_ms;

    
    private:
        void cursorUpdate();
        void cursorCheck();
        int cursor_timer;
    
};