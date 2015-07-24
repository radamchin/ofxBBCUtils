#pragma once

#include "ofMain.h"
#include "ofEvents.h"

#include "CheckTimer.h"
#include "FrameTimer.h"

#include "bbcConfig.h"

#include "ErpEase.h"

#include "FrameTweener.h"
#include "BezierAnimator.h"
#include "RandomBezierAnimator.h"

#include "BBCUtils.h"

#include "iApp.h"


#define BBC_UTILS_DEV_VERSION "1.0.2"

using namespace bbc::utils;

class ofApp : public iApp{
	public:
    
        ofApp();
    
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void testConfig();
        void testTimers();
        void testEasing();
        void testAnimators();
        void testClipboard();
    
    private:
    
        CheckTimer *a_timer;
        CheckTimer *b_timer;
        FrameTimer *fa_timer;
        FrameTimer *fb_timer;
        
        float fa;
        float fb;
        float fc;
    
        FrameTweener frame_tweener;
        BezierAnimator bezier_animator_a;
        RandomBezierAnimator rand_bezier_animator;
    
};
