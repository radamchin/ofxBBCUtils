
namespace bbc {
	namespace utils {
        namespace easing {
            namespace Sine {
				
				inline float easeIn(float t, float b, float c, float d) {
					return -c * (float)cos(t/d * (PI/2)) + c + b;
				}

				inline float easeOut(float t, float b, float c, float d) {
					return c * (float)sin(t/d * (PI/2)) + b;	
				}

				inline float easeInOut(float t, float b, float c, float d) {
					return -c/2 * ((float)cos(PI*t/d) - 1) + b;
				}
	
			}
		}
    }
}
