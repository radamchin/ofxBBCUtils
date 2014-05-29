
namespace bbc {
	namespace utils {
        namespace easing {
 			namespace Expo {
	
				inline float easeIn(float t, float b, float c, float d) {
					return (t==0) ? b : c * (float)powf(2, 10 * (t/d - 1)) + b;
				}

				inline float easeOut(float t, float b, float c, float d) {
					return (t==d) ? b+c : c * (-(float)powf(2, -10 * t/d) + 1) + b;	
				}

				inline float easeInOut(float t, float b, float c, float d) {
					if (t==0) return b;
					if (t==d) return b+c;
					if ((t/=d/2) < 1) return c/2 * (float)powf(2, 10 * (t - 1)) + b;
					return c/2 * (-(float)powf(2, -10 * --t) + 2) + b;
				}

			}	
        }
    }
}
