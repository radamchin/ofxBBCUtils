

#include "iApp.h"

string iApp::app_name = "iApp";
string iApp::app_version = "1.0.0";

iApp::iApp(string _app_name, string _app_version) {
    
    if(_app_name != "") app_name = _app_name;
    if(_app_version != "") app_version = _app_version;
    
    logHeader(app_name, app_version);
    
    cursor_timer = ofGetElapsedTimeMillis() + cursor_duration_ms;
    
  //  ofRegisterMouseEvents(this);
    // ofRegisterKeyEvents(this);
    // ofRegisterGetMessages(this);
    // ofRegister
    
   // ofAddListener(ofEvents().update, this, &iApp::update);
    
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
            
            // Cursor show and hide not working on mac in 0.8.0 : using workaroud from http://forum.openframeworks.cc/t/ofhidecursor-not-working-on-osx-10-8-v0-8-0/13379/3?u=adamh
            // Working in 0.8.1 so do a OF compile check here
            
            #ifdef __APPLE__
                CGDisplayHideCursor(NULL);
            #else
                ofHideCursor();
            #endif
            
            cout << " hideCursor " << ofGetElapsedTimeMillis() << endl;
            cursor_visible = false;
        }
    }
    
}

void iApp::cursorUpdate() {
    
  //  cout << "cursorUpdate " << ofGetElapsedTimeMillis() << endl;
    
    if(!cursor_visible) {
        cout << " showCursor " << ofGetElapsedTimeMillis() << endl;
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
    
}


//-----------------------------------------------------------------------------
void iApp::logHeader(const string& _name, const string& _version) {
    ofLogNotice("");
    ofLogNotice("--------------------------------------");
    ofLogNotice("--- START ") << _name << " app v" << _version << " @ " << ofGetTimestampString("%H:%M:%S %d-%m-%Y");
    // TODO: log OS version and name + opengl properties + OF props, free gpu memory?
    ofLogNotice("--------------------------------------");
}

void iApp::logFooter(const string& _name, const string& _version) {
    ofLogNotice("--------------------------------------");
    ofLogNotice("--- STOP ") << _name << " app v" << _version << " @ " << ofGetTimestampString("%H:%M:%S %d-%m-%Y");
    ofLogNotice("--------------------------------------");
}

//-----------------------------------------------------------------------------