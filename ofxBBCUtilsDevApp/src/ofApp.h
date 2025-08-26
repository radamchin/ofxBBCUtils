#pragma once

#include "ofMain.h"
#include "ofEvents.h"

#include "BBCUtils.h"

#include "CheckTimer.h"
#include "FrameTimer.h"

#include "bbcConfig.h"

#include "FrameTweener.h"
#include "BezierAnimator.h"
#include "RandomBezierAnimator.h"

#include "iApp.h"

#include "FPSTrackingWidget.h"
#include "MiniPlotter.h"

#include "ofParameterSerialiser.h"

#include "tests/EasingTest.h"
#include "tests/OscillatorTest.h"

#define BBC_UTILS_DEV_VERSION "1.0.6"

using namespace bbc::utils;

//--------------------------------------------------------------------
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
        void testOfParamSerialiser();
        void testTimers();
        void testAnimators();
        void testClipboard();
    
    private:
    
        CheckTimer *a_timer;
        CheckTimer *b_timer;
        FrameTimer *fa_timer;
        FrameTimer *fb_timer;
		
		FrameTweener frame_tweener;
		BezierAnimator bezier_animator_a;
		RandomBezierAnimator rand_bezier_animator;
	
		OscillatorTest oscillators;
		EasingTest easing;
        
        FPSTrackingWidget fps_tracker;
    
};
