/*
     RandomBezierAnimator
 
     Adam Hinshaw 2014
 
     TODO: Add support for Z dim
 
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
            
            //--------------------------------------------
            
            RandomBezierAnimator(bool _repeating = false, float _control_rand = 200.0f) {
                control_rand = _control_rand;
                repeating = _repeating;
            }
            
            void setup( ofRectangle & rect) {
                range.set(rect);
                ofLogNotice("RandomBezierAnimator:setup") << range;
            }
            
            void setup(float rx, float ry, float rw, float rh) {
                setRange(rx,ry,rw,rh);
                ofLogNotice("RandomBezierAnimator:setup") << range;
            }
            
            void setRange(ofRectangle & rect) {
                range.set(rect);
            }
            
            void setRange(float rx, float ry, float rw, float rh) {
                range.set(rx,ry,rw,rh);
            }
            
            void start( ofPoint & start_pos, int _duration_frames = 200 ) {
                ofLogNotice("RandomBezierAnimator:start") << start_pos << ", " << _duration_frames;
                
                current_pos.set(start_pos.x, start_pos.y);
                frame_total = _duration_frames;
                
                next();
            }
            
            void start( ofVec2f & start_pos, int _duration_frames = 200 ) {
                ofLogNotice("RandomBezierAnimator:start") << start_pos << ", " << _duration_frames;
                
                current_pos.set(start_pos);
                frame_total = _duration_frames;
                
                next();
            }
            
            void start(int _duration_frames = 200) {
                ofLogNotice("RandomBezierAnimator:start") << start_pos;
                // set the start pos to something random
                
                current_pos.x = ofRandom(range.x, range.getRight());
                current_pos.y = ofRandom(range.y, range.getBottom());
                ofLogNotice() << getX() << "," << getY();
                
                frame_total = _duration_frames;
                next();
            }
            
            void start(ofPoint & _start_pos, ofPoint & _end_pos, int _duration_frames) {
                start(_start_pos.x, _start_pos.y, _end_pos.x, _end_pos.y, _duration_frames);
            }
            
            void start(ofVec2f & _start_pos, ofVec2f & _end_pos, int _duration_frames) {
                start(_start_pos.x, _start_pos.y, _end_pos.x, _end_pos.y, _duration_frames);
            }
            
            void start(float x1, float y1, float x2, float y2, int _duration_frames) {
                // More complete start call, with anchors being randomized only
                
                ofLogNotice("RandomBezierAnimatior::start") << x1 << "," << y1 << " ->" << x2 << "," << y2 << " : " << _duration_frames;
 
                float sx = x1;
                float sy = y1;
                float ax = sx + randomControl();
                float ay = sy + randomControl();
                
                float ex = x2;
                float ey = y2;
                float bx = ex + randomControl();
                float by = ey + randomControl();
                
                BezierAnimator::start( sx,sy, ax,ay, bx,by, ex,ey, _duration_frames );
            }
            
            void setFrameTotal( int n) {
                frame_total = n; // change the duraiton a tween takes. (Prop of FrameTweener class)
            }
            
            float randomControl() {
                return RandomBezierAnimator::random(-control_rand, control_rand);
            }
            
            float random(float min, float max) { // override this to change the random function (i.e use a seeded value.
                return ofRandom(min, max);
            }
            
            void update() {
                BezierAnimator::update();
                
                if(_complete && repeating) next(); // a movement has finished so do another
            }
            
            void drawDebug(int alpha = 255, float r = 10.0) {
                BezierAnimator::drawDebug(alpha, r);
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
                
                float ex = RandomBezierAnimator::random(range.x, range.getRight());
                float ey = RandomBezierAnimator::random(range.y, range.getBottom());
                
                float bx = ex + randomControl();
                float by = ey + randomControl();
                
                BezierAnimator::start(sx,sy, ax,ay, bx,by ,ex,ey, frame_total);
            }
            
        };
        
    }
}


