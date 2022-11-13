//
//  Spiral.h
//  Spiral
//  Created by Adam Hinshaw on 9/8/22.
//
//  Generate Spirals
// 

#ifndef Spiral_h
#define Spiral_h

namespace bbc {
    namespace utils {

        class Spiral {

        public:

            //--------------------------------------------------------------
            static void drawPoint( float x, float y, float dim = 18 ) {
                ofPushStyle();
                ofNoFill();
                ofSetColor(128,128,128,128);
                ofDrawEllipse(x,y,dim,dim);
                
                ofSetColor(255,0,0,128);
                //ofFill();
                //ofDrawEllipse(x,y,5,5);
                // DRAW A CROSS
                ofDrawLine(x-5,y,x+5,y);
                ofDrawLine(x,y-5,x,y+5);
                ofPopStyle();
            }

            //--------------------------------------------------------------
            static ofPoint getPosition( float n, float cx, float cy, float radius, float coils, float rotation, bool clockwise = true ) {
                // Return a point
                
                ofPoint pos(cx, cy);
                
                float thetaMax = coils * TWO_PI; // maximum radian
                float awayStep = radius / thetaMax;  // How far to step away from center for each side.
                
                float theta = n * thetaMax;
                
                float away = awayStep * theta;  // How far away from center
                
                float around = theta + rotation;  // How far around the center.
                 
                // Convert 'around' and 'away' to X and Y.
                if(clockwise) {
                    pos.x = cx + cos(around) * away;
                } else {
                    pos.x = cx - cos(around) * away;
                }

                pos.y = cy + sin(around) * away;
                
                return pos;
            }
            
            //--------------------------------------------------------------
            static void drawSpiral2(float cx, float cy, float radius, float coils, float rot, float point_every = 0.001, bool clockwise = true, bool lines_between = true) {
                
                // Variation draw, putting points at intervals (instead of using a distance
                
                float p = 0;
                
                point_every = point_every <= 0 ? 0.001 : point_every;
                
                ofPoint last_pos(cx, cy);
                
                bool last_pos_drawn = false;
                
                while(!last_pos_drawn) {
                    
                    if(p+point_every >= 1.0) { // always draw last point
                        p = 1.0;
                        last_pos_drawn = true; // cause loop to end after this pass
                    }
                    
                    ofPoint pos = getPosition(p, cx, cy, radius, coils, rot, clockwise);
                    
                    if(lines_between) {
                        ofSetColor(255,255,255,128);
                        ofDrawLine(last_pos, pos);
                    }
                    
                    drawPoint(pos.x, pos.y);
                    
                    last_pos.set(pos);
                    
                    p += point_every;
                    
                }
                 
                 
             }

            //--------------------------------------------------------------
            static void drawSpiral(float cx, float cy, float radius, float coils, float rotation, float dist_between_points, int total = 0, bool clockwise = true, bool lines_between = true) {
              
                // dist_between_points = distance between points to plot
              
                float thetaMax = coils * TWO_PI;
                float awayStep = radius / thetaMax;  // How far to step away from center for each side.
              
                drawPoint(cx, cy);
              
                // For every side, step around and away from center.
                // start at the angle corresponding to a distance of chord
                // away from centre.

                int c = 1;
                float theta = dist_between_points / (awayStep * 1); // first point after centre, Could make smaller step to make centre a bit rounder
                
                float lx = cx;
                float ly = cy;
                
                while(theta <= thetaMax) {

                    /*  if(clockwise) {
                    }else{
                    }*/

                    //for(float theta = chord / awayStep; theta <= thetaMax; c++) {

                    if(total && c >= total) break;

                    float away = awayStep * theta;  // How far away from center
                    float around = theta + rotation;  // How far around the center.
                  
                    // Convert 'around' and 'away' to X and Y.
                    float x;
                    if(clockwise) {
                        x = cx + cos(around) * away;
                    }else{
                        x = cx - cos(around) * away;
                    }
                    
                    float y = cy + sin(around) * away;
                    
                    
                    if(lines_between) {
                        ofSetColor(255,255,255,128);
                        ofDrawLine(lx,ly,x,y);
                    }
                        
                    drawPoint(x, y);

                    lx = x;
                    ly = y;

                    float delta = dist_between_points / away;
                    //float delta = -2 * away + sqrt(4 * away * away + 8 * awayStep * dist_between_points);

                    // to a first approximation, the points are on a circle
                    // so the angle between them is chord/radius
                    theta += delta;

                    c++;
                }
              
            }

        };
    
    }

}

#endif /* Spiral_h */
