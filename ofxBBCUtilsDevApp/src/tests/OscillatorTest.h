//
//  OscillatorTest.h
//  ofxBBCUtilsDevApp
//
//  Created by Adam Hinshaw on 26/8/2025.
//
//	Dev playground for Oscillator functions

#pragma once

#include "TestRunner.h"
#include "Oscillator.h"

//--------------------------------------------------------------------
class OscillatorTest : public TestRunner {
	
public:
	
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

	//--------------------------------------------------------------------
	void setup() override {
		
		
		sineOscillator.setup("Sine", 0.005).setEnabled( true );
		sinePlotter.setup(24,48);
		
		sawOscillator.setup("Saw", 0.005).setType( bbc::utils::OSC_TYPE_SAW ).setEnabled( true );
		sawPlotter.setup(24,48);
		
		// Square, is a binary / blinking vibe
		squareOscillator.setup("Square", 0.005).setType( bbc::utils::OSC_TYPE_SQUARE ).setEnabled( true );
		squarePlotter.setup(24,48);
		
		// Randomesque but uses perlin noise.
		noiseOscillator.setup("Noise", 0.005).setType( bbc::utils::OSC_TYPE_NOISE ).setEnabled( true );
		noisePlotter.setup(24,48);
		
		noise2Oscillator.setup("Noise2", 0.005).setType( bbc::utils::OSC_TYPE_NOISE2 ).setEnabled( true );
		noise2Plotter.setup(24,48);
		
		
	}
	
	//--------------------------------------------------------------------
	void update() override {
		
	}
	
	//--------------------------------------------------------------------
	void draw( int _x = 0, int _y = 0 ) override {
		
		ofPushStyle();
		ofPushMatrix();
		
		float MAX_R = 60; // how big our circle is that shows this value.
		
		int DW = 320+(MAX_R*4.5);
		int DH = 180;
		int PADX = 50;
		int PADY = 50;
		
		ofTranslate( PADX, ofGetHeight()-DH-PADY ); //  ofGetWidth()-DW-
		
		// draw bg box
		ofSetColor(ofColor::white, 64);
		ofFill();
		ofDrawRectangle(0, 0, DW, DH);
		
		ofDrawBitmapStringHighlight( "Oscillators:", 5, -10);
		
		
		float dx = 1 * MAX_R;
		float dy = DH * .5;
		
		float v = sineOscillator.update();
		sinePlotter.add(v);
		
		float r = MAX_R * v;
		ofSetColor(ofColor::pink, 192);
		ofDrawCircle( dx, dy, r ); // d*.5, DH*.5
		ofDrawBitmapStringHighlight( "Sine", dx, DH * .75);
		//ofDrawBitmapStringHighlight(sineOscillator.toString(), 5, DH * .25);
		sinePlotter.draw(dx-sinePlotter.getWidth()/2); // 0, 0); // DH-sinePlotter.getHeight());
		
		
		v = sawOscillator.update();
		sawPlotter.add(v);
		
		r = MAX_R * v;
		ofSetColor(ofColor::lemonChiffon, 192);
		dx += MAX_R * 2;
		ofDrawCircle( dx, dy, r );
		ofDrawBitmapStringHighlight( "Saw", dx, DH * .75);
		//ofDrawBitmapStringHighlight(sawOscillator.toString(), 5, DH * .66);
		sawPlotter.draw(dx-sawPlotter.getWidth()/2); // 0, 0); // DH-sinePlotter.getHeight());
		
		
		v = squareOscillator.update();
		squarePlotter.add(v);
		r = MAX_R * v;
		ofSetColor(ofColor::cadetBlue, 192);
		dx += MAX_R * 2;
		ofDrawCircle( dx, dy, r );
		ofDrawBitmapStringHighlight( "Square", dx, DH * .75);
		//ofDrawBitmapStringHighlight(squareOscillator.toString(), 5, DH * .85);
		squarePlotter.draw(dx-squarePlotter.getWidth()/2);
		
		
		v = noiseOscillator.update();
		noisePlotter.add(v);
		r = MAX_R * v;
		ofSetColor(ofColor::seaGreen, 192);
		dx += MAX_R * 2;
		ofDrawCircle( dx, dy, r );
		ofDrawBitmapStringHighlight( "Noise", dx, DH * .75);
		//ofDrawBitmapStringHighlight(noiseOscillator.toString(), 5, DH * 1);
		noisePlotter.draw(dx-noisePlotter.getWidth()/2);
		
		
		v = noise2Oscillator.update();
		noise2Plotter.add(v);
		r = MAX_R * v;
		ofSetColor(ofColor::gold, 192);
		dx += MAX_R * 2;
		ofDrawCircle( dx, dy, r );
		ofDrawBitmapStringHighlight( "Noise2", dx, DH * .75);
		//ofDrawBitmapStringHighlight(noise2Oscillator.toString(), 5, DH * 1);
		noise2Plotter.draw(dx-noise2Plotter.getWidth()/2);
		
		ofPopMatrix();
		ofPopStyle();
		
	}
		
	//--------------------------------------------------------------------
	
};
