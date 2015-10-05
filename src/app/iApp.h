/*
    iApp: InstalationApp
    Collection of utils for running an application in interactive installation type environment
    Adam Hinshaw 17 May 2014
 
    TODO:
        * Add the interaction interupt, timeout stuff from AWM-DP project, reseting on mouse input and having timeout / listeners to expiry events.
        * Could add draw_calibration flag, and call drawCalibration manually in draw.
 
 */

#pragma once

#include "ofMain.h"
#include "ofEvents.h"

#include "BBCUtils.h" // at moment to get at the custom round method for WIN32

#include "Poco/LocalDateTime.h"

class iApp : public ofBaseApp{
    
public:
    
    iApp(string _app_name = "", string _app_version = "", bool _log_to_file = false, bool _archive_logs = true);
    
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
    
    void showCursor();
    void hideCursor(bool permanent = false);
        
protected:
    
    bool canAutoShutdownNow(); // to be extended to abort an auto shutdown
    
    void logHeader();
    void logFooter();
    
    bool log_to_file;
    bool archive_logs;
    
    bool keep_cursor_hidden;
    
    bool auto_hide_cursor;
    bool cursor_visible;
    
    bool auto_shutdown;
    
    Poco::LocalDateTime shutdown_time;
    
    void logSetup(bool appending = true);
    
    int cursor_duration_ms;
    
    bool header_logged;
    
private:
    
    void cursorUpdate();
    void cursorCheck();
    
    int cursor_timer;
    
};