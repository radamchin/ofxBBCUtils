
namespace bbc {
	namespace utils {
        namespace easing {
			 namespace Elastic {
				
				inline float easeIn(float t, float b, float c, float d ) {
					if (t==0) return b;  if ((t/=d)==1) return b+c;  
					float p=d*.3f;
					float a=c; 
					float s=p/4;
					return -(a*(float)powf(2,10*(t-=1)) * (float)sin( (t*d-s)*(2*(float)PI)/p )) + b;
				}

				inline float easeIn(float t, float b, float c, float d, float a, float p) {
					float s;
					if (t==0) return b;  if ((t/=d)==1) return b+c;  
					if (a < abs(c)) { a=c;  s=p/4; }
					else { s = p/(2*(float)PI) * (float)asin (c/a);}
					return -(a*(float)powf(2,10*(t-=1)) * (float)sin( (t*d-s)*(2*PI)/p )) + b;
				}

				inline float easeOut(float t, float b, float c, float d) {
					if (t==0) return b;  if ((t/=d)==1) return b+c;  
					float p=d*.3f;
					float a=c; 
					float s=p/4;
					return (a*(float)powf(2,-10*t) * (float)sin( (t*d-s)*(2*(float)PI)/p ) + c + b);	
				}

				inline float easeOut(float t, float b, float c, float d, float a, float p) {
					float s;
					if (t==0) return b;  if ((t/=d)==1) return b+c;  
					if (a < abs(c)) { a=c;  s=p/4; }
					else { s = p/(2*(float)PI) * (float)asinf(c/a);}
					return (a*(float)powf(2,-10*t) * (float)sin( (t*d-s)*(2*(float)PI)/p ) + c + b);	
				}

				inline float easeInOut(float t, float b, float c, float d) {
					if (t==0) return b;  if ((t/=d/2)==2) return b+c; 
					float p=d*(.3f*1.5f);
					float a=c; 
					float s=p/4;
					if (t < 1) return -.5f*(a*(float)powf(2,10*(t-=1)) * (float)sin( (t*d-s)*(2*(float)PI)/p )) + b;
					return a*(float)powf(2,-10*(t-=1)) * (float)sin( (t*d-s)*(2*(float)PI)/p )*.5f + c + b;
				}

				inline float easeInOut(float t, float b, float c, float d, float a, float p) {
					float s;
					if (t==0) return b;  if ((t/=d/2)==2) return b+c;  
					if (a < abs(c)) { a=c; s=p/4; }
					else { s = p/(2*(float)PI) * (float)asin (c/a);}
					if (t < 1) return -.5f*(a*(float)powf(2,10*(t-=1)) * (float)sin( (t*d-s)*(2*(float)PI)/p )) + b;
					return a*(float)powf(2,-10*(t-=1)) * (float)sin( (t*d-s)*(2*(float)PI)/p )*.5f + c + b;
				}

			}
        }
    }
}
