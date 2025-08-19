//
//  SloMo.h
//  ofxBBCUtilsDevApp
//
//  Created by Adam Hinshaw on 19/8/2025.
//

namespace bbc {
	namespace utils {
		namespace easing {
			namespace SloMo {
				
				inline float ease (float t, float b , float c, float d, float linear_ratio = 0.05, float power = 0.5 ) {
					
					// TODO: b,c,d are not used. Work out how to do these here.
					
					// linear_ratio: smaller this the smoother / slower the ins and outs  0.05; // 0.7;
					// power: higher this the flatter the slomo middle0.5; // 0.7;
					   
					float _p = (linear_ratio != 1.0) ? power : 0;
					float _p1 = (1 - linear_ratio) / 2;
					float _p2 = linear_ratio;
					float _p3 = _p1 + _p2;
					
					// need to calculate p
					
					float p = c*t/d + b;
					
					float r = p + (0.5 - p) * _p;
					
					if (p < _p1) {
						return r - ((p = 1 - (p / _p1)) * p * p * p * r);
					} else if (p > _p3) {
						return  r + ((p - r) * (p = (p - _p3) / _p1) * p * p * p);
					}
					return  r;
				}
				
				inline float easeIn (float t,float b , float c, float d) {
				   return ease(t, b, c, d);
				}

				inline float easeOut(float t,float b , float c, float d) {
				   return ease(t, b, c, d);
				}

				inline float easeInOut(float t,float b , float c, float d){
				   return ease(t, b, c, d);
				}

			}
		}
	}
}
