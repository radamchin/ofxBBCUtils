//
//  Stepped.h
//  ofxBBCUtilsDevApp
//
//  Created by Adam Hinshaw on 19/8/2025.
//

namespace bbc {
	namespace utils {
		namespace easing {
			namespace Stepped {
				
				inline float ease (float t, float b, float c, float d, int _steps = 10 ) {
					
					// TODO: b,c,d are not used. Work out how to do these here.
					
					if (_steps <= 1) {
						// With 1 or fewer steps, behave as a linear ease.
						return t;
					}
					
					// If we’re exactly at the end, snap to 1.0
					if (t >= 1) {
					  return 1;
					}
				
					float steps = (float)_steps;
					
					// Each step size.
					float step_size = 1.0 / (steps); // always add extra step so we can get to 1.0
					
					// Determine current step index (0-based), clamped to [0, steps - 1].
					//int step_index = glm::min( steps - 1, glm::floor(t / step_size) );
					int step_index = glm::round(t / step_size);
					
					// Return the stepped value.					
					return step_index * step_size;
				}
				
				inline float easeIn (float t, float b, float c, float d) {
				   return ease(t, b, c, d);
				}

				inline float easeOut(float t, float b, float c, float d) {
				   return ease(t, b, c, d);
				}

				inline float easeInOut(float t, float b, float c, float d){
				   return ease(t, b, c, d);
				}

			}
		}
	}
}
