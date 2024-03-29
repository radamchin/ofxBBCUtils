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
            
            RandomBezierAnimator(bool _repeating = false, float _control_rand = 200.0f, bool _use_ease = true, bool _use_3d = false) : BezierAnimator(_use_ease, _use_3d) {
                control_rand = _control_rand;
                repeating = _repeating;
            }
            
            void setup( ofParameter<ofRectangle> & rect) {
                setRange(rect);
                ofLogNotice("RandomBezierAnimator:setup") << range;
            }
            
            void setup( ofRectangle & rect) {
                range.set(rect);
                ofLogNotice("RandomBezierAnimator:setup") << range;
            }
            
            void setup(float rx, float ry, float rw, float rh) {
                setRange(rx,ry,rw,rh);
                ofLogNotice("RandomBezierAnimator:setup") << range;
            }
            
            void setRange(ofParameter<ofRectangle> & rect) {
                setRange(rect->x, rect->y, rect->width, rect->height);
            }
            
            void setRange(ofRectangle & rect) {
                range.set(rect);
            }
            
            void setRange(float rx, float ry, float rw, float rh) {
                range.set(rx,ry,rw,rh);
            }
            
            void setZRange(float front, float back) {
                z_range.set(front, back);
            }
            
            float getZRangeFront() {
                return z_range.x;
            }
            
            float getZRangeBack() {
                return z_range.y;
            }
            
            void start( ofPoint & start_pos, int _duration_frames = 200 ) {
                ofLogNotice("RandomBezierAnimator:start") << "[" << start_pos << "], frames:" << _duration_frames;
                
                current_pos.set(start_pos);
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
                
                float sx = _start_pos.x;
                float sy = _start_pos.y;
                float ax = sx + randomControl();
                float ay = sy + randomControl();
                
                float ex = _end_pos.x;
                float ey = _end_pos.y;
                float bx = ex + randomControl();
                float by = ey + randomControl();
                
                if(use_3d) {
                    
                    float sz = getZ();
                    float az = sz + randomControl();
                    float ez = RandomBezierAnimator::random(z_range.x, z_range.y);
                    float bz = ez + randomControl();
                    
                    ofLogNotice("RandomBezierAnimatior::start::(3d):") << sx << "," << sy << "," << sz << " -> " << ex << "," << ey << "," << ez << " : " << _duration_frames;
                    
                    BezierAnimator::start(sx,sy,sz, ax,ay,az, bx,by,bz, ex,ey,ez, frame_total);
                    
                }else{
                    start(_start_pos.x, _start_pos.y, _end_pos.x, _end_pos.y, _duration_frames);
                }
                
            }
            
            void start(ofVec2f & _start_pos, ofVec2f & _end_pos, int _duration_frames) {
                start(_start_pos.x, _start_pos.y, _end_pos.x, _end_pos.y, _duration_frames);
            }
            
            void start(float x1, float y1, float x2, float y2, int _duration_frames) {
                // More complete start call, with anchors being randomized only
                
                if(use_3d) ofLogWarning("RandomBezierAnimator:start") << "2d start method used and use_3d is defined. Your bezier will be 2d";
                
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
            
            void start( float sx, float sy, float ax, float ay, float bx, float by, float ex, float ey, int frame_total ) {
                 BezierAnimator::start( sx,sy, ax,ay, bx,by, ex,ey, frame_total );
            }
            
            void start( float sx, float sy, float sz, float ax, float ay, float az, float bx, float by, float bz, float ex, float ey, float ez, int frame_total ) {
                BezierAnimator::start( sx,sy,sz, ax,ay,az, bx,by,bz, ex,ey,ez, frame_total );
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
            
            ofRectangle getRange() {
                // return a copy of the range
                ofRectangle result;
                result.set(range);
                return result;
            }

            
        private:
            
            ofRectangle range;
            ofVec2f z_range; // x,y used to define a z range. x == closest to camera.
            
            
            void next() {
                
                float sx = getX();
                float sy = getY();
                
                float ax = sx + randomControl();
                float ay = sy + randomControl();
                
                float ex = RandomBezierAnimator::random(range.x, range.getRight());
                float ey = RandomBezierAnimator::random(range.y, range.getBottom());
                
                float bx = ex + randomControl();
                float by = ey + randomControl();
                
                if(use_3d) {
                    
                    float sz = getZ();
                    float az = sz + randomControl();
                    float ez = RandomBezierAnimator::random(z_range.x, z_range.y);
                    float bz = ez + randomControl();

                    BezierAnimator::start(sx,sy,sz, ax,ay,az, bx,by,bz, ex,ey,ez, frame_total);
                    
                }else{
                    BezierAnimator::start(sx,sy, ax,ay, bx,by, ex,ey, frame_total);
                }
              
                
            }
            
        };
        
    }
}


