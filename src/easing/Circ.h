
namespace bbc {
	namespace utils {
        namespace easing {
			 namespace Circ {
				
				inline float easeIn(float t, float b, float c, float d) {
					return -c * ((float)sqrt(1 - (t/=d)*t) - 1) + b;
				}
	
				inline float easeOut(float t, float b, float c, float d) {
					return c * (float)sqrt(1 - (t=t/d-1)*t) + b;
				}
	
				inline float easeInOut(float t, float b, float c, float d) {
					if ((t/=d/2) < 1) return -c/2 * ((float)sqrt(1 - t*t) - 1) + b;
					return c/2 * ((float)sqrt(1 - (t-=2)*t) + 1) + b;
				}

			}
        }
    }
}
