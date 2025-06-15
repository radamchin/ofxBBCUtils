//
//  Oscillator.h
//  bbcUtils
//
//  Created by Adam Hinshaw on 29/3/22.
//
//  Back and forth between two values at a speed
//

/**

 TODO:
 
* Add a setup that can set type
 
 * Could add an ofParameter<index> to alllow changing??
 
 * Match step affect on time to the SINE.
        + So 2 plotters with same step will be at similar position?
        + use PI??
 
 * OSC_TYPE_NOISE use perlin or inbuilt noce
    -see: https://necessarydisorder.wordpress.com/2017/11/15/drawing-from-noise-and-then-making-animated-loopy-gifs-from-there/
        - note the golan levin cicular loop concept
                - NOTE: there is ofSignedNoise() too to do our ramp
 
 * Support some kind of combining of outputs of multiple to create detailed waves? Average between them? Visualise to proof. Think multiple sine waves
 
 */

#ifndef bbcOscillator_h
#define bbcOscillator_h

#include "ofMain.h"
#include "ofParameter.h"

namespace bbc {
    namespace utils {
        
        //------------------------------------------------------------------------
        enum OscillatorType {
			OSC_TYPE_DEFAULT = -1,
            OSC_TYPE_SINE = 0,
            OSC_TYPE_SAW,       // linear tween
            OSC_TYPE_SQUARE,    // on off
            OSC_TYPE_NOISE,     // noise based
            OSC_TYPE_NOISE2     // alt noise based
        };
   
        //------------------------------------------------------------------------
    
        class Oscillator {
            
        private:
            
        protected:
            
        public:
            
            ofParameterGroup params;
            
            ofParameter<bool> enabled{"Enabled", false};
            ofParameter<float> speed;
            
            float step;
            
            float range_start;
            float range_end;
            
            bool _setup;
            
            string name;
            
            OscillatorType type = OSC_TYPE_SINE;
            
            //------------------------------------------------------------------------
            Oscillator() {
                _setup = false;
                step = 0;
                range_start = 0.0;
                range_end = 1.0;
            }
            
            //------------------------------------------------------------------------
            Oscillator & setup() {
                return setup("");
            }
			
			//------------------------------------------------------------------------
            Oscillator & setup( const string _name ) {
                return setup(_name, 0.5, 0.0, 1.0);
            }
			
			//------------------------------------------------------------------------
            Oscillator & setup( const string _name, float _speed ) {
                return setup(_name, _speed, std::max(_speed*.5, 0.00001), _speed * 2);
            }
			
			//------------------------------------------------------------------------
            Oscillator & setup( const string _name, float _speed, float _speed_min, float _speed_max ) {
                
                _setup = true;
                name = _name;
                params.setName("Osc. " + _name + "");
                //params.add( enabled.set("Enabled [Osc. " + _name + "]", false) );
                //speed.setName("Speed [Osc. " + _name + "]");
                params.add( enabled );
                speed.setName("Speed");
                params.add( speed );
                
                setSpeed( _speed );
                setSpeedRange( _speed_min, _speed_max );
                
                return *this;
            }
            
            //------------------------------------------------------------------------
            Oscillator & setEnabled( const bool b ) {
                enabled = b;
                return *this;
            }
            
            //------------------------------------------------------------------------
            bool getEnabled() {
                return enabled;
            }
            
            //------------------------------------------------------------------------
            void mapStepTo( int i ) {
                mapStepTo( (float)i );
            }
            
            //------------------------------------------------------------------------
            void mapStepTo( float val ) {
            
                // Update step value to an external value. Preset it.
            
               if(type == OSC_TYPE_SINE) {
                   
                   // What radian value would yeild a result of val, between range_start and range_end.
                   // map val between -1..1, arc sin
                   
                   // TODO: handle < 0: So if a oscillator is going backwards in last update, we want this to resume going backwards?
                   // TODO: handle when f is outside of the range, as it will jump.
                   
                   float n = ofMap(val, range_start, range_end, 0, 1);
                   step = asin(n);
                   
               } else if( type == OSC_TYPE_SAW ) {
                   
                   step = ofMap(val, range_start, range_end, 0, 1);
                   
               }else if( type == OSC_TYPE_SQUARE ) {
                   
                   // TODO: Implement for square
                   
                   
               }else if( type == OSC_TYPE_NOISE ) {
                   
                   // TODO: implement for noise
                   
               }else if( type == OSC_TYPE_NOISE2) {
                   
                   // TODO: implement for noise
               }
               
            }
           
            //------------------------------------------------------------------------
            float update() {
                
				if (!_setup || !enabled) return 0;
                
                step += speed.get();
                
                return getValue();
            }
            
            //------------------------------------------------------------------------
            float getRawValue() { // -1.0..1.0
                
                if(type == OSC_TYPE_SINE) {
                    
                    return sin(step);
                    
                }else if(type == OSC_TYPE_SAW) {
                    
                    // A linear variation
                    int i = floor(step);
                    float f = step - i;
                    // Note: Might not need the ternary tests for 0 =, trying to make sure it hits the final value.
                    if(i % 2 == 0) { // Even, 0..1
                        return f == 0 ? 1 : f;
                    }else{  // Odd, -1..0,
                        return f == 0 ? -1 : -(1-f);
                    }
                    
                }else if(type == OSC_TYPE_SQUARE) {
                    
                    // Use same linear variation but hard cut it.
                    int i = floor(step);
                    if(i % 2 == 0) { // Even
                        return 1;
                    } else { // Odd
                        return -1;
                    }
                    
                    
                }else if(type == OSC_TYPE_NOISE) {
                   
                    float n = ofNoise(step); // 0..1
                   // float n = ofNoise(step, ofGetFrameNum()); // 0..1  HELLA NOISY
                    //return n;
                    // could use ofSignedNoise(step) isntead as one call.
                    return (n * 2) - 1; // -1..1
                    
                }else if(type == OSC_TYPE_NOISE2) {
                    
                    float n = ofSignedNoise(step, 0); // -1..1
                    return n;
                    
                }
                
                return 0;
            }
            
            //------------------------------------------------------------------------
            float getValue() {
                
                // getRawValue =  -1..1
                float p = getRawValue();
                
                if(type != OSC_TYPE_SAW) {
                    // Make this 0..1 relative / normalised
                    p = (p + 1) * .5;
                }
                
                float dist = range_end - range_start;
                float v = range_start + abs(dist * p);
                return v;
            }
            
            //------------------------------------------------------------------------
            void setSpeed( float v ) {
                speed = v;
            }
            
            //------------------------------------------------------------------------
            Oscillator & setSpeedRange( float _min, float _max ) {
                speed.setMin(_min);
                speed.setMax(_max);
                return *this;
            }
            
            //------------------------------------------------------------------------
            Oscillator & setOutputRange( float a, float b) {
                range_start = a;
                range_end = b;
                return *this;
            }
            
            //------------------------------------------------------------------------
            Oscillator & setType( OscillatorType t ) {
                type = t;
                return *this;
            }
            
            //------------------------------------------------------------------------
            string toString() {
				std::ostringstream out;
                out << "[Oscillator '" << name << "' val=" << getValue() << ", raw=" << getRawValue() << ", type:" << type << ", speed=" << speed << " {" << speed.getMin() << "," << speed.getMax() << "}" << ", range={" << range_start << "," << range_end << "}" << ", step:" << step << " ]";
                return out.str();
            }
            
        };
    }
}

#endif /* bbcOscillator_h */
