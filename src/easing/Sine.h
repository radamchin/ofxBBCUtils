
/*
 Here’s what each parameter means:

	t → time (the current progress).
	Usually starts at 0 and increases up to d.
	It’s the independent variable — where you are along the animation.

	b → begin value (the starting value of the property you’re animating).
	For example, if animating x from 100 to 300, then b = 100.

	c → change in value (the total distance to cover).
	It’s end - begin.
	In the example above: c = 300 - 100 = 200.

	d → duration (how long the animation lasts).
	Usually in the same units as t (frames, milliseconds, etc.).
	When t == d, the easing function should return b + c.
 */

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
