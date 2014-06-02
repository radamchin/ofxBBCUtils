/*
	RandomBezierAnimator
	
    Adam Hinshaw 2014
 
*/

#pragma once

#include "BezierAnimator.h"
#include "ofRectangle.h"

namespace bbc {
    namespace utils {
        
        class RandomBezierAnimator : public BezierAnimator {
	        
            public:
            
                float control_rand;

                bool repeating;
                
                RandomBezierAnimator(bool _repeating = false, float _control_rand = 200.0f) {
                    control_rand = _control_rand;
					repeating = _repeating;
                }
            
                void setup(float rx, float ry, float rw, float rh) {
                    range.set(rx,ry,rw,rh);
                }
                
                void start(int _duration_frames = 200) {
                    ofLogNotice("RandomBezierAnimator:start");
                    // set the start pos to something random
                    
                    current_pos.x = ofRandom(range.x, range.getRight());
                    current_pos.y = ofRandom(range.y, range.getBottom());
                    
                    ofLogNotice() << getX() << "," << getY();
                    
                    frame_total = _duration_frames;
                    
                    next();
                }
            
                void start(ofVec2f _start_pos, ofVec2f _end_pos, int _duration_frames) {
                    start(_start_pos.x, _start_pos.y, _end_pos.x, _end_pos.y, _duration_frames);
                }
            
                void start(float x1, float y1, float x2, float y2, int _duration_frames) {
                    // more complete start call, with anchors being randomized only  
                    
                    float sx = x1;
                    float sy = y1;
                    float ax = sx + randomControl();
                    float ay = sy + randomControl();

                    float ex = x2;
                    float ey = y2;
                    float bx = ex + randomControl();
                    float by = ey + randomControl();
                    
                    BezierAnimator::start(sx,sy,ax,ay,bx,by,ex,ey,_duration_frames);
                }
            
                float randomControl() { 
                    return random(-control_rand, control_rand);
                }
            
                float random(float min, float max) { // override this to change the random function
                    return ofRandom(min, max);
                }
            
                void update() {
                    BezierAnimator::update();
                    
                    if(_complete && repeating) next(); // a movement has finished so do another
                }
            
                void drawDebug(int alpha = 255) {
                    BezierAnimator::drawDebug(alpha);
                }
            
                string toString() {
                    ostringstream out;
                    out << "{RandomBezierAnimator " << FrameTweener::toShortString() << "}";
                    return out.str();
                }
            
            private:
            
                ofRectangle range;
            
                void next() {
                
                    float sx = getX();
                    float sy = getY();
                    float ax = sx + randomControl();
                    float ay = sy + randomControl();

                    float ex = random(range.x, range.getRight());
                    float ey = random(range.y, range.getBottom());
                    float bx = ex + randomControl();
                    float by = ey + randomControl();
                    
                    BezierAnimator::start(sx,sy,ax,ay,bx,by,ex,ey,frame_total);
                }            
            
        };
 
    }
}
    
	