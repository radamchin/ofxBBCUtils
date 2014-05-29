
namespace bbc {
	namespace utils {
        namespace easing {
			namespace Linear {
				
				inline float easeNone (float t, float b, float c, float d) {
					return c*t/d + b;
				}

				inline float easeIn (float t, float b, float c, float d) {
					return c*t/d + b;
				}

				inline float easeOut (float t, float b, float c, float d) {
					return c*t/d + b;
				}

				inline float easeInOut (float t, float b, float c, float d) {
					return c*t/d + b;
				}

			}
        }
    }
}
