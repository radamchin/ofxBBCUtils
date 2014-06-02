
/*
 
 BBCUtils
 
 General utilities, living here until somewhere more organized shows u
 
 Adam Hinshaw 2013
 
 
 */

#pragma once

//#include "ErpEase.h"
//#include "Config.h"

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

        

    }
}