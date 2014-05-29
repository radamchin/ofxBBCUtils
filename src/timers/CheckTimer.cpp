/*
 *  CheckTimer.cpp
 *
 *  Created by Adam Hinshaw on 24/08/12.
 *  Copyright 2012 BigBrownCupboard. All rights reserved.
  
	TODO: could make a static Timer class that holds TimerChild(ren) like in my processing lib
	TODO: update and make static the getCurrentTimeStep to save lots of calls to it every update (minor thing)
 *
 */

#include "CheckTimer.h"
#include "ofUtils.h"
#include "ofMain.h"

//--------------------------------------------------------------
namespace bbc {
	namespace utils {
                
        CheckTimer::CheckTimer(string id, int duration) { // constructor
            this->id = id;
            this->duration = duration;
            resetCount = 0;
            reset(false); // start counting
        }

        CheckTimer::~CheckTimer() {
            printf("*** CheckTimer Destroyed ***\n");
        }

        bool CheckTimer::isExpired() {
            return getCurrentTimeStamp() >= expiryTime;
        }

        float CheckTimer::getPosition() {
            // return fractional position
            return norm(getCurrentTimeStamp(), expiryTime-duration, expiryTime);
        }

        // Taken from PApplet source
        float CheckTimer::norm(float value, float start, float stop) {
            return (value - start) / (stop - start);
        }

        int CheckTimer::getRemaining() {
            int i = expiryTime - getCurrentTimeStamp();
            return i < 0 ? 0 : i;
        }

        int CheckTimer::getDuration() {
            return duration;
        }

        float CheckTimer::getPositionSeconds() {
            return getPosition() * (duration / 1000);
        }

        void CheckTimer::reset(bool log) {
            expiryTime = getCurrentTimeStamp() + duration;
            resetCount++;
            if(log) ofLogNotice("CheckTimer:[" + id + "]:reset:" + ofToString(getCurrentTimeStamp()) + " + " + ofToString(duration) + " = " + ofToString(expiryTime));
        }

        void CheckTimer::reset(int new_duration, bool log) {
            duration = new_duration;
            reset(log);
        }

        int CheckTimer::getCurrentTimeStamp() {
            return ofGetElapsedTimeMillis();
        }

        void CheckTimer::expire() {
            // hack ish way to expire a timer.
            expiryTime = getCurrentTimeStamp();
        }

        int CheckTimer::getResetCount() {
            return resetCount;
        }

        string CheckTimer::toString() { // ofToString(getPositionSeconds(),2) + " "
            return "CheckTimer[" + id + "] " + ofToString(isExpired()) +":" + ofToString(getPosition(),2) + ", " + ofToString(getRemaining(),4,'0') + "/" + ofToString(getDuration()) + "]";
        }
        
    }
}
