
/*
 
 Drawing
 
 Drawing helpers and utils.
 
 Adam Hinshaw 2025
 
 
 */

#ifndef bbcDrawing_h
#define bbcDrawing_h

#include "ofMain.h"

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
    }
    
}

#endif // bbcDrawing_h
