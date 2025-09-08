
/*
 
 Drawing
 
 Drawing helpers and utils.
 
 Adam Hinshaw 2025
 
 
 */

#ifndef bbcDrawing_h
#define bbcDrawing_h

#include "ofMain.h"
#include <regex>

namespace bbc {

    namespace utils {
        
        //---------------------------------------------------------------------------
		
        static void drawGrid(float size, int w, int h, const ofColor onColor = ofColor::gainsboro, const ofColor offColor = ofColor::gray) {
            // taken from https://github.com/openframeworks/openFrameworks/issues/5217

            static ofMesh gridMesh;
			
            gridMesh.clear();
            gridMesh.setMode(OF_PRIMITIVE_TRIANGLES);
        #ifndef TARGET_EMSCRIPTEN
        #ifdef TARGET_OPENGLES
            if(ofIsGLProgrammableRenderer()) gridMesh.setUsage(GL_STREAM_DRAW);
        #else
         //   gridMesh.setUsage(GL_STREAM_DRAW);
        #endif
        #endif

            std::vector<glm::vec3> verts;

            for (std::size_t y = 0; y < 3; ++y){
                for (std::size_t x = 0; x < 3; ++x) {
                    verts.push_back({x * size, y * size, 0.f});
                }
            }

            std::vector<ofColor> colors = { onColor, offColor };

            float twoSize = size * 2;

            for (std::size_t y = 0; y < h; y += twoSize){
                for (std::size_t x = 0; x < w; x += twoSize){
                    glm::vec3 offset(x, y, 0.f);
                    for (std::size_t i = 0; i < 2; ++i){
                        gridMesh.addVertex(verts[i + 0] + offset);
                        gridMesh.addColor(colors[i]);
                        gridMesh.addVertex(verts[i + 3] + offset);
                        gridMesh.addColor(colors[i]);
                        gridMesh.addVertex(verts[i + 4] + offset);
                        gridMesh.addColor(colors[i]);
                        gridMesh.addVertex(verts[i + 0] + offset);
                        gridMesh.addColor(colors[i]);
                        gridMesh.addVertex(verts[i + 4] + offset);
                        gridMesh.addColor(colors[i]);
                        gridMesh.addVertex(verts[i + 1] + offset);
                        gridMesh.addColor(colors[i]);

                        std::size_t j = colors.size() - i - 1;

                        gridMesh.addVertex(verts[i + 3] + offset);
                        gridMesh.addColor(colors[j]);
                        gridMesh.addVertex(verts[i + 6] + offset);
                        gridMesh.addColor(colors[j]);
                        gridMesh.addVertex(verts[i + 7] + offset);
                        gridMesh.addColor(colors[j]);
                        gridMesh.addVertex(verts[i + 3] + offset);
                        gridMesh.addColor(colors[j]);
                        gridMesh.addVertex(verts[i + 7] + offset);
                        gridMesh.addColor(colors[j]);
                        gridMesh.addVertex(verts[i + 4] + offset);
                        gridMesh.addColor(colors[j]);
                    }
                }
            }

            GLboolean depthMaskEnabled;
            glGetBooleanv(GL_DEPTH_WRITEMASK,&depthMaskEnabled);
            glDepthMask(GL_FALSE);
            gridMesh.draw();
            if(depthMaskEnabled){
                glDepthMask(GL_TRUE);
            }
			
        }
		
		//---------------------------------------------------------------------------
		static void drawBackgroundGrid(float size,  const ofColor onColor = ofColor::gainsboro, const ofColor offColor = ofColor::gray) {
				
			drawGrid(size, ofGetViewportWidth(), ofGetViewportHeight(), onColor, offColor);
			
		}
			
        //---------------------------------------------------------------------------
		static void drawCalibration(int alpha = 255, const ofColor mainColor = ofColor::white, float thickness =  2.0f, float w = 0, float h = 0) {
            /*
             Draw a screen calibration graphic, useful for projection calibration,
             */
            
            ofPushStyle();
            
            ofSetLineWidth(thickness);
            
            w = w > 0 ? w : ofGetWidth();
            h = h > 0 ? h : ofGetHeight();
            
            float cx = w / 2.0;
            float cy = h / 2.0;
            
            float half_thick = thickness / 2.0;
            
            ofSetCircleResolution(36);
            
            ofSetColor(mainColor, alpha);
            ofNoFill();
            
            // border
            ofRectMode(OF_RECTMODE_CORNER);
            ofDrawRectangle(half_thick, half_thick, w-thickness, h-thickness);
            
            // diagonal lines
            ofDrawLine(half_thick, half_thick, w+half_thick, h-half_thick);
            ofDrawLine(-half_thick, h-half_thick, w-half_thick, half_thick);
            
            // centre lines
            ofDrawLine(cx, 0, cx, h);
            ofDrawLine(0, cy, w, cy);
            
            // horizontal 1/4 lines
            ofDrawLine(0, h/4, w, h/4);
            ofDrawLine(0, h-h/4, w, h-h/4);
            
            // Draw centre rect & circle
            ofRectMode(OF_RECTMODE_CENTER);
            
            float dim = glm::min(w, h) * .66f;
            
            ofDrawEllipse(cx, cy, dim, dim);
            
            // Draw more comprehensive grid
            
            // do this at the ratio of the screen?
            // TODO: make the ratio dynamic too reading getWidth and getHeight
            float wc = 16.0f;
            float hc = 9.0f;
            
            float grid_x = w / wc;
            float grid_y = h / hc;
            
            ofSetColor(mainColor, alpha);
            
            ofSetLineWidth(half_thick);
            // vertical lines
            for(int col = 1; col < wc; col++) {
                int gx = round(col * grid_x);
                ofDrawLine(gx, 0, gx, h);
            }
            
            // horizontal lines
            for(int row = 1; row < hc; row++) {
                int gy = round(row * grid_y);
                ofDrawLine(0, gy, w, gy);
            }
            
            ofSetLineWidth(thickness);
            
            // Draw circles at the sides
            
            int n = 6;
            float mini_rad = h / n;
            float y;
            
            for(int i = 0; i<n-1; i++) {
                y = (mini_rad)+(i*mini_rad);
                int c = i % 4;
                switch(c) {
                    case 0: ofSetColor(255, alpha); break;
                    case 1: ofSetColor(255,0,0, alpha); break;
                    case 2: ofSetColor(0,255,0, alpha); break;
                    case 3: ofSetColor(0,0,255, alpha); break;
                }
                
                ofDrawEllipse(0, y, mini_rad, mini_rad); // LHS
                ofDrawEllipse(w, y, mini_rad, mini_rad); // RHS
            }
            
            
            ofPopStyle();
            
        }
	
        //---------------------------------------------------------------------------
        // Draw a line with percentage offsets
        static void drawOffsetLine(const ofVec2f& start, const ofVec2f& end, float startOffsetPercent = 0.0, float endOffsetPercent = 0.0, float lineWidth = 2.0) {
           
            // Calculate the direction vector
           ofVec2f direction = end - start;

           // Calculate the offset distances
           float startOffsetDistance = startOffsetPercent * direction.length();
           float endOffsetDistance = endOffsetPercent * direction.length();

           // Normalize the direction vector to get the unit vector
           direction.normalize();

           // Calculate the new start and end points
           ofVec2f newStart = start + direction * startOffsetDistance;
           ofVec2f newEnd = end - direction * endOffsetDistance;

           // Draw the line
           ofSetLineWidth(lineWidth);
           ofDrawLine(newStart, newEnd);
       }
    
		//---------------------------------------------------------------------------
		static void drawDashedLine(const glm::vec3& start, const glm::vec3& end, float dashLength = 10.0f, float gapLength = 5.0f) {
			
			glm::vec3 direction = end - start;
			float totalLength = glm::length(direction);
			if (totalLength == 0) return;

			glm::vec3 unitDir = glm::normalize(direction);
			float drawnLength = 0.0f;

			while (drawnLength < totalLength) {
				float thisDash = std::min(dashLength, totalLength - drawnLength);
				glm::vec3 p1 = start + unitDir * drawnLength;
				glm::vec3 p2 = start + unitDir * (drawnLength + thisDash);

				ofDrawLine(p1, p2);
				drawnLength += thisDash + gapLength;
			}
		}
	
		//---------------------------------------------------------------------------
		static void drawDashedEllipseLine( float centerX, float centerY, float radiusX, float radiusY, float startAng = 0, ofColor col = ofColor::white, float thickness = 0.5, float dashLength = 5, float gapLength = 5 ) {
			
			float stepAngle = 0.01f;
			float angle = 0.0f;
			float arcLength = 0.0f;
			bool drawDash = true;

			// Apply the starting angle offset to the first point
			glm::vec2 firstPoint = {
			   centerX + cos(startAng) * radiusX,
			   centerY + sin(startAng) * radiusY
			};
			glm::vec2 lastPoint = firstPoint;
			
			ofPushStyle();
			
			ofSetColor(col, 128);
			ofSetLineWidth(thickness);
		
			while (angle <= TWO_PI) {
				angle += stepAngle;
				float a = startAng + angle;
				
				glm::vec2 point = {
					centerX + cos(a) * radiusX,
					centerY + sin(a) * radiusY
				};
				
				float segmentLength = glm::distance(lastPoint, point);
				arcLength += segmentLength;
				
				if (drawDash) {
					ofDrawLine(lastPoint, point);
				}
				
				if ((drawDash && arcLength >= dashLength) ||
					(!drawDash && arcLength >= gapLength)) {
					drawDash = !drawDash;
					arcLength = 0;
				}
				
				lastPoint = point;
			}

			// Optionally close the ellipse cleanly
			float closingSegment = glm::distance(lastPoint, firstPoint);
			if (drawDash && closingSegment > 0.1f) {
				if (arcLength + closingSegment <= dashLength) {
					ofDrawLine(lastPoint, firstPoint);
				}
			}
			
			ofPopStyle();
			
		}
	
		//---------------------------------------------------------------------------
	
		// https://chatgpt.com/c/682485bc-c0d0-8003-af18-83d48fd98c70
		static ofMesh getDashedEllipseMesh(glm::vec3 center,
									 float radiusX, float radiusY,
									 glm::vec3 normal = {0, 0, 1},
									 float startAngle = 0.0f,
									 float dashLength = 10.0f, float gapLength = 5.0f,
									 float resolution = 0.01f) {
			ofMesh dashedMesh;
			dashedMesh.setMode(OF_PRIMITIVE_LINES);

			float angle = 0.0f;
			float arcLength = 0.0f;
			bool drawing = true;

			glm::vec3 lastPoint;

			// Build rotation matrix to orient the ellipse into 3D
			glm::vec3 defaultNormal = glm::vec3(0, 0, 1);
			glm::quat orientation = glm::rotation(defaultNormal, glm::normalize(normal));

			bool hasLast = false;

			while (angle <= TWO_PI) {
				float a = startAngle + angle;

				glm::vec3 local = {
					cos(a) * radiusX,
					sin(a) * radiusY,
					0
				};

				glm::vec3 point = center + orientation * local;

				if (hasLast) {
					float segmentLength = glm::distance(lastPoint, point);
					arcLength += segmentLength;

					if (drawing) {
						dashedMesh.addVertex(lastPoint);
						dashedMesh.addVertex(point);
					}

					if ((drawing && arcLength >= dashLength) ||
						(!drawing && arcLength >= gapLength)) {
						drawing = !drawing;
						arcLength = 0;
					}
				}

				lastPoint = point;
				hasLast = true;
				angle += resolution;
			}

			return dashedMesh;
		}
		
		//---------------------------------------------------------------------------
		static void drawRotatedBitmapStringHighlight(string txt, int x = 0, int y = 0, int angle_deg = -90, ofColor background = ofColor::black, ofColor foreground  = ofColor::white ) {
			ofPushMatrix();
			 // Move to the position where you want text anchored
			 ofTranslate(x, y);

			 // Rotate 90 degrees around Z axis (since we're in 2D)
			 ofRotateDeg(angle_deg);  // or -90 for opposite direction
			
			 ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);
			 // Draw string at the new origin
			 ofDrawBitmapStringHighlight( txt, 0, 0, background, foreground );

			 ofSetDrawBitmapMode(OF_BITMAPMODE_SIMPLE); // reset to default
			
			 ofPopMatrix();
		}

		//---------------------------------------------------------------------------
		static void drawCross(float cx, float cy, float size, float thickness, ofColor color, bool as_x = true ) {
			// https://chatgpt.com/c/6825cbdf-c220-8003-b132-4e536e7530bc
			ofPushMatrix();
			ofTranslate(cx, cy);
			if(as_x) ofRotateDeg(45); // Rotate to align cross arms like "X"
			ofSetColor(color);
			ofFill();

			float halfSize = size * 0.5;
			float halfThickness = thickness * 0.5;

			// First bar (horizontal after rotation)
			ofBeginShape();
			ofVertex(-halfSize, -halfThickness);
			ofVertex(halfSize, -halfThickness);
			ofVertex(halfSize, halfThickness);
			ofVertex(-halfSize, halfThickness);
			ofEndShape(true);

			// Second bar (vertical after rotation)
			ofBeginShape();
			ofVertex(-halfThickness, -halfSize);
			ofVertex(halfThickness, -halfSize);
			ofVertex(halfThickness, halfSize);
			ofVertex(-halfThickness, halfSize);
			ofEndShape(true);

			ofPopMatrix();
		}
	
	
		//---------------------------------------------------------------------------
		static void offsetPolyline(ofPolyline &poly, float dx, float dy) {
			 for (auto &v : poly.getVertices()) {
				 v.x += dx;
				 v.y += dy;
			 }
		 }

		//---------------------------------------------------------------------------
		static ofPolyline offsetCopyPolyline(const ofPolyline &poly, float dx, float dy) {
			 ofPolyline shifted;
			 for (auto v : poly.getVertices()) {
				 v.x += dx;
				 v.y += dy;
				 shifted.addVertex(v);
			 }
			 shifted.close();
			 return shifted;
		 }
	
		//---------------------------------------------------------------------------
		static glm::vec2 getRandomPointInsidePolyline(const ofPolyline &poly) {
			ofRectangle box = poly.getBoundingBox();
			glm::vec2 p;
			do {
				p = glm::vec2(ofRandom(box.x, box.x + box.width),
							  ofRandom(box.y, box.y + box.height));
			} while (!poly.inside(glm::vec3(p, 0)));
			return p;
		}
	
		//---------------------------------------------------------------------------
		static glm::vec2 getRandomPointInsidePolyline( const ofPolyline &poly, const vector<ofPolyline>& obstacles ) {
			ofRectangle box = poly.getBoundingBox();
			glm::vec2 p;
			bool valid = false;

			do {
				p = glm::vec2(ofRandom(box.x, box.x + box.width),
								 ofRandom(box.y, box.y + box.height));

				// Check inside main poly
				if (!poly.inside(glm::vec3(p, 0))) continue;

				// Check outside all obstacles
				valid = true;
				for (const auto& o : obstacles) {
					if (o.inside(glm::vec3(p, 0))) {
						valid = false;
						break;
					}
				}

			} while (!valid);

			return p;
		}
	
		//---------------------------------------------------------------------------
		// Cubic Bezier interpolation
		static glm::vec2 cubicBezier(const glm::vec2 &p0,
							  const glm::vec2 &p1,
							  const glm::vec2 &p2,
							  const glm::vec2 &p3,
							  float t) {
			float u = 1 - t;
			return u*u*u * p0 +
				   3*u*u*t * p1 +
				   3*u*t*t * p2 +
				   t*t*t * p3;
		}
	
		//---------------------------------------------------------------------------
		// Helper: parse numbers from SVG path segment (handles comma or no space)
		static std::vector<float> parseNumbers(const std::string &s) {
			std::vector<float> nums;
			std::regex re("[-+]?[0-9]*\\.?[0-9]+"); // matches floats
			auto begin = std::sregex_iterator(s.begin(), s.end(), re);
			auto end = std::sregex_iterator();
			for (auto it = begin; it != end; ++it) {
				nums.push_back(std::stof(it->str()));
			}
			return nums;
		}
	
		//---------------------------------------------------------------------------
		// Parse a very simple subset of SVG path data into an ofPolyline
		static ofPolyline svgPathToPolyline(const std::string &d, int bezierResolution = 20) {
			ofPolyline poly;
		   glm::vec2 cursor(0,0);
		   glm::vec2 lastMove(0,0);

		   size_t i = 0;
		   while (i < d.size()) {
			   char cmd = d[i];
			   if (isspace(cmd)) { i++; continue; }
			   if (!isalpha(cmd)) { i++; continue; }

			   i++; // move past command
			   size_t nextCmdPos = d.find_first_of("MmLlCcZz", i);
			   std::string data = (nextCmdPos == std::string::npos) ? d.substr(i) : d.substr(i, nextCmdPos - i);
			   std::vector<float> nums = parseNumbers(data);

			   if (cmd == 'M') { cursor = glm::vec2(nums[0], nums[1]); lastMove = cursor; poly.addVertex(cursor.x, cursor.y); }
			   else if (cmd == 'm') { cursor += glm::vec2(nums[0], nums[1]); lastMove = cursor; poly.addVertex(cursor.x, cursor.y); }
			   else if (cmd == 'L') { cursor = glm::vec2(nums[0], nums[1]); poly.addVertex(cursor.x, cursor.y); }
			   else if (cmd == 'l') { cursor += glm::vec2(nums[0], nums[1]); poly.addVertex(cursor.x, cursor.y); }
			   else if (cmd == 'C') {
				   for (size_t j = 0; j + 5 < nums.size(); j+=6) {
					   glm::vec2 p0 = cursor;
					   glm::vec2 p1(nums[j], nums[j+1]);
					   glm::vec2 p2(nums[j+2], nums[j+3]);
					   glm::vec2 p3(nums[j+4], nums[j+5]);
					   for (int k=1; k<=bezierResolution; k++) {
						   float t = (float)k / (float)bezierResolution;
						   glm::vec2 pt = cubicBezier(p0,p1,p2,p3,t);
						   poly.addVertex(pt.x, pt.y);
					   }
					   cursor = p3;
				   }
			   }
			   else if (cmd == 'c') {
				   for (size_t j = 0; j + 5 < nums.size(); j+=6) {
					   glm::vec2 p0 = cursor;
					   glm::vec2 p1 = cursor + glm::vec2(nums[j], nums[j+1]);
					   glm::vec2 p2 = cursor + glm::vec2(nums[j+2], nums[j+3]);
					   glm::vec2 p3 = cursor + glm::vec2(nums[j+4], nums[j+5]);
					   for (int k=1; k<=bezierResolution; k++) {
						   float t = (float)k / (float)bezierResolution;
						   glm::vec2 pt = cubicBezier(p0,p1,p2,p3,t);
						   poly.addVertex(pt.x, pt.y);
					   }
					   cursor = p3;
				   }
			   }
			   else if (cmd == 'Z' || cmd == 'z') { poly.addVertex(lastMove.x, lastMove.y); poly.close(); }

			   i = nextCmdPos;
		   }

		   return poly;
		}
	
		//---------------------------------------------------------------------------
		// Build a circle polyline centered at (cx, cy) with given radius
		static ofPolyline makePolylineCircle(float cx, float cy, float r, int resolution = 40) {
			ofPolyline poly;
			
			// Magic constant for control point offset
			float k = 0.5522847498f;
			float c = r * k;

			glm::vec2 p0(cx + r, cy);      // rightmost point
			glm::vec2 p1(cx + r, cy + c);
			glm::vec2 p2(cx + c, cy + r);
			glm::vec2 p3(cx,     cy + r);  // bottom

			glm::vec2 p4(cx - c, cy + r);
			glm::vec2 p5(cx - r, cy + c);
			glm::vec2 p6(cx - r, cy);      // left

			glm::vec2 p7(cx - r, cy - c);
			glm::vec2 p8(cx - c, cy - r);
			glm::vec2 p9(cx,     cy - r);  // top

			glm::vec2 p10(cx + c, cy - r);
			glm::vec2 p11(cx + r, cy - c);
			glm::vec2 p12(cx + r, cy);     // back to rightmost

			auto addCubic = [&](glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d) {
				glm::vec2 prev = a;
				for (int i=1; i<=resolution; i++) {
					float t = (float)i / (float)resolution;
					glm::vec2 pt = cubicBezier(a,b,c,d,t);
					poly.addVertex(pt.x, pt.y);
					prev = pt;
				}
			};

			poly.addVertex(p0.x, p0.y);
			addCubic(p0,p1,p2,p3);
			addCubic(p3,p4,p5,p6);
			addCubic(p6,p7,p8,p9);
			addCubic(p9,p10,p11,p12);

			poly.close();
			return poly;
		}

		//---------------------------------------------------------------------------
		// Sample n points evenly spaced around a polyline, starting from centroid
		static std::vector<glm::vec2> getRadialBoundaryPoints(const ofPolyline& poly, int n, float step = 2.0f, int refineSteps = 5) {
			std::vector<glm::vec2> pts;

		   if (poly.size() < 3 || n <= 0) return pts;

		   // centroid first
		   glm::vec2 centroid = poly.getCentroid2D();
		   pts.push_back(centroid);

		   float angleStep = TWO_PI / n;

		   for (int i = 0; i < n; i++) {
			   float angle = i * angleStep;
			   glm::vec2 dir(cos(angle), sin(angle));

			   glm::vec2 pos = centroid;
			   glm::vec2 lastInside = pos;
			   glm::vec2 firstOutside = pos;

			   // march outward until outside
			   while (poly.inside(glm::vec3(pos,0))) {
				   lastInside = pos;
				   pos += dir * step;
			   }
			   firstOutside = pos;

			   // refine between lastInside and firstOutside
			   for (int j = 0; j < refineSteps; j++) {
				   glm::vec2 mid = (lastInside + firstOutside) * 0.5f;
				   if (poly.inside(glm::vec3(mid, 0))) {
					   lastInside = mid;
				   } else {
					   firstOutside = mid;
				   }
			   }

			   pts.push_back(lastInside);
		   }

		   return pts;
		}

		//---------------------------------------------------------------------------
	
	}

}

#endif // bbcDrawing_h
