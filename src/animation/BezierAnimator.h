/*
     BezierAnimator
     Frame Based, manually updated
 
     (See AS3 sms_origins:BezierAnimate for a time based version that could be ported)
 
     Adam Hinshaw 2014
     
     TODO: Add support for Z dim! or just add a BezierAnimator3D variant?
 
 */

#pragma once

#include "FrameTweener.h"
#include "ErpEase.h"
#include "ofVec2f.h"

namespace bbc {
    namespace utils {
        
        class BezierAnimator : public FrameTweener {
            
        public:
            
            bool use_ease;
            
            BezierAnimator(bool _use_ease = true) {
                use_ease = _use_ease;
            }
            
            void start(float start_x, float start_y, float a_x, float a_y, float b_x, float b_y, float end_x, float end_y, int frame_duration) {
                
                start_pos.set(start_x, start_y);
                current_pos.set(start_x, start_y);
                end_pos.set(end_x, end_y);
                
                control_a.set(a_x, a_y);
                control_b.set(b_x, b_y);
                
                FrameTweener::start(frame_duration); // super method
            }
            
            void start(ofPoint & _start_pos, ofPoint & _control_a, ofPoint & _control_b, ofPoint & _end_pos, float frame_duration) {
                
                start_pos.set(_start_pos);
                current_pos.set(_start_pos);
                end_pos.set(_end_pos);
                
                control_a.set(_control_a);
                control_b.set(_control_b);
                
                FrameTweener::start(frame_duration); // super method
            }
            
            void start(ofVec2f & _start_pos, ofVec2f & _control_a, ofVec2f & _control_b, ofVec2f & _end_pos, float frame_duration) {
                
                start_pos.set(_start_pos);
                current_pos.set(_start_pos);
                end_pos.set(_end_pos);
                
                control_a.set(_control_a);
                control_b.set(_control_b);
                
                FrameTweener::start(frame_duration); // super method
            }
            
            void repeat() {
                start(start_pos, control_a, control_b, end_pos, frame_total);
            }
            
            void interupt() {
                ofLogNotice("BezierAnimator interupt");
                FrameTweener::interupt();
            }
            
            void update() {
                
                FrameTweener::update();
                
                if(_complete) {
                    // set to 1.0??
                    //return;
                }
                
                float pos = use_ease ? ErpEase::quadInOut(0.0, 1.0, step) : step;
                
                current_pos.x = bezierPoint(start_pos.x, control_a.x, control_b.x, end_pos.x, pos);
                current_pos.y = bezierPoint(start_pos.y, control_a.y, control_b.y, end_pos.y, pos);
            }
            
            void drawDebug(int alpha = 255, float r = 10.0) {
                // Draw the points along with the path and handles.
                
                ofPushStyle();
                ofNoFill();
                
                ofSetColor(0,255,255,alpha);
                
                ofDrawBezier(start_pos.x, start_pos.y, control_a.x, control_a.y, control_b.x, control_b.y, end_pos.x, end_pos.y);
                //(x1, y1, cx1, cy1, cx2, cy2, x2, y2);
                
                ofSetColor(255,255,0,alpha);
                ofDrawEllipse(start_pos.x, start_pos.y, r, r);
                
                ofSetColor(255,0,255,alpha);
                ofDrawEllipse(end_pos.x, end_pos.y, r, r);
                
                ofSetColor(255,255,255,alpha);
                ofDrawEllipse(control_a.x, control_a.y, r/2, r/2);
                ofDrawEllipse(control_b.x, control_b.y, r/2, r/2);
                
                ofSetColor(128,128,128,alpha);
                ofDrawLine(control_a.x, control_a.y, start_pos.x, start_pos.y);
                ofDrawLine(control_b.x, control_b.y, end_pos.x, end_pos.y);
                
                ofFill();
                ofSetColor(255,0,0,alpha);
                ofDrawEllipse(current_pos.x, current_pos.y, r*.8, r*.8);
                
                ofPopStyle();
            }
            
            float getX() {
                return current_pos.x;
            }
            
            float getY() {
                return current_pos.y;
            }
            
            ofVec2f getPosition() {
                return current_pos;
            
            }
            
            
            string toString(){
                ostringstream out;
                out << "{BezierAnimator " << FrameTweener::toShortString() << "}";
                return out.str();
            }
            
        protected:
            
            ofVec2f start_pos;
            ofVec2f current_pos;
            ofVec2f end_pos;
            
            ofVec2f control_a; // control point for the start_pos
            ofVec2f control_b; // control point for the end_pos
            
            // TODO: this should be in core, or an bbc IAPP util thing?  bbcBezierPoint?
            float bezierPoint(float a, float b, float c, float d, float t) {
                // Taken from Processing PGraphics
                float t1 = 1.0 - t;
                return a*t1*t1*t1 + 3*b*t*t1*t1 + 3*c*t*t*t1 + d*t*t*t;
            }
            
        };
        
    }
}
