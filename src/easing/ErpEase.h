/*
 *  ErpEase
 *
 *  Robert Penner based easing based Lerp (Linear(ish) Interpolation) methods
 *	
 *
 *  Created by Adam Hinshaw on 25/02/14.
 *  Copyright 2012 BigBrownCupboard. All rights reserved.
 *
 */

#ifndef _BBC_ERP_EASE
#define _BBC_ERP_EASE 

#include "easing.h"

namespace ErpEase {
             
    // LINEAR
    inline float linearInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Linear::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float linearIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Linear::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float linearOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Linear::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	// QUAD
    inline float quadInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quad::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float quadIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quad::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float quadOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quad::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
  	

	// CUBIC
    inline float cubicInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Cubic::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float cubicIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Cubic::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float cubicOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Cubic::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	// QUART
    inline float quartInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quart::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float quartIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quart::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float quartOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quart::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	
	// QUINT
    inline float quintInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quint::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float quintIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quint::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float quintOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quint::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	
	// CIRC
    inline float circInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Circ::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float circIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Circ::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float circOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Circ::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
    
    // EXPO
    inline float expoInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Expo::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float expoIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Expo::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float expoOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Expo::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	// BACK
    inline float backInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Back::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float backIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Back::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float backOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Back::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	// SINE
    inline float sineInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Sine::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float sineIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Sine::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float sineOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Sine::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	// ELASTIC
    inline float elasticInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Elastic::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float elasticIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Elastic::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float elasticOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Elastic::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	// BOUNCE
    inline float bounceInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Bounce::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float bounceIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Bounce::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    inline float bounceOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Bounce::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
    
}

#endif
