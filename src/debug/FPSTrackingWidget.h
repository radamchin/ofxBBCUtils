//
//  FPSTrackingWidget.h
//
//  Visual peformance profiling aid thing. So you can visualy track fps glitches
//
//  Created by Adam Hinshaw on 13/08/2015.
//
//

#ifndef HMKPlayer_FPSTrackingWidget_h
#define HMKPlayer_FPSTrackingWidget_h

#include "ofMain.h"

namespace bbc {
    namespace utils {
        
        class FPSTrackingWidget{
            
        public:
            
            ofColor bgCol = ofColor::white;
            ofColor fillCol = ofColor(0,255,0,128);
            ofColor markCol = ofColor::black;
            ofColor playheadCol = ofColor(255,0,0,128);
            
            float base_fps;
            
            int update_freq;

            float h;
            float x_margin;
            
            void setup(float _base_fps = 60.0, int _update_freq=5, float _h = 24.0, float _x_margin = 5.0) {
                base_fps = _base_fps;
                h = _h;
                x_margin = _x_margin;
                
                draw_pos = -1;
                
                update_freq = _update_freq;
                
                resize();
                
                ofAddListener(ofEvents().windowResized, this, &FPSTrackingWidget::resize);
                ofAddListener(ofEvents().update, this, &FPSTrackingWidget::update);
                
            }
            
            void resize(ofResizeEventArgs & args) {
                resize();
            }
            
            void resize() {
                
                draw_pos = -1;
                
                if(fbo.isAllocated()) {
                    // already created resize it?
                }else{
                }
                
                fbo.allocate(ofGetWidth()-(x_margin*2), h);
                
                fbo.begin();
                    ofClear(0,0,0,0);
                    ofSetColor(bgCol);
                    ofFill();
                    ofDrawRectangle(0,0,fbo.getWidth(),h);
                fbo.end();

            }
            
            void update( ofEventArgs & args) {
                
                if(ofGetFrameNum() % update_freq != 0) return;
                
                draw_pos++;
                if(draw_pos >= fbo.getWidth()){
                    draw_pos = 0;
                }

                ofPushMatrix();
                ofPushStyle();

                // Draw next line
                
                fbo.begin();

                    // clear line first
                    ofFill();
                    ofSetColor(bgCol);
                    ofDrawRectangle(draw_pos, 0, 1, h);

                    // float ft = 60.0; //ofGetTargetFrameRate();

                    ofSetColor(fillCol);
                    float f = MIN(base_fps, ofGetFrameRate());
                    float lp = f/base_fps;
                    float ly = h-(lp*h);
                    //ofLogNotice("FPSTracking") << draw_pos << " " << f << " " << lp << " " << ly;

                    ofDrawRectangle(draw_pos, ly, 1, h-ly);
                fbo.end();
                
                ofPopStyle();
                ofPopMatrix();
                
            }
            
            void mark() {
                // mark the timeline right now for reference
                ofPushStyle();
                fbo.begin();
                    ofSetColor(markCol);
                    ofFill();
                    ofDrawRectangle(draw_pos, 0, 1, h);
                fbo.end();
                ofPopStyle();
            }
            
            void draw(float x, float y) {
                
               // if(update_on_demand) update();
                
                ofPushStyle();
                ofEnableAlphaBlending();
                ofSetColor(255);
                fbo.draw(x, y);
               
                // draw a colour marker of where play head is
                ofSetColor(playheadCol);
                ofFill();
                ofDrawRectangle(x+draw_pos-1, y, 3, h);
                
                ofPopStyle();
            }
            
        private:
            ofFbo fbo;
            int draw_pos;
            
        };

    }
}

#endif
