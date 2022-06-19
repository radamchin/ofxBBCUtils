
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

#include <Poco/Timestamp.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeParser.h>
#include <Poco/DateTime.h>

// For Clipboard access
#if (_MSC_VER)
#include <GLFW/glfw3.h>
#else
#include "GLFW/glfw3.h"
#endif

#if (_MSC_VER)
	// crazy no round function in math.h on win32 (or in OF)
	/*static inline float round(float f){
		return floor(f + .5);
	}*/
#endif

#define bbcSQLDateStampFormat "%Y-%m-%d %H:%M:%S"    // "YYYY-MM-DD HH:MM:SS" : Format SQLite needs to save dates (or could just use  DateTimeFormat::SORTABLE_FORMAT for this..)
#define bbcSQLDayFormat "%Y-%m-%d"                   // "YYYY-MM-DD"
#define bbcSQLTimeFormat "%H:%M:%S"                  // "HH:MM:SS"
#define bbcSQLTimeFormatWithMS "%H:%M:%S:%i"	    //"HH:MM:SS:MSS"
// see: https://pocoproject.org/docs/Poco.DateTimeFormatter.html

namespace bbc {
    namespace utils {

		typedef struct {
			string version;
			string vendor;
			string renderer;

			bool bPointSpritesSupported;
			bool bVboSupported;
			bool bShadersSupported;
			int maxTextureSize;
			int maxDimensions[2];
			int maxLights;

		} commonOpenGlInfo;

		
        static const string getUpTimeStr(bool show_secs = true) {
            // Return formated string of how long has this app been running.
            
            unsigned long total_up_secs = ofGetElapsedTimeMillis() / 1000;
            
            int dys = (int) floor(total_up_secs / 86400); // 86400 == 60 * 60 * 24, seconds in a day.
            int hrs = (int) floor((total_up_secs % 86400) / 3600); // 3600 == 60 * 60. secopnds in an hour
            int mins = (int) floor(((total_up_secs % 86400) % 3600) / 60);
            int secs = (total_up_secs % 86400) % 3600 % 60;
            
            stringstream out;
            out << "up:" << dys << "d," << hrs << "h," << mins << "m," << secs << "s";
            return out.str();
        }
        
        static float HMSFtoSeconds(const string & input, int frame_rate = 25) {
            // take 0:03:29:17 return (3*60) + 29 + ()
            vector<string> parts = ofSplitString(input, ":", false, true);
            if(parts.size() == 4) {
                int hours = ofToInt(parts[0]);
                int mins = ofToInt(parts[1]);
                int secs = ofToInt(parts[2]);
                float frames = ofToFloat(parts[3]);
                
                return (hours * 3600) + (mins * 60) + secs + (frames / (float)(frame_rate));
            }else{
                ofLogError("HMSFtoSeconds illegal part count. Can't parse") << parts.size() << " 4 expected '" << input << "'";
                return -1.0;
            }
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
            // Time "15:39:22"
            Poco::LocalDateTime now;
            return Poco::DateTimeFormatter::format(now, bbcSQLTimeFormat);
        }

		static string getNowTimeWithMS() {
			// time with ms "15:39:22:230"
			Poco::LocalDateTime now;
			return Poco::DateTimeFormatter::format(now, bbcSQLTimeFormatWithMS);
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
    
        static float msToFrames( const int ms, unsigned int frameRate = 0) {
            
            frameRate = (frameRate == 0) ? ofGetFrameRate() : frameRate;
            
            return frameRate*(ms/1000.0);
        }
        
		//--------------------------------------------------------------------------------------

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
        
        static string toUpperCase( const string & str ) {
            ostringstream out;
            
            for( int i=0; i<str.length(); i++ ) {
                out << toupper( str[ i ] );
            }
            
            return out.str();
        }
        
        static string toLowerCase( const string & str ) {
            ostringstream out;
            
            for( int i=0; i<str.length(); i++ ){
                out << tolower( str[ i ] );
            }
            
            return out.str();
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
        
        //---------------------------------------------------------------------------
        
        // see: https://stackoverflow.com/questions/5100718/integer-to-hex-string-in-c
        template< typename T >
        static std::string intToWebHex( T i ) {
            std::stringstream stream;
            stream << "#"
            << std::setfill ('0') << std::setw(sizeof(T)*2)
            << std::hex << i;
            return stream.str();
        }
        
		//---------------------------------------------------------------------------
		static void getGLInfo(commonOpenGlInfo & info) {

			info.version = (char*)glGetString(GL_VERSION);
			info.vendor = (char*)glGetString(GL_VENDOR);
			info.renderer = (char*)glGetString(GL_RENDERER);
			info.bVboSupported = info.bShadersSupported = info.bPointSpritesSupported = false;

#ifndef TARGET_OPENGLES
			if (glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite")) {
				info.bPointSpritesSupported = true;
			}

			if (glewIsSupported("GL_ARB_vertex_buffer_object")) {
				info.bVboSupported = true;
			}

			if (glewIsSupported("GL_ARB_vertex_shader")) {
				info.bShadersSupported = true;
			}

			glGetIntegerv(GL_MAX_VIEWPORT_DIMS, info.maxDimensions);

#else

			// TODO work out equiv. look ups in glm?

#endif

			glGetIntegerv(GL_MAX_TEXTURE_SIZE, &info.maxTextureSize);
			glGetIntegerv(GL_MAX_LIGHTS, &info.maxLights);

		}

		//---------------------------------------------------------------------------
        static string getGLInfoStringMin() {
			ostringstream out;

			commonOpenGlInfo info;
			getGLInfo(info);

			out << "v=" << info.version << ", vendor=" << info.vendor << ", maxTex=" << info.maxTextureSize;

#ifndef TARGET_OPENGLES
			out << ", maxView=" << info.maxDimensions[0] << "," << info.maxDimensions[1];
#endif

			return out.str();
		}

        //---------------------------------------------------------------------------
        static void printGLStats() {
            
			ofLogNotice("\tGL") << getGLInfoStringMin();

            if(ofIsGLProgrammableRenderer()) {
                ofLogNotice("\tofGL Using Programmable Renderer");
            }
            
            ofLogNotice("IsGLProgrammableRenderer") << ofIsGLProgrammableRenderer();
            ofLogNotice("GL-Version-Major") << ofGetGLRenderer()->getGLVersionMajor();
            ofLogNotice("GL-Version-Minor") << ofGetGLRenderer()->getGLVersionMinor();
            ofLogNotice("GLSL Version") << ofGLSLVersionFromGL(ofGetGLRenderer()->getGLVersionMajor(), ofGetGLRenderer()->getGLVersionMinor());

        }
        
        //---------------------------------------------------------------------------
        static void drawBackgroundGrid(float size, const ofColor& onColor, const ofColor& offColor) {
            // taken from https://github.com/openframeworks/openFrameworks/issues/5217

            static ofMesh gridMesh;
            
            float w = ofGetViewportWidth(), h = ofGetViewportHeight();
            gridMesh.clear();
            gridMesh.setMode(OF_PRIMITIVE_TRIANGLES);
        #ifndef TARGET_EMSCRIPTEN
        #ifdef TARGET_OPENGLES
            if(ofIsGLProgrammableRenderer()) gridMesh.setUsage(GL_STREAM_DRAW);
        #else
         //   gridMesh.setUsage(GL_STREAM_DRAW);
        #endif
        #endif

            std::vector<glm::vec3> verts;

            for (std::size_t y = 0; y < 3; ++y){
                for (std::size_t x = 0; x < 3; ++x) {
                    verts.push_back({x * size, y * size, 0.f});
                }
            }

            std::vector<ofColor> colors = { onColor, offColor };

            float twoSize = size * 2;

            for (std::size_t y = 0; y < h; y += twoSize){
                for (std::size_t x = 0; x < w; x += twoSize){
                    glm::vec3 offset(x, y, 0.f);
                    for (std::size_t i = 0; i < 2; ++i){
                        gridMesh.addVertex(verts[i + 0] + offset);
                        gridMesh.addColor(colors[i]);
                        gridMesh.addVertex(verts[i + 3] + offset);
                        gridMesh.addColor(colors[i]);
                        gridMesh.addVertex(verts[i + 4] + offset);
                        gridMesh.addColor(colors[i]);
                        gridMesh.addVertex(verts[i + 0] + offset);
                        gridMesh.addColor(colors[i]);
                        gridMesh.addVertex(verts[i + 4] + offset);
                        gridMesh.addColor(colors[i]);
                        gridMesh.addVertex(verts[i + 1] + offset);
                        gridMesh.addColor(colors[i]);

                        std::size_t j = colors.size() - i - 1;

                        gridMesh.addVertex(verts[i + 3] + offset);
                        gridMesh.addColor(colors[j]);
                        gridMesh.addVertex(verts[i + 6] + offset);
                        gridMesh.addColor(colors[j]);
                        gridMesh.addVertex(verts[i + 7] + offset);
                        gridMesh.addColor(colors[j]);
                        gridMesh.addVertex(verts[i + 3] + offset);
                        gridMesh.addColor(colors[j]);
                        gridMesh.addVertex(verts[i + 7] + offset);
                        gridMesh.addColor(colors[j]);
                        gridMesh.addVertex(verts[i + 4] + offset);
                        gridMesh.addColor(colors[j]);
                    }
                }
            }

            GLboolean depthMaskEnabled;
            glGetBooleanv(GL_DEPTH_WRITEMASK,&depthMaskEnabled);
            glDepthMask(GL_FALSE);
            gridMesh.draw();
            if(depthMaskEnabled){
                glDepthMask(GL_TRUE);
            }
        }
        
        //---------------------------------------------------------------------------
        static void drawCalibration(int alpha = 255, const ofColor mainColor = ofColor::white, float thickness =  2.0f) {
            /*
             Draw a screen calibration graphic, useful for projection calibration,
             */
            
            ofPushStyle();
            
            ofSetLineWidth(thickness);
            
            float w = ofGetWidth();
            float h = ofGetHeight();
            
            float cx = w / 2.0;
            float cy = h / 2.0;
            
            float half_thick = thickness / 2.0;
            
            ofSetCircleResolution(36);
            
            ofSetColor(mainColor, alpha);
            ofNoFill();
            
            // border
            ofRectMode(OF_RECTMODE_CORNER);
            ofDrawRectangle(half_thick, half_thick, w-thickness, h-thickness);
            
            // diagonal lines
            ofDrawLine(half_thick, half_thick, w+half_thick, h-half_thick);
            ofDrawLine(-half_thick, h-half_thick, w-half_thick, half_thick);
            
            // centre lines
            ofDrawLine(cx, 0, cx, h);
            ofDrawLine(0, cy, w, cy);
            
            // horizontal 1/4 lines
            ofDrawLine(0, h/4, w, h/4);
            ofDrawLine(0, h-h/4, w, h-h/4);
            
            // Draw centre rect & circle
            ofRectMode(OF_RECTMODE_CENTER);
            
            float dim = min(w, h) * .66f;
            
            ofDrawEllipse(cx, cy, dim, dim);
            
            // Draw more comprehensive grid
            
            // do this at the ratio of the screen?
            // TODO: make the ratio dynamic too reading getWidth and getHeight
            float wc = 16.0f;
            float hc = 9.0f;
            
            float grid_x = w / wc;
            float grid_y = h / hc;
            
            ofSetColor(mainColor, alpha);
            
            ofSetLineWidth(half_thick);
            // vertical lines
            for(int col = 1; col < wc; col++) {
                int gx = round(col * grid_x);
                ofDrawLine(gx, 0, gx, h);
            }
            
            // horizontal lines
            for(int row = 1; row < hc; row++) {
                int gy = round(row * grid_y);
                ofDrawLine(0, gy, w, gy);
            }
            
            ofSetLineWidth(thickness);
            
            // Draw circles at the sides
            
            int n = 6;
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
                
                ofDrawEllipse(0, y, mini_rad, mini_rad); // LHS
                ofDrawEllipse(w, y, mini_rad, mini_rad); // RHS
            }
            
            
            ofPopStyle();
            
        }

    }
    
}
