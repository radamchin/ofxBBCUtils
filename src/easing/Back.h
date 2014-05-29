
namespace bbc {
	namespace utils {
        namespace easing {
             namespace Back {
			
				inline float easeIn(float t, float b, float c, float d) {
                    float s = 1.70158f;
                    return c*(t/=d)*t*((s+1)*t - s) + b;
                }
               
                inline float easeIn(float t, float b, float c, float d, float s) {
                    return c*(t/=d)*t*((s+1)*t - s) + b;
                }
               
                inline float easeOut(float t, float b, float c, float d) {
                    float s = 1.70158f;
                    return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
                }
               
                inline float easeOut(float t, float b, float c, float d, float s) {
                    return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
                }
               
                inline float easeInOut(float t, float b, float c, float d) {
                    float s = 1.70158f;
                    if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525f))+1)*t - s)) + b;
                    return c/2*((t-=2)*t*(((s*=(1.525f))+1)*t + s) + 2) + b;
                }
               
                inline float easeInOut(float t, float b, float c, float d, float s) {	
                    if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525f))+1)*t - s)) + b;
                    return c/2*((t-=2)*t*(((s*=(1.525f))+1)*t + s) + 2) + b;
                }
               
			}
        }
    }
}