#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    
    ofGLFWWindowSettings settings;
    //settings.setGLVersion(3, 2); // Programmable renderer
    settings.setSize(1365,768);
    ofCreateWindow(settings);
    
	//ofSetupOpenGL(1365, 768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp() );

}
