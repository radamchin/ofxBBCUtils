
namespace bbc {
	namespace utils {
        namespace easing {
			namespace Quad {
				
                inline float easeIn(float t, float b, float c, float d) {
                    return c*(t/=d)*t + b;
                }

                inline float easeOut(float t, float b, float c, float d) {
                    return -c *(t/=d)*(t-2) + b;
                }

                inline float easeInOut(float t, float b, float c, float d) {
                    if ((t/=d/2) < 1) return c/2*t*t + b;
                    return -c/2 * ((--t)*(t-2) - 1) + b;
                }

            }
		}
    }
}
