/*
 * FrameTweener
 * 
 *  Liner Interpolates step 0..1 over x frames(updates)
 *
 *  Needs to be manually updated
 *
 *  Adam Hinshaw 2014
 *
 *      TODO: add option to automatically update via ofEvents listener
 *
 *
 * */

#pragma once

#include "ofMain.h"

namespace bbc {
    namespace utils {
        
        class FrameTweener {
        
            public:
            
                FrameTweener() {
                    frame_counter = 0;
					frame_total = 1; 
            
					_running = false;
					_complete = true;
            
					 step = 0.0;
                }
                
                void start(int _frame_total = 100) {
                    //ofLogNotice("FrameTweener.start:") << " _running=" << _running << ", _complete=" << _complete;
                    
                    if(_running) {
                        // reset ?? or interupt first?
                        interupt();
                        // or just let it change the target time and reset itself below??
                    }
                    
                    frame_counter = 0;
                    frame_total = _frame_total;
                    
                    if(frame_total < 1) frame_total = 1;
                    
                    step = 0.0;
                    
                    _complete = false;
                    _running = true;
                }
                
                void update() {
                    
                    if(_complete) return;
                    
                    frame_counter++;
                    
                    if(frame_counter >= frame_total) {
                        step = 1.0f;
                        completed(false);
                        return;
                    }
                    
                    step = frame_counter / (float)frame_total; // fractional step 0-1
                }
                
                void interupt() {
                    
                    if(_complete) return;
                    
                    //ofLogNotice("FrameTweener.interupt");
                    
                    completed(true); // let listener know this is completed but interupted
                }
            
                float getPosition() {
                    return step;
                }
                
                bool isRunning() {
                    return _running;
                }
                
                bool isActive(){
                    return !_complete;
                }
                
                bool isComplete(){
                    return _complete;
                }
            
                int getDuration() {
                    return frame_total;
                }
            
                string toShortString() {
                    ostringstream out;
                    out << "f=" << frame_counter << "/" << frame_total << ", step=" << ofToString(step,4) << ", running=" << _running << ", complete=" << _complete;
                    return out.str();
                }
                
                string toString() {
                    ostringstream out;
                    out << "{FrameTweener " << toShortString() << "}";
                    return out.str();
                }
            
            protected:
                
                int frame_counter;
                int frame_total; // how many frames to reach target
            
                bool _running;
                bool _complete;
            
                float step;
                
                void completed(bool interrupted) {
                    _complete = true;
                    _running = false;
                }
            
        };
    
    }
}
