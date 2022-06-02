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

typedef enum  {
    None = -1,
    LinearInOut = 0,
    LinearIn,
    LinearOut,
    QuadInOut,
    QuadIn,
    QuadOut,
    CubicInOut,
    CubicIn,
    CubicOut,
    QuartInOut,
    QuartIn,
    QuartOut,
    QuintInOut,
    QuintIn,
    QuintOut,
    CircInOut,
    CircIn,
    CircOut,
    ExpoInOut,
    ExpoIn,
    ExpoOut,
    BackInOut,
    BackIn,
    BackOut,
    SineInOut,
    SineIn,
    SineOut,
    ElasticInOut,
    ElasticIn,
    ElasticOut,
    BounceInOut,
    BounceIn,
    BounceOut,
} EaseKind;

namespace ErpEase {
    
    // LINEAR
    static float linearInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Linear::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    static float linearIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Linear::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    static float linearOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Linear::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	// QUAD
    static float quadInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quad::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    static float quadIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quad::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    static float quadOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quad::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
  	

	// CUBIC
    static float cubicInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Cubic::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    static float cubicIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Cubic::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    static float cubicOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Cubic::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	// QUART
    static float quartInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quart::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    static float quartIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quart::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    static float quartOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quart::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	
	// QUINT
    static float quintInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quint::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    static float quintIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quint::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    static float quintOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Quint::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	
	// CIRC
    static float circInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Circ::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    static float circIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Circ::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    static float circOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Circ::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
    
    // EXPO
    static float expoInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Expo::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    static float expoIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Expo::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    static float expoOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Expo::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	// BACK
    static float backInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Back::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    static float backIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Back::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    static float backOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Back::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	// SINE
    static float sineInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Sine::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    static float sineIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Sine::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    static float sineOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Sine::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	// ELASTIC
    static float elasticInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Elastic::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    static float elasticIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Elastic::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    static float elasticOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Elastic::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
	
	// BOUNCE
    static float bounceInOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Bounce::easeInOut(amt, 0.0f, 1.0f, 1.0f);
    }
    static float bounceIn(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Bounce::easeIn(amt, 0.0f, 1.0f, 1.0f);
    }
    static float bounceOut(float start, float stop, float amt) {
        return start + (stop-start) * bbc::utils::easing::Bounce::easeOut(amt, 0.0f, 1.0f, 1.0f);
    }
    
    //------------------------------------------------------------------
    typedef float (*easeFunc)(float, float, float); // function pointer signiture

    //------------------------------------------------------------------

    static easeFunc getEaseFunctionPointer( EaseKind kind ) {
        switch(kind) {
            case LinearInOut: return &linearInOut;
            case LinearIn: return &linearIn;
            case LinearOut: return &linearOut;
            case QuadInOut: return &quadInOut;
            case QuadIn: return &quadIn;
            case QuadOut: return &quadOut;
            case CubicInOut: return &cubicInOut;
            case CubicIn: return &cubicIn;
            case CubicOut: return &cubicOut;
            case QuartInOut: return &quartInOut;
            case QuartIn: return &quartIn;
            case QuartOut: return &quartOut;
            case QuintInOut: return &quintInOut;
            case QuintIn: return &quintIn;
            case QuintOut: return &quintOut;
            case CircInOut: return &circInOut;
            case CircIn: return &circIn;
            case CircOut: return &circOut;
            case ExpoInOut: return &expoInOut;
            case ExpoIn: return &expoIn;
            case ExpoOut: return &expoOut;
            case BackInOut: return &backInOut;
            case BackIn: return &backIn;
            case BackOut: return &backOut;
            case SineInOut: return &sineInOut;
            case SineIn: return &sineIn;
            case SineOut: return &sineOut;
            case ElasticInOut: return &elasticInOut;
            case ElasticIn: return &elasticIn;
            case ElasticOut: return &elasticOut;
            case BounceInOut: return &bounceInOut;
            case BounceIn: return &bounceIn;
            case BounceOut: return &bounceOut;
            
        }
    }

    //------------------------------------------------------------------
    // Call an ease by an enum
    static float easeByKind(EaseKind kind, float start, float stop, float amt) {
        easeFunc func = ErpEase::getEaseFunctionPointer( kind );
        return func(start, stop, amt);
    }


}

#endif
