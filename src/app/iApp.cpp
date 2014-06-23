

#include "iApp.h"

string iApp::app_name = "iApp";
string iApp::app_version = "1.0.0";


iApp::iApp(string _app_name, string _app_version, bool _log_to_file, bool _archive_logs) {
    
	auto_hide_cursor = true;
    cursor_visible = true;
    
	cursor_duration_ms = 3000;
    
    if(_app_name != "") app_name = _app_name;
    if(_app_version != "") app_version = _app_version;
    
    log_to_file = _log_to_file;
    archive_logs = _archive_logs;
    
    logSetup();
    
    logHeader(app_name, app_version);
    
    cursor_timer = ofGetElapsedTimeMillis() + cursor_duration_ms;

}

void iApp::setup() {
    ofBaseApp::setup();
    ofLogNotice("iApp:setup");
    // NOT SURE THIS WILL WORK?
    
}

void iApp::draw(ofEventArgs & args) {
    ofBaseApp::draw(args);
    
}

void iApp::update(ofEventArgs& args) {
    ofBaseApp::update(args);
    
    if(auto_hide_cursor) cursorCheck();
    
}

void iApp::cursorCheck() {
    
    // cout << "check cursor " << ofGetElapsedTimeMillis() << endl;
    
    if(cursor_visible) {
        if(ofGetElapsedTimeMillis() >= cursor_timer) { // its been still long enough to auto hide it
            
            // Cursor show and hide not working on mac in 0.8.0 : using workaroud from http://forum.openframeworks.cc/t/ofhidecursor-not-working-on-osx-10-8-v0-8-0/13379/3
            // Working in 0.8.1 so do a OF compile check here
            
    #ifdef __APPLE__
            CGDisplayHideCursor(NULL);
    #else
            ofHideCursor();
    #endif
            
           // cout << " hideCursor " << ofGetElapsedTimeMillis() << endl;
            cursor_visible = false;
        }
    }
    
}

void iApp::cursorUpdate() {
    
    //  cout << "cursorUpdate " << ofGetElapsedTimeMillis() << endl;
    
    if(!cursor_visible) {
        //cout << " showCursor " << ofGetElapsedTimeMillis() << endl;
        cursor_visible = true;
        
    #ifdef __APPLE__
        CGDisplayShowCursor(NULL);
    #else
        ofShowCursor();
    #endif
        
    }
    
    cursor_timer = ofGetElapsedTimeMillis() + cursor_duration_ms; // reset timer hid it after 3 seconds of no movement
}

//------------------------------------------------------------------------------------------------------

void iApp::keyPressed(ofKeyEventArgs & key) {
    ofBaseApp::keyPressed(key);
    
}

void iApp::keyReleased(ofKeyEventArgs & key) {
    ofBaseApp::keyReleased(key);
    
}

//------------------------------------------------------------------------------------------------------

void iApp::mouseMoved( ofMouseEventArgs & mouse ) {
    ofBaseApp::mouseMoved(mouse);
    
    if(auto_hide_cursor) cursorUpdate();
}

void iApp::mouseDragged( ofMouseEventArgs & mouse ) {
    ofBaseApp::mouseDragged(mouse);
    
    if(auto_hide_cursor) cursorUpdate();
}

void iApp::mousePressed( ofMouseEventArgs & mouse ) {
    ofBaseApp::mousePressed(mouse);
    
    if(auto_hide_cursor) cursorUpdate();
}

void iApp::mouseReleased( ofMouseEventArgs & mouse ) {
    ofBaseApp::mouseReleased(mouse);
}

//------------------------------------------------------------------------------------------------------

void iApp::windowResized(ofResizeEventArgs & resize) {
    ofBaseApp::windowResized(resize);
    
}

void iApp::dragEvent(ofDragInfo dragInfo) {
    ofBaseApp::dragEvent(dragInfo);
    
}

void iApp::gotMessage(ofMessage msg){
    ofBaseApp::gotMessage(msg);
    
}

void iApp::exit(ofEventArgs & args) {
    ofBaseApp::exit(args);
    logFooter(app_name, app_version);
    
    ofLogToConsole(); // reset logging to file
    
}


//------------------------------------------------------------------------------------------------------

void iApp::drawCalibration(int alpha) {
    
    /*
     Draw a screen calibration graphic, useful for projection calibration,
     */
    
    ofPushStyle();
    
    float sw = 2.0f;
    ofSetLineWidth(sw);
    
    float w = ofGetWidth();
    float h = ofGetHeight();
    
    float cx = w / 2.0;
    float cy = h / 2.0;
    
    float hsw = sw / 2.0;
    
    ofSetCircleResolution(36);
    
    ofSetColor(255, alpha);
    ofNoFill();
    
    // border
    ofRectMode(OF_RECTMODE_CORNER);
    ofRect(hsw, hsw, w-sw, h-sw);
    
    // diagonal lines
    ofLine(hsw, hsw, w+hsw, h-hsw);
    ofLine(-hsw, h-hsw, w-hsw, hsw);
    
    // centre lines
    ofLine(cx, 0, cx, h);
    ofLine(0, cy, w, cy);
    
    // horizontal 1/4 lines
    ofLine(0, h/4, w, h/4);
    ofLine(0, h-h/4, w, h-h/4);
    
    // Draw centre rect & circle
    ofRectMode(OF_RECTMODE_CENTER);
    
    float dim = min(w, h) * .66f;
    
    ofEllipse(cx, cy, dim, dim);
    
    ofSetLineWidth(1.0f);
    
    // Draw circles at the sides
    int n = 8;
    float mini_rad = h / n;
    float y;
    
    for(int i = 0; i<n-1; i++) {
        y = (mini_rad)+(i*mini_rad);
        int c = i % 4;
        switch(c) {
            case 0: ofSetColor(255, alpha); break;
            case 1: ofSetColor(255,0,0, alpha); break;
            case 2: ofSetColor(0,255,0, alpha); break;
            case 3: ofSetColor(0,0,255, alpha); break;
        }
        
        ofEllipse(0, y, mini_rad, mini_rad); // LHS
        ofEllipse(w, y, mini_rad, mini_rad); // RHS
    }
    
    // Draw more comprehensive grid
    
    // do this at the ratio of the screen?
    // TODO: make the ratio dynamic too reading getWidth and getHeight
    float wc = 16.0f;
    float hc = 9.0f;
    
    float grid_x = w / wc;
    float grid_y = h / hc;
    
    ofSetColor(255, alpha);
    
    // vertical lines
    for(int col = 1; col < wc; col++) {
        int gx = round(col * grid_x);
        ofLine(gx, 0, gx, h);
    }
    
    // horizontal lines
    for(int row = 1; row < hc; row++) {
        int gy = round(row * grid_y);
        ofLine(0, gy, w, gy);
    }
    
    ofPopStyle();
    
}


//-----------------------------------------------------------------------------

void iApp::logSetup() {
     
    if(log_to_file) {
        
        if(archive_logs) {
            // TODO: check logs/ dir and zip up anything over 1MB to logs/archive (cmd line zip util? or an addon)
            
            // Mac could use: terminal gzip: http://superuser.com/questions/161706/command-to-gzip-a-folder
            
            // Win could use: win7 cmd option: http://superuser.com/questions/110991/can-you-zip-a-file-from-the-command-prompt-using-only-windows-built-in-capabili
        }
        
        ofLogToFile("logs/" + app_name + ".log", true); // appends
    }
    
    //ofSetLogLevel(OF_LOG_VERBOSE);
    
}


void iApp::logHeader(const string& _name, const string& _version) {
    ofLogNotice("");
    ofLogNotice("--------------------------------------");
    ofLogNotice("--- START ") << _name << " app v" << _version << " @ " << ofGetTimestampString("%H:%M:%S %d-%m-%Y");
    ofLogNotice("--- ") << "oF:" << OF_VERSION_MAJOR << "." << OF_VERSION_MINOR << "." << OF_VERSION_PATCH << " platform:" << ofGetTargetPlatform();
    // TODO: log OS version and name + opengl properties, free gpu memory?
    ofLogNotice("--------------------------------------");
}

void iApp::logFooter(const string& _name, const string& _version) {
    ofLogNotice("--------------------------------------");
    ofLogNotice("--- STOP ") << _name << " app v" << _version << " @ " << ofGetTimestampString("%H:%M:%S %d-%m-%Y");
    ofLogNotice("--------------------------------------");
}


//-----------------------------------------------------------------------------