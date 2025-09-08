//
//  EasingTest.h
//  ofxBBCUtilsDevApp
//
//  Created by Adam Hinshaw on 26/8/2025.
//
//	Dev playground for easing functions

// TODO: how to get stepped and slowmo as ease funtion pointers?


#pragma once
#include "TestRunner.h"

#include "ErpEase.h"

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
class EasingTest : public TestRunner {
	
public:
	
	EaseVals ease_vals;

	ErpEase::easeFunc testEaseFunc;

	//--------------------------------------------------------------------
	void setup() override {
		
		// Ease function pointers
		testEaseFunc = ErpEase::getEaseFunctionPointer(EaseKind::CircInOut);
		
	}
	
	//--------------------------------------------------------------------
	void update() override {
		
	}
	
	//--------------------------------------------------------------------
	void draw( int _x = 0, int _y = 0 ) override {
		
		// Test Easing.
		ease_vals.increment(0.002);
		
		// TODO: could draw a line for every path, but with a dot (small circ) at every 5% along?? to show what the plot looks like in a 2 dims
		
		int vpad = 35;
		int x = 20;
		int x_step = 24; // distance between columns
		int yanchor = ofGetHeight() - 10; // 26 - vpad;
		int crad = 8;
		int xpad = 4;
		int start_y = vpad;
		int end_y = ofGetHeight() - crad - vpad - 75;
		int angle = -90;
		
		ofColor bg_col(0,0,0);
		ofColor col(255,255,0);
		
		static auto easeLabel = [&]( string label, ofColor _col ) { // lambda to make code repeated code simpler
			col.set(_col);
			bbc::utils::drawRotatedBitmapStringHighlight( label, x+xpad, yanchor, angle, bg_col, col );
			ofSetColor(col); // for the circle draw that follows
			return true;
		};
		
		static auto plotEasLine = [&]( int dx, ErpEase::easeFunc ease_func ) {
			// draw a line with small dots at 5% markers for an ease
			// use col
			float step = 0.05; // 5% steps
			float v = 0; // value to increment
			
			ofSetLineWidth(0.5);
			ofDrawLine(x, start_y, x, end_y);
			
			while(v < 1.0+step) {
				float vy = ease_func(start_y, end_y, v);
				ofDrawCircle( x, vy, 2);
				v += step;
			}
			
		};
		
		// Back Bounce Circ Cubic Elastic Expo Linear Quad Quart Quint Sine
		
		
		easeLabel( "LinearInOut", ofColor::limeGreen );
		ofDrawCircle( x, ErpEase::linearInOut(start_y, end_y, ease_vals.c), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::LinearInOut));
		
		/*x+=x_step;
		easeLabel( "SineIn", col);
		ofDrawCircle( x, ErpEase::sineIn(start_y, end_y, ease_vals.a), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::SineIn));
		
		x+=x_step;
		easeLabel( "SineOut", ofColor::lightCoral );
		ofDrawCircle( x, ErpEase::sineOut(start_y, end_y, ease_vals.b), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::SineOut));*/
		
		x+=x_step;
		easeLabel( "SineInOut", ofColor::yellowGreen );
		ofDrawCircle( x, ErpEase::sineInOut(start_y, end_y, ease_vals.c), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::SineInOut));
		
		
		
		// Special ease lookup by type
		x+=x_step;
		easeLabel( "QuadInOut", ofColor::darkCyan );
		ofDrawCircle( x, ErpEase::easeByKind(EaseKind::QuadInOut, start_y, end_y, ease_vals.c), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::QuadInOut));
		
		
		x+=x_step;
		easeLabel( "QuartInOut", ofColor::mediumAquaMarine );
		ofDrawCircle( x, ErpEase::easeByKind(EaseKind::QuartInOut, start_y, end_y, ease_vals.c), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::QuartInOut));
		
		x+=x_step;
		easeLabel( "QuintInOut", ofColor::orange );
		ofDrawCircle( x, ErpEase::easeByKind(EaseKind::QuintInOut, start_y, end_y, ease_vals.c), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::QuintInOut));
		
		x+=x_step;
		// Test easeFunc pointer
		easeLabel( "CircInOut", ofColor::wheat );
		ofDrawCircle( x, testEaseFunc(start_y, end_y, ease_vals.c), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::CircInOut));
		
		
		// Wierder / Extreme ones
		
		x+=x_step;
		easeLabel( "BackInOut", ofColor::lemonChiffon );
		ofDrawCircle( x, ErpEase::easeByKind(EaseKind::BackInOut, start_y, end_y, ease_vals.c), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::BackInOut));
		
		/*x+=x_step;
		easeLabel( "ElasticIn", ofColor::cyan );
		ofDrawCircle( x, ErpEase::elasticIn(start_y, end_y, ease_vals.a), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::ElasticIn));
		
		x+=x_step;
		easeLabel( "ElasticOut", ofColor::magenta );
		ofDrawCircle( x, ErpEase::elasticOut(start_y, end_y, ease_vals.b), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::ElasticOut));*/
		
		x+=x_step;
		easeLabel( "ElasticInOut", ofColor::indianRed );
		ofDrawCircle( x, ErpEase::elasticInOut(start_y, end_y, ease_vals.c), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::ElasticInOut));
		

	/*	x+=x_step;
		easeLabel( "BounceIn", ofColor::pink );
		ofDrawCircle( x, ErpEase::bounceIn(start_y, end_y, ease_vals.a), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::BounceIn));
		
		x+=x_step;
		easeLabel( "BounceOut", ofColor::teal );
		ofDrawCircle( x, ErpEase::bounceOut(start_y, end_y, ease_vals.b), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::BounceOut));*/
		
		x+=x_step;
		easeLabel( "BounceInOut", ofColor::lavender );
		ofDrawCircle( x, ErpEase::bounceInOut(start_y, end_y, ease_vals.c), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::BounceInOut));
		
		
		x+=x_step;
		easeLabel( "ExpoInOut", ofColor::orchid );
		ofDrawCircle( x, ErpEase::expoInOut(start_y, end_y, ease_vals.c), crad);
		plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::ExpoInOut));
		
		
		// SloMos
		x+=x_step;
		easeLabel( "SloMo Ex.1", ofColor::chocolate);
		ofDrawCircle( x, ErpEase::slowMo(start_y, end_y, ease_vals.c, 0.005, 0.7), crad);
		// plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::ElasticInOut));
		
		x+=x_step;
		easeLabel( "SloMo Ex.2", ofColor::cadetBlue );
		ofDrawCircle( x, ErpEase::slowMo(start_y, end_y, ease_vals.c, 0.7, 0.4), crad);
		// plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::ElasticInOut));
			
		// slowMo(float start, float stop, float amt, float linear_ratio = 0.05, float power = 0.5)
		// linear_ratio: smaller this the smoother / slower the ins and outs  0.05; // 0.7;
		// power: higher this the flatter the slomo middle0.5; // 0.7;
		   
		// Stepped ease
		x+=x_step;
		easeLabel( "Stepped Ex.1", ofColor::rosyBrown );
		ofDrawCircle( x, ErpEase::stepped(start_y, end_y, ease_vals.c, 4), crad); // 32
		//plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::ElasticInOut));
		
		x+=x_step;
		easeLabel( "Stepped Ex.2", ofColor::coral );
		ofDrawCircle( x, ErpEase::stepped(start_y, end_y, ease_vals.c, 12), crad); // 12
		//plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::ElasticInOut));
		
		x+=x_step;
		easeLabel( "Stepped Ex.3", ofColor::mediumPurple );
		ofDrawCircle( x, ErpEase::stepped(start_y, end_y, ease_vals.c, 24), crad);
		//plotEasLine( x, ErpEase::getEaseFunctionPointer(EaseKind::ElasticInOut));
		
		
		// Log current value
		ofDrawBitmapStringHighlight( "v=" + ofToString(ease_vals.a), 12, 16); // start_y + (end_y - start_y) / 2); // EaseVal.a = " +
		
		
	}
	
	//--------------------------------------------------------------------
	
};
