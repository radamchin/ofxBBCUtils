
/*
 
 BBCUtils
 
 General utilities, living here until somewhere more organized shows up
 
 Adam Hinshaw 2013
 
 
 */

#pragma once

//#include "ErpEase.h"
//#include "bbcConfig.h"

//#include "RandomBezierAnimator.h"
//#include "BezierAnimator.h"
//#include "FrameTweener.h"

#include "ofMain.h"

#include "Poco/Timestamp.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTime.h"

// For Clipboard access
#if (_MSC_VER)
#include <GLFW/glfw3.h>
#else
#include "GLFW/glfw3.h"
#endif

#if (_MSC_VER)
	// crazy no round function in math.h on win32 (or in OF)
	static inline float round(float f){
		return floor(f + .5);
	}
#endif


#define bbcSQLDateStampFormat "%Y-%m-%d %H:%M:%S"    // "YYYY-MM-DD HH:MM:SS" : Format SQLite needs to save dates (or could just use  DateTimeFormat::SORTABLE_FORMAT for this..)
#define bbcSQLDayFormat "%Y-%m-%d"                   // "YYYY-MM-DD"
#define bbcSQLTimeFormat "%H:%M:%S"                  // "HH:MM:SS"


namespace bbc {
    namespace utils {
		
        static const string getUpTimeStr(bool show_secs = true) {
            // How long uas this app been running? Return formated string of such.
            
            unsigned long total_up_secs = ofGetElapsedTimeMillis() / 1000;
            
            int dys = (int) floor(total_up_secs / 86400); // 86400 == 60 * 60 * 24, seconds in a day.
            int hrs = (int) floor((total_up_secs % 86400) / 3600); // 3600 == 60 * 60. secopnds in an hour
            int mins = (int) floor(((total_up_secs % 86400) % 3600) / 60);
            int secs = (total_up_secs % 86400) % 3600 % 60;
            
            stringstream out;
            out << "up:" << dys << "d," << hrs << "h," << mins << "m," << secs << "s";
            return out.str();
        }
        
        static string secondsToHMS(int totalSeconds) {
            int hours   = floor(totalSeconds / 3600);
            int minutes = floor((totalSeconds - (hours * 3600)) / 60);
            int seconds = round(totalSeconds - (hours * 3600) - (minutes * 60));
            
            return ofToString(hours, 2, '0') + ":" + ofToString(minutes, 2, '0') + ":" + ofToString(seconds, 2, '0');
        }
        
        static string getNowSQLDateStamp() {
            // "2015-02-23 15:39:22"
            Poco::LocalDateTime now;
            return Poco::DateTimeFormatter::format(now, bbcSQLDateStampFormat);
        }
        
        static string getSQLDateStamp(Poco::LocalDateTime & t) {
            return Poco::DateTimeFormatter::format(t, bbcSQLDateStampFormat);
        }
        
        static string getNowSQLDay() {
            // "2015-02-23"
            Poco::LocalDateTime now;
            return Poco::DateTimeFormatter::format(now, bbcSQLDayFormat);
        }
        
        
        
        static string getNowTime() {
            // just time "15:39:22"
            Poco::LocalDateTime now;
            return Poco::DateTimeFormatter::format(now, bbcSQLTimeFormat);
        }
        
        static unsigned int getNowSeconds() {
            return ofGetUnixTime();
        }
        
        static bool isToday(Poco::LocalDateTime & date) {
            Poco::LocalDateTime today;
            
            if(date.day() == today.day() && date.month() == today.month() && date.year() == today.year()) {
                return true;
            }
            
            return false;
        }
        
        static bool isYesterday(Poco::LocalDateTime & date) {
            Poco::LocalDateTime today;
            
            if(date.day() == today.day() && date.month() == today.month() && date.year() == today.year()) {
                return false; // it's today.
            }
            
            Poco::Timespan difference = today - date;
            
          //  int h = difference.totalHours();
          //  int m = difference.totalMinutes();
          //  int s = difference.totalSeconds();
            
            if(difference.totalHours() <= 24) {
                return true;
            }
            
            return false;
        }
        
       /* static string secondsToMS(int totalSeconds) {
            int hours   = floor(totalSeconds / 3600);
            int minutes = floor((totalSeconds - (hours * 3600)) / 60);
            int seconds = round(totalSeconds - (hours * 3600) - (minutes * 60));
            
            return ofToString(minutes) + ":" + ofToString(seconds, 2, '0');
        }
        
        static string minsToHMS(float totalMins) {
            return secondsToHMS((int)(totalMins * 60));
        }
        
        static string minsToMS(float totalMins) {
            return secondsToMS((int)(totalMins * 60));
        }*/
        
        static string msToHMS(int totalMS) {
            
            int totalSeconds = totalMS/1000.0;
            
          //  int ms = totalMS % 1000;
            
            int hours   = floor(totalSeconds / 3600);
            int minutes = floor((totalSeconds - (hours * 3600)) / 60);
            int seconds = round(totalSeconds - (hours * 3600) - (minutes * 60));
            
            return ofToString(hours, 2, '0') + ":" + ofToString(minutes, 2, '0') + ":" + ofToString(seconds, 2, '0');
        }
        
        static string msToMS(int totalMS, bool show_ms = false, int ms_pad = 3) {
            
            int totalSeconds = totalMS/1000.0;
            
            int ms = totalMS % 1000;
            
            int hours   = floor(totalSeconds / 3600);
            int minutes = floor((totalSeconds - (hours * 3600)) / 60);
            int seconds = round(totalSeconds - (hours * 3600) - (minutes * 60));
            
            string ms_str = show_ms ? "." + ofToString(ms, ms_pad, '0') : "";
            
            /*if(show_ms) {
             ms_str = "." + ms_pad ? ofToString(ms, 3, '0') : ofToString(ms);
             }*/

            return ofToString(minutes) + ":" + ofToString(seconds, 2, '0') + ms_str;
        }
        
        static void setClipboard(string clippy) {
            // Found in ofxTextInputField
            // if win32 code not working, could just bail out.
            
            #if defined(TARGET_OSX)
            glfwSetClipboardString( (GLFWwindow*) ofGetWindowPtr()->getCocoaWindow(), clippy.c_str());
            #endif
            
			#if defined(TARGET_WIN32)
            glfwSetClipboardString( (GLFWwindow*) ofGetWindowPtr()->getWin32Window(), clippy.c_str());
            #endif
        }
        
        static const string getClipboard(){
            
            #if defined(TARGET_OSX)
            const char *clip = glfwGetClipboardString((GLFWwindow*) ofGetWindowPtr()->getCocoaWindow());
            #endif
            
            #if defined(TARGET_WIN32)
			const char *clip;
			return "<<THIS NOT CURRENTLY WORKING ON WIN32 SORRY>>";
            //const char *clip = glfwGetClipboardString((GLFWwindow*) ofGetWindowPtr()->getWin32Window());
            #endif
            
            return (clip==NULL) ? "" : string(clip);
        }
        
        static const string getUnixTimeStamp(bool show_ms = false) {
            // get now in format  YYYYMMDDHHMMSSmmm
            ostringstream format;
            format << "%Y%m%d%H%M%S" << (show_ms ? "%i" : "");
            
            return ofGetTimestampString(format.str());
        }

        static void recursiveFileSearchNameContains(const string & path, const string & search_str, vector<string> & results ) {
            
            // Get all files of a folder that contain a string (useful for searching by type, eg ".mp3")
            
            ofDirectory dir;
            
            dir.listDir(path);
            
            for(int i = 0; i < (int)dir.size(); i++){
                
                string file_path = dir.getPath(i);
                
                ofFile file(file_path);
                
                if(file.isDirectory()) {
                    recursiveFileSearchNameContains(file_path, search_str, results);
                }else{
                    if( ofIsStringInString(file_path, search_str) ){
                        results.push_back(file_path);
                    }
                }
                
            }
            
        }
        
        ///////////////////////////////////////////////////////////////////////////////////////
        
        static float getNextMultiple(int n, int multiple) {
            // return next number, from #n that is a multiple of #multiple, but not if #n already multiple
            //
            // see: http://stackoverflow.com/questions/2403631/how-do-i-find-the-next-multiple-of-10-of-any-integer
            
            if (n % multiple){
                n = n + (multiple - n % multiple);
            }
            
            return n;
        }

        //---------------------------------------------------------------------------
        
        // These could have alts. that operate on the string passes instead
        // i.e, void setToUpperCase void setToLowerCase
        
        static string toUpperCase(const string &  str) {
            string strUpper = "";
            
            for( int i=0; i<str.length(); i++ ) {
                strUpper += toupper( str[ i ] );
            }
            
            return strUpper;
        }
        
        static string toLowerCase(const string & str) {
            string strLower = "";
            
            for( int i=0; i<str.length(); i++ ){
                strLower += tolower( str[ i ] );
            }
            
            return strLower;
        }
        
        //---------------------------------------------------------------------------
        
        static string vecToStr(const ofVec3f & v, int places = -1) {
            ostringstream out;
            if(places > -1) {
                out << ofToString(v.x, places) << "," << ofToString(v.y, places) << "," << ofToString(v.z, places);
            }else{
                 out << v.x << "," << v.y << "," << v.z;
            }
            return out.str();
        }

        static void printGLStats() {
            
            // Dump opengl info
            ofLogNotice("\tGL") << "Vendor:   " << (char*)glGetString(GL_VENDOR);
            ofLogNotice("\tGL") << "Renderer: " << (char*)glGetString(GL_RENDERER);
            ofLogNotice("\tGL") << "Version:  " << (char*)glGetString(GL_VERSION);
            ofLogNotice("\tGL") << "GLSL:     " << (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
            //ofLogNotice("\tGL") << "Extensions:" << (char*)glGetString(GL_EXTENSIONS);
            
            int GlMaxTextureSize;
            glGetIntegerv(GL_MAX_TEXTURE_SIZE, &GlMaxTextureSize);
            ofLogNotice("\tGL") << "MaxTexSize:" << GlMaxTextureSize; // px?
            
            ofLogNotice("ofFbo") << "checkGLSupport:" << ofFbo::checkGLSupport() << ", maxColorAttachments=" << ofFbo::maxColorAttachments() << ", maxDrawBuffers=" << ofFbo::maxDrawBuffers() <<
            ", maxSamples=" << ofFbo::maxSamples();
            
            if(ofIsGLProgrammableRenderer()) {
                ofLogNotice("\tofGL Using Programmable Renderer");
            }
            
        }

    }
    
}