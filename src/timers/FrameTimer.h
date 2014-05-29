/*
 *  FrameTimer.h
 *
 *  Frame counting timer
 *	Manually updated and checked
 *
 *  Created by Adam Hinshaw on 24/08/12.
 *  Copyright 2012 BigBrownCupboard. All rights reserved.
 *
 */

#ifndef _BBC_FRAME_TIMER // if this class hasn't been defined, the program can define it
#define _BBC_FRAME_TIMER // by using this if statement you prevent the class to be called more 

#include "ofMain.h"
#include "ofUtils.h"

namespace bbc {
	namespace utils {
                
        class FrameTimer {
            
            public:
                
                FrameTimer(int frames_duration, bool auto_reset = false);
                
                void update(); // short cut for step
                void step(); // update
                bool isExpired();
                void reset();
                float getPosition();
                int getFramesRemaining();
                int getDuration();
                void setCounter(int n); // back door to delay initial start or mess with
                int getCounter();
                string toString();
                
            private:	
                
                void init(int frames_duration, bool auto_reset);
                
                int _duration;
                int _counter;

                bool _auto_reset = true;
                
                ~FrameTimer();
            
        };

    }
}

#endif
