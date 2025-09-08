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

// Macros to generate easing functions for a given easing type

// Small building-block macros
#define DEFINE_EASING_IN(NAME, TYPE) \
	static float NAME##In(float start, float stop, float amt) { \
		return start + (stop-start) * bbc::utils::easing::TYPE::easeIn(amt, 0.0f, 1.0f, 1.0f); \
	}

#define DEFINE_EASING_OUT(NAME, TYPE) \
	static float NAME##Out(float start, float stop, float amt) { \
		return start + (stop-start) * bbc::utils::easing::TYPE::easeOut(amt, 0.0f, 1.0f, 1.0f); \
	}

#define DEFINE_EASING_INOUT(NAME, TYPE) \
	static float NAME##InOut(float start, float stop, float amt) { \
		return start + (stop-start) * bbc::utils::easing::TYPE::easeInOut(amt, 0.0f, 1.0f, 1.0f); \
	}

// Bigger macro that combines all three
#define DEFINE_EASING_FUNCS(NAME, TYPE) \
	DEFINE_EASING_IN(NAME, TYPE) \
	DEFINE_EASING_OUT(NAME, TYPE) \
	DEFINE_EASING_INOUT(NAME, TYPE)


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
	SloMo,
	Stepped
} EaseKind;

namespace ErpEase {
    
	DEFINE_EASING_FUNCS(linear, Linear)
	DEFINE_EASING_FUNCS(quad, Quad)
	DEFINE_EASING_FUNCS(cubic, Cubic)
	DEFINE_EASING_FUNCS(quart, Quart)
	DEFINE_EASING_FUNCS(quint, Quint)
	DEFINE_EASING_FUNCS(circ, Circ)
	DEFINE_EASING_FUNCS(expo, Expo)
	DEFINE_EASING_FUNCS(back, Back)
	DEFINE_EASING_FUNCS(sine, Sine)
	DEFINE_EASING_FUNCS(elastic, Elastic)
	DEFINE_EASING_FUNCS(bounce, Bounce)

	// SLOWMO
	static float slowMo(float start, float stop, float amt, float linear_ratio = 0.05, float power = 0.5) {
		return start + (stop-start) * bbc::utils::easing::SloMo::ease(amt, 0.0f, 1.0f, 1.0f, linear_ratio, power);
	}

	// STEPPED
	static float stepped(float start, float stop, float amt, int steps = 10 ) {
		return start + (stop-start) * bbc::utils::easing::Stepped::ease(amt, 0.0f, 1.0f, 1.0f, steps);
	}

    
    //------------------------------------------------------------------
    typedef float (*easeFunc)(float, float, float); // Function pointer signiture

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
			
			// Note SloMo & Stepped wont work here as they have different function signatures. TODO: work out how to do this (templates?)
			//case SlowMo: return &sloMo;
			//case Stepped: return &stepped;
        }
		
        return &linearInOut;
    }

    //------------------------------------------------------------------
    // Call an ease by an Enum
    static float easeByKind(EaseKind kind, float start, float stop, float amt) {
        easeFunc func = ErpEase::getEaseFunctionPointer( kind );
        return func(start, stop, amt);
    }


}

#endif
