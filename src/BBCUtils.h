
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
            
            int ms = totalMS % 1000;
            
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


    }
}