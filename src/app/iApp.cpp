#include "iApp.h"
#include "bbcConfig.h"

#include "Poco/DateTimeParser.h"

string iApp::app_name = "iApp";
string iApp::app_version = "1.0.0";

// Archive (compress) logs that are 1MB
#define IAPP_DEF_LOG_SIZE_ARCH_KB_MAX 1024

using namespace bbc::utils;

iApp::iApp(string _app_name, string _app_version, bool _log_to_file, bool _archive_logs) {
    
    if(!Config::instance()->load_success){
        ofLogError("Config XML failed to load") << Config::data_file_path;
    }else{
        ofLogNotice("Config XML loaded!") << Config::data_file_path;
    }
    
	auto_hide_cursor = true;
    cursor_visible = true;
    
    keep_cursor_hidden = false; // a lock
    
    header_logged = false;
    
	cursor_duration_ms = 3000;
    
    if(_app_name != "") app_name = _app_name;
    if(_app_version != "") app_version = _app_version;
    
    log_to_file = _log_to_file;
    archive_logs = _archive_logs;
    
    if(CONFIG_GET("log", "to_file", false)) {
        if(!log_to_file) { // not already setup
            log_to_file = true;
            logSetup(CONFIG_GET("log", "append", true));
            logHeader(); // relog header so it gets to file
        }
    }else{
        logSetup();
        logHeader();
    }

    ofSetLogLevel((ofLogLevel)CONFIG_GET("log", "level", (int)OF_LOG_NOTICE));
    
    if(Config::instance()->attributeExists("config:window", "fps")) {
		int fps = CONFIG_GET("window", "fps", 60);
        ofSetFrameRate(fps);
        ofLogNotice("iApp set") << "fps=" << fps;
    }
    
	bool vs = CONFIG_GET("window", "vertical_sync", true);
    
    ofSetVerticalSync(vs);
    ofLogNotice("iApp set") << "vertical_sync=" << vs;
    
    // NOTE: to get full fps, dont specify fps and set vertical_sync="0"
    
    if(CONFIG_GET("window", "fullscreen", true)){
		ofToggleFullscreen();
    }
    
    cursor_timer = ofGetElapsedTimeMillis() + cursor_duration_ms;
    
    if(CONFIG_GET("mouse", "hide", false)) { // override auto hide cursor
        auto_hide_cursor = false;
        hideCursor(true);
    }
    
    auto_shutdown = CONFIG_GET("shutdown", "enabled", false);
    
    if(auto_shutdown) { // override auto hide cursor
        
        string time_str = CONFIG_GET("shutdown", "time", "20:20");
        
        ofLogNotice("auto_shutdown setting up with time") << time_str;
        
        Poco::LocalDateTime now;
        
        int time_zone_dif = now.tzd();
        
        Poco::DateTime t = Poco::DateTimeParser::parse("%H:%M:%S", time_str, time_zone_dif);
        
        Poco::LocalDateTime next(now.year(), now.month(), now.day(), t.hour(), t.minute(), t.second());
        
        if(next < now) {
            ofLogNotice("Shutdown time already elapsed for today making it for tomorrow");
            
            // Add a day
            Poco::Timespan dif(0, 24, 0, 0, 0);
            shutdown_time = next + dif;
            
        }else{
            shutdown_time = next;
        }
        
        
    }
    
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
    
    if(keep_cursor_hidden) hideCursor();
    
    if(auto_shutdown) {
        Poco::LocalDateTime now;
        
        if( now > shutdown_time && canAutoShutdownNow() ) {
            ofLogWarning("iApp: AUTO SHUTDOWN was scheduled for now. Terminating app.");
            ofExit();
        }
    }
    
}

bool iApp::canAutoShutdownNow() {
    return true;
}

void iApp::cursorCheck() {
    
    // cout << "check cursor " << ofGetElapsedTimeMillis() << endl;
    
    if(cursor_visible) {
        if(ofGetElapsedTimeMillis() >= cursor_timer) { // its been still long enough to auto hide it
            hideCursor();
           // cout << " hideCursor " << ofGetElapsedTimeMillis() << endl;
            // cursor_visible = false;
        }
    }
    
}

void iApp::toggleCursor() {
    
    if(cursor_visible) {
        hideCursor();
    }else{
        showCursor();
    }
}

void iApp::hideCursor(bool permanent) {
    
   // ofLogNotice("iApp::hideCursor");
    
    // Cursor show and hide not working on mac in 0.8.0 : using workaroud from http://forum.openframeworks.cc/t/ofhidecursor-not-working-on-osx-10-8-v0-8-0/13379/3
    // Is working in 0.8.1 so do a OF compile check here
    #ifdef __APPLE__
        CGDisplayHideCursor(NULL);
    #else
        ofHideCursor();
    #endif
    
    cursor_visible = false;
    
    if(permanent) keep_cursor_hidden = true;
    
}

void iApp::showCursor() {
    
    //ofLogNotice("iApp::showCursor");
    
    #ifdef __APPLE__
        CGDisplayShowCursor(NULL);
    #else
        ofShowCursor();
    #endif
    
    cursor_visible = true;
    
    if(keep_cursor_hidden) keep_cursor_hidden = false;

}

void iApp::cursorUpdate() {
    
    // reset the timer that was counting down to when it restarts
    
    //  cout << "cursorUpdate " << ofGetElapsedTimeMillis() << endl;
    
    if(!cursor_visible) { // >> why??
        // cursor_visible = true;
        showCursor();
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
    logFooter();
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

void iApp::logSetup(bool appending) {
     
    if(log_to_file) {
        
        string log_name = app_name + ".log";
        
        if(archive_logs) {
            
            ofFile f("logs/" + log_name);
            
            if(f.exists()) {
                
                uint64_t sz_kb = f.getSize() / 1024;
                
                if(sz_kb >= IAPP_DEF_LOG_SIZE_ARCH_KB_MAX) {
                    
                    ofFile parent_dir(f.getEnclosingDirectory());
                    
                    #if defined(TARGET_OSX)
                        string zip_cmd = "gzip '" + f.getAbsolutePath() + "'";
                        ofLogNotice("ARCHIVING LOG with") << zip_cmd;
                        string zip_result = ofSystem(zip_cmd);
                        ofLogNotice("zip_result") << zip_result;
                    
                        string rename_cmd =  "mv '" + f.getAbsolutePath() + ".gz' '" + parent_dir.getAbsolutePath() + "/" + ofGetTimestampString("%Y-%m-%d-%H-%M-%S") + "_" + app_name + ".log.gz'";
                        ofLogNotice("RENAMING LOG ARCHIVE with") << rename_cmd;
                        string rename_result = ofSystem(rename_cmd);
                        ofLogNotice("rename_result") << rename_result;
                    #endif
                    
                    #if defined(TARGET_WIN32)
                        // TODO: Win could use: win7 cmd option: http://superuser.com/questions/110991/can-you-zip-a-file-from-the-command-prompt-using-only-windows-built-in-capabili
                    #endif

                }
                
            }
            
        }
        
        ofLogToFile("logs/" + log_name, appending);
    }
    
    
    int level = CONFIG_GET("log", "level", 1);
    // VERBOSE = 0  NOTICE = 1 WARNING = 2 ERROR = 3 FATAL_ERROR = 4 SILENT = 5
    
    if(level >= 0 && level <= (int)OF_LOG_SILENT) {
        ofSetLogLevel( (ofLogLevel)level );
    }
        
}

void iApp::logHeader() {
    ofLogNotice("");
    ofLogNotice("--------------------------------------");
    ofLogNotice("--- START ") << app_name << " app v" << app_version << " @ " << ofGetTimestampString("%H:%M:%S %d-%m-%Y");
    ofLogNotice("--- ") << "oF:" << OF_VERSION_MAJOR << "." << OF_VERSION_MINOR << "." << OF_VERSION_PATCH << " platform:" << ofGetTargetPlatform();
    // TODO: log OS version and name + opengl properties, free gpu memory?
    ofLogNotice("--------------------------------------");
    
    header_logged = true;    
}

void iApp::logFooter() {
    ofLogNotice("--------------------------------------");
    ofLogNotice("--- STOP ") << app_name << " app v" << app_version << " @ " << ofGetTimestampString("%H:%M:%S %d-%m-%Y");
    ofLogNotice("--------------------------------------");
}

//-----------------------------------------------------------------------------