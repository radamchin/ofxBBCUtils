#pragma once

#include "ofMain.h"
#include "ofEvents.h"

#include "BBCUtils.h"

#include "CheckTimer.h"
#include "FrameTimer.h"

#include "bbcConfig.h"

#include "ErpEase.h"

#include "FrameTweener.h"
#include "BezierAnimator.h"
#include "RandomBezierAnimator.h"
#include "Oscillator.h"

#include "iApp.h"

#include "FPSTrackingWidget.h"
#include "MiniPlotter.h"

#include "ofParameterSerialiser.h"

#define BBC_UTILS_DEV_VERSION "1.0.5"

using namespace bbc::utils;


//--------------------------------------------------------------------
struct EaseVals {
	
	// Struct to hold and increment test easing norms 0..1
	
	float a = 0;
	float b = 0;
	float c = 0;
	
	int a_dir = 1; // -1 || 1
	int b_dir = 1;
	int c_dir = 1;
	
	//--------------------------------------------------------
	void process( const float stp, float & v, int & dir ) {
		// Move value along the step
		v += stp * dir;
		if(dir == -1) {
			if(v < 0.0) {
				v = 0.0;
				dir = 1.0;
			}
		}else{
			if(v > 1.0) {
				v = 1.0;
				dir = -1.0;
			}
		}
	}
	
	//--------------------------------------------------------
	void increment( float stp = 0.001 ) {
		
		process( stp, a, a_dir );
		process( stp, b, b_dir );
		process( stp, c, c_dir );
		
	}
};

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
        void testEasing();
        void testAnimators();
        void testClipboard();
        void testOscillators();
    
    private:
    
        CheckTimer *a_timer;
        CheckTimer *b_timer;
        FrameTimer *fa_timer;
        FrameTimer *fb_timer;
        
		EaseVals ease_vals;
	
        bbc::utils::Oscillator sineOscillator;
        bbc::utils::MiniPlotter sinePlotter;
    
        bbc::utils::Oscillator sawOscillator;    
        bbc::utils::MiniPlotter sawPlotter;
    
        bbc::utils::Oscillator squareOscillator;
        bbc::utils::MiniPlotter squarePlotter;
        
        bbc::utils::Oscillator noiseOscillator;
        bbc::utils::MiniPlotter noisePlotter;
        
        bbc::utils::Oscillator noise2Oscillator;
        bbc::utils::MiniPlotter noise2Plotter;

        FrameTweener frame_tweener;
        BezierAnimator bezier_animator_a;
        RandomBezierAnimator rand_bezier_animator;
    
        ErpEase::easeFunc testEaseFunc;
        
        FPSTrackingWidget fps_tracker;
    
};
