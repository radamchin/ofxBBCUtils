//
//  Oscillator.h
//  bbcUtils
//
//  Created by Adam Hinshaw on 29/3/22.
//
//  Back and forth at a speed
//

/**
    TODO:
    * Implement Saw: Linear    
    * Implement Square: ON / OFF
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
            OSC_TYPE_SINE = 0,
            OSC_TYPE_SAW,
            OSC_TYPE_SQUARE
        };
   
        //------------------------------------------------------------------------
    
        class Oscillator {
            
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
            
            void setup() {
                setup("");
            }
            
            void setup( const string _name ) {
                setup(_name, 0.5, 0.0, 1.0);
            }
            
            void setup( const string _name, float _speed ) {
                setup(_name, _speed, std::max(_speed*.5, 0.00001), _speed * 2);
            }
            
            void setup( const string _name, float _speed, float _speed_min, float _speed_max ) {
                
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
            }
            
            //------------------------------------------------------------------------
            void setEnabled( const bool b ) {
                enabled = b;
            }
            
            bool getEnabled() {
                return enabled ;
            }
            //------------------------------------------------------------------------
            float update() {
                
                if(!_setup) return;
                
                step += speed.get();
                
                return getValue();
            }
            
            //------------------------------------------------------------------------
            float getRawValue() { // -1.0..1.0
                
                if(type == OSC_TYPE_SINE) {
                    return sin(step);
                    
                }else if(type == OSC_TYPE_SAW) {
                    // TODO a linear variation
                    // return  if odd, -1 .. 0, even, 0 ..1
                    
                }else if(type == OSC_TYPE_SQUARE) {
                    
                }
                
                return 0;
            }
            
            //------------------------------------------------------------------------
            float getValue() {
                float p = getRawValue();
                float dist = range_end - range_start;
                float v = range_start + abs(dist * p);
                return v;
            }
            
            //------------------------------------------------------------------------
            float setSpeed( float v ) {
                speed = v;
            }
            
            float setSpeedRange( float _min, float _max ) {
                speed.setMin(_min);
                speed.setMax(_max);
            }
            
            //------------------------------------------------------------------------
            void setOutputRange( float a, float b) {
                range_start = a;
                range_end = b;
            }
            
            void setType(  OscillatorType t ) {
                type = t;
            }
            
            //------------------------------------------------------------------------
            string toString() {
                ostringstream out;
                out << "[Oscillator '" << name << "' val=" << getValue() << ", raw=" << getRawValue() << ", type:" << type << ", speed=" << speed << " {" << speed.getMin() << "," << speed.getMax() << "}" << ", range={" << range_start << "," << range_end << "}" << " ]";
                return out.str();
            }
            
        };
    }
}

#endif /* bbcOscillator_h */
