
/*
 
 BBCUtils
 
 General utilities, living here until somewhere more organized shows up
 
 Adam Hinshaw 2013
 
 
 */

#pragma once

#include "ofMain.h"

//#include "ErpEase.h"
//#include "bbcConfig.h"

//#include "RandomBezierAnimator.h"
//#include "BezierAnimator.h"
//#include "FrameTweener.h"

#include "drawing/Drawing.h"
#include "time/BBCTime.h"

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
        
	
		//--------------------------------------------------------------------------------------
        static inline void recursiveFileSearchNameContains(const string & path, const string & search_str, vector<string> & results ) {
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
			std::ostringstream out;
            
            for( int i=0; i<str.length(); i++ ) {
                out << toupper( str[ i ] );
            }
            
            return out.str();
        }
        
        static string toLowerCase( const string & str ) {
			std::ostringstream out;
            
            for( int i=0; i<str.length(); i++ ){
                out << tolower( str[ i ] );
            }
            
            return out.str();
        }
        
        //---------------------------------------------------------------------------
        static string vecToStr(const ofVec3f & v, int places = -1) {
			std::ostringstream out;
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
			std::ostringstream out;

			commonOpenGlInfo info;
			getGLInfo(info);

			out << "v=" << info.version << ", vendor=" << info.vendor << ", maxTex=" << info.maxTextureSize;

#ifndef TARGET_OPENGLES
			out << ", maxView=" << info.maxDimensions[0] << "," << info.maxDimensions[1];
#endif

			return out.str();
		}
	
		//--------------------------------------------------------------------------------------
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
	
		//--------------------------------------------------------------------------------------
        static float getAngleRadiansBetweenPoints( ofVec2f & a, ofVec2f & b ) {
            
            float fx = b.x - a.x;
            float fy = b.y - a.y;
            
            return atan2(fy, fx);
        }
	
		//--------------------------------------------------------------------------------------
        // Get an offset point along a line at a normalised offset
        static ofVec2f getPointOnLine(const ofVec2f& start, const ofVec2f& end, float offset = 0.5) {
           
            // Calculate the direction vector
            ofVec2f dir = end - start;

            // Calculate the offset distances
            float dist = offset * dir.length();

            // Normalize the direction vector to get the unit vector
            dir.normalize();

            // Calculate the new start and end points
            ofVec2f newPos = start + dir * dist;
            return newPos;
        }
	
		//--------------------------------------------------------------------------------------
        // If an image sprite can be rotated, what is its maximum radius?
        // https://chatgpt.com/c/67f62871-75a0-8003-a0c2-2c31803d8ad8
        static float getMaxRadius(float width, float height) {
          return 0.5 * glm::sqrt(width * width + height * height);
        }
    
        // max Radius of a rotated sprite based on its base width and height
        static float getRotatedBoundingRadius(float width, float height, float angleRadians) {
            
            float cos = glm::abs( glm::cos(angleRadians) );
            float sin = glm::abs( glm::sin(angleRadians) );
            float rotatedWidth = width * cos + height * sin;
            float rotatedHeight = width * sin + height * cos;
            return 0.5 * glm::sqrt(rotatedWidth * rotatedWidth + rotatedHeight * rotatedHeight);
        }
        
	
		//--------------------------------------------------------------------------------------
    }
    
}
