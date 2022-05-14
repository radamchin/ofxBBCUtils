/*
 *  FrameTimer.cpp
 *
 *  Created by Adam Hinshaw on 24/08/12.
 *  Copyright 2012 BigBrownCupboard. All rights reserved.
 *
    
    TODO; could make it not manual by listening to of update event it's self (see ofxTimer for example)
    addListener(ofEvent().update, this &FrameTimer::update);
    But would have to be an optional, auto_update thing. as there are cases when its better to auto update it (i.e, mpe apps)
 
 */

#include "FrameTimer.h"

//--------------------------------------------------------------
namespace bbc {
	namespace utils {
                
        FrameTimer::FrameTimer(int frames_duration, bool auto_reset) {
			setup(frames_duration, auto_reset);
        }

        void FrameTimer::setup(int frames_duration, bool auto_reset) {
            this->_duration = frames_duration;
            this->_auto_reset = auto_reset;
            this->_counter = 0;
        }
    
        FrameTimer::~FrameTimer() {
            printf("*** FrameTimer Destroyed ***\n");
        }
    
        //---------------------------------------------------------------
        void FrameTimer::update() { // increment the timer
            step();
        }

        void FrameTimer::step() { // increment the timer
            _counter++;
        }

        //---------------------------------------------------------------
        bool FrameTimer::isExpired() {

            if(_counter >= _duration) { // period has elapsed
                _counter = _duration;
                if(_auto_reset) reset();
                return true;
            }

            return false;
        }

        //---------------------------------------------------------------
        void FrameTimer::reset() {
            _counter = 0;
        }

        float FrameTimer::getPosition() { // 0..1
            return _counter/(float)_duration;
        }

        int FrameTimer::getFramesRemaining() {
            return _duration - _counter;
        }

        int FrameTimer::getDuration() {
            return _duration;
        }

        void FrameTimer::setCounter(int n) { // back door to delay initial start or mess with
            _counter = n;
        }

        int FrameTimer::getCounter() {
            return _counter;
        }

        //---------------------------------------------------------------
        string FrameTimer::toString() { // render_modes
            return "[" + ofToString(isExpired()) +"," + ofToString(getCounter()) +  ":" + ofToString(getFramesRemaining()) + "/" + ofToString(getDuration()) + " " + ofToString(getPosition()) + "]";
        }
        
	}
}
