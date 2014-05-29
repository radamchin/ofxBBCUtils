/*
 *  CheckTimer.h
 *  Manually checked milliseconds based stamp timers. (Thanx Tab Julius!)
 *
 *  Created by Adam Hinshaw on 24/08/12.
 *  Copyright 2012 BigBrownCupboard. All rights reserved.
 *
 */

#ifndef _BBC_CHECK_TIMER // if this class hasn't been defined, the program can define it
#define _BBC_CHECK_TIMER // by using this if statement you prevent the class to be called more 

#include "ofMain.h"

namespace bbc {
	namespace utils {
        
        class CheckTimer {
                
            public:
                
                string id;
                
                CheckTimer(string id, int duration);
                
                bool isExpired();
                float getPosition();
                float getPositionSeconds();
                int getRemaining();
                int getDuration();
                
                void expire();
                
                void reset(bool log = false);
                void reset(int new_duration, bool log = false);
                
                string toString();
                int getResetCount();

            private:
                
                int startTime;
                int duration; // milliseconds
                int expiryTime;
                    
                float norm(float value, float start, float stop);
                
                int getCurrentTimeStamp(); // could be static ??
                int resetCount;
                
                ~CheckTimer();
            
        };
        
    }
}

        
#endif
