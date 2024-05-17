//
//  MiniPlotter.h
//  ofxBBCUtils
//
//  Small FBO based graph/plotter
//
//  Created by Adam Hinshaw on 17/5/2024.
//

/*
 
    
 */

#ifndef MiniPlotter_h
#define MiniPlotter_h


#include "ofMain.h"

namespace bbc {
    namespace utils {
        
        class MiniPlotter{
            
        public:
            
            ofColor bgCol = ofColor::white;
            ofColor lineCol = ofColor::black;
            
            uint64_t last_update;
            uint64_t update_time; // how long between updates to allow new data.
            
            deque<float> data;
            
            void setup(float _h = 32.0, float _w = 32.0, float _update_time = 250) {
                
                h = _h;
                w = _w;
                
                update_time = _update_time;
                last_update = ofGetElapsedTimeMillis();
            }
            
            int getWidth() {
                return w;
            }
            
            int getHeight() {
                return h;
            }
            
            void add( float v ) {
                // Add a value to the data
                
                uint64_t now = ofGetElapsedTimeMillis();
                
                if(now >= last_update + update_time) {
                    // enough time has elapsed to add data.
                    last_update = now;
                }else{
                    return ;  // dont allow as not enough time has elapsed
                }
                
                // This expects a normalised value 0..1
                //v = max( fmin(v, 1.0f), 0.0f); // Force to normalised value
                
                if (data.size() >= w) {
                    data.pop_front();  // Remove the oldest element
                }
                
                data.push_back( v );
                
            }
            
            void draw( float x = 0, float y = 0 ) {
                
                
                ofPushStyle();
                ofEnableAlphaBlending();
                ofSetColor(255);
                
                // Clear background
                ofSetColor(bgCol);
                ofFill();
                ofDrawRectangle(x, y, w, h);
                
                
                // Draw a vertex here using the values
                ofSetColor(lineCol);
                ofSetLineWidth(1);
                ofNoFill();
                            
                ofBeginShape();
                float cx = x;
                float cy;
                for ( float v : data ) {
                    cy = y + (h * v);
                    ofVertex( cx, cy );
                    // cout << "[" << cx << "," << cy << "," << v << "], ";
                    cx++;
                }
                ofEndShape(false);
                
                ofPopStyle();
            }
            
        private:
            
            float h;
            float w;
            
        };

    }
}

#endif /* MiniPlotter_h */
