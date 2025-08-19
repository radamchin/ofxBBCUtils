#include "ofApp.h"

//using namespace bbc::utils;

#include "ErpEase.h"

//--------------------------------------------------------------
ofApp::ofApp():iApp("BBC_UTILS_DEV_TEST", BBC_UTILS_DEV_VERSION, false) {
    // How to pass configurable values into iApp, very not great.
    
}

//--------------------------------------------------------------
void ofApp::setup()  {        
    ofSetWindowTitle("bbcUtils: dev test app");
    
    testOfParamSerialiser();
    
    testConfig();
    
    // init timers.
   
	a_timer = new CheckTimer("A_TEST", 1 * 1000);
	b_timer = new CheckTimer("B_TEST", 3 * 1000);
    fa_timer = new FrameTimer(500, true);
    fb_timer = new FrameTimer(320);
    
    frame_tweener.start(600);
    
    ofPoint start_pos = ofPoint(200,200);
    ofPoint end_pos = ofPoint(ofGetWidth()-200,  ofGetHeight()-200);
    
    //bezier_animator_a.start(start_pos.x, start_pos.y, start_pos.x-50,start_pos.y+50, end_pos.x+50,end_pos.y-50, end_pos.x, end_pos.y, 400);
    ofPoint start_cntrl = start_pos+300;
    ofPoint end_cntrl = end_pos-300;
    
    bezier_animator_a.start(start_pos,  start_cntrl, end_cntrl, end_pos, 500);
    bezier_animator_a.use_ease = true;
    
    rand_bezier_animator.setup(10,10,ofGetWidth()-20, ofGetHeight()-20);
    rand_bezier_animator.repeating = true;
    // rand_bezier_animator.use_ease = true;
    rand_bezier_animator.setEase(true);
    rand_bezier_animator.setEaseKind(EaseKind::BounceOut);
    rand_bezier_animator.start();
    
	cout << "\tGL: " << bbc::utils::getGLInfoStringMin();
	//bbc::utils::printGLStats();
	//ofLogNotice("GL should have printed above here");
    
    fps_tracker.bgCol = ofColor(192,192,192,212);
    fps_tracker.setup();
    
    // Ease function pointers
    testEaseFunc = ErpEase::getEaseFunctionPointer(EaseKind::CircInOut);
    
    
    sineOscillator.setup("Sine", 0.005).setEnabled( true );
    sinePlotter.setup(24,48);
    
    sawOscillator.setup("Saw", 0.005).setType( bbc::utils::OSC_TYPE_SAW ).setEnabled( true );
    sawPlotter.setup(24,48);
    
    // Square, is a binary / blinking vibe
    squareOscillator.setup("Square", 0.005).setType( bbc::utils::OSC_TYPE_SQUARE ).setEnabled( true );
    squarePlotter.setup(24,48);
    
    // Randomesque but uses perlin noise.
    noiseOscillator.setup("Noise", 0.005).setType( bbc::utils::OSC_TYPE_NOISE ).setEnabled( true );
    noisePlotter.setup(24,48);
    
    noise2Oscillator.setup("Noise2", 0.005).setType( bbc::utils::OSC_TYPE_NOISE2 ).setEnabled( true );
    noise2Plotter.setup(24,48);
    
    
}

//--------------------------------------------------------------
void ofApp::testConfig() {

    //string s = Config::instance()->getAttribute("config:colors:palette", "values", "empty");
    string s = CONFIG_GET("colors:palette", "values", "empty0");
    cout << s << endl;
    
    string s2 = CONFIG_GET_FROM_INDEX("colors:palette", "values", "empty1", 1);
    cout << s2 << endl;
    
    string  i2 = CONFIG_GET_FROM_INDEX("colors:palette", "id", "empty2", 1);
    cout << i2 << endl;
    
    string s3 = CONFIG_GET_FROM_INDEX("colors:palette", "values", "empty3", 2);
    cout << s3 << endl;
    
    bool mpe_enabled = Config::instance()->getAttribute("config:mpereadwillfail", "enabled", 1);
    cout << mpe_enabled << endl;
    
   // printf("mpe_enabled=%i=%i\n",mpe_enabled,12);
    
    mpe_enabled = Config::instance()->getAttribute("config:mpe", "enabled", 1);
    cout << mpe_enabled << endl;
    
    //string xml_str = Config::instance()->getXMLString("config:colors");
    //cout << "'" << xml_str << "'" << endl;
    
    string xml_str;
    TiXmlElement* elem = Config::instance()->getNode("config:colors");
    
    ofxXmlSettings xmls;
    
    if(elem) {
        //cout << "'" << Config::instance()->makeString(elem) << "'"  << endl;
        int i = 0;
        for (const TiXmlNode* node=elem->FirstChild(); node; node=node->NextSibling(), i++){
            if(Config::instance()->isComment(node)) {
                cout << "This ones a Comment!" << endl << endl;
            }else{
                Config::instance()->copyToString(node, xml_str);
                //  cout << "\t" << xml_str << endl;
                //  xml.loadFromBuffer(xml_str); // convert to ofXML
                //  cout << endl << xml.toString() << endl;
                
                xmls.loadFromBuffer(xml_str);
                
                cout << "mode:" << i << " " << Config::instance()->makeString(&xmls) << endl;
            }
        }
        
    }else{
        cout << "No node found" << endl;
    }
    
    //ofxXmlSettings *cols_xml = bbc::utils::Config::instance()->getXMLSettingsNode("config:colors");
    //cout << "Found:" << endl << Config::instance()->makeString(cols_xml) << endl;
    
    ofXml *cols_xml = bbc::utils::Config::instance()->getXMLNode("config:colors");
    cout << "Found:" << endl << cols_xml->toString() << endl;
    
    /* TODO: fix as remmed for 0.10 port as throwing errors
    cols_xml->setToChild(0); // set it to the first one.
    bool sibling_found = 1;
    int i = 0;
    while(sibling_found) {
        if(cols_xml->getName() == "palette") {
            string id = cols_xml->getAttribute("[@id]");
            cout << i << ",<" << cols_xml->getName() << ">:#" << id << ", '" << cols_xml->getAttribute("[@values]") << "'" << endl;
            i++;
        }
        sibling_found = cols_xml->setToSibling();
    }
    
    cout << i << " parsed." << endl;*/

}

void ofApp::testOfParamSerialiser(){
    
    ofParameterGroup mirrorGroup;
    ofParameter<bool> doMirror{"Enabled", false};
    ofParameter<int> columns{"Columns", 1, 0, 16};
    ofParameter<float> rows{"Rows", 10.0, 0.0, 16.0};
    ofParameter<ofColor> color{"Color", ofColor::red };
   
    mirrorGroup.setName("Mirror");
    mirrorGroup.add( doMirror );
    mirrorGroup.add( columns );
    mirrorGroup.add( rows );
    mirrorGroup.add( color );
    
    ofParameterGroup otherGroup;
    ofParameter<ofPoint> pos{"Position", ofPoint(-1,0.3,PI)};
    ofParameter<ofRectangle> rect{"Rectem", ofRectangle(5,6,249,480)};
    ofParameter<void> testBut{"Button"};
    
    otherGroup.setName("Other one");
    otherGroup.add(pos);
    otherGroup.add(rect);
    
    ofParameter<string> title{"Title", "The fellowship of the ring"};
    
    ofParameterSerialiser serialiser;
    serialiser.setName("Testbed");
    
    serialiser.addGroup(mirrorGroup);
    serialiser.addParameter(title);
    serialiser.addParameter(testBut);
    serialiser.addGroup(otherGroup);
    
    // Now the serialiser is loaded we can recall it from disk?
    
   // serialiser.saveToFile("param_serialisation.xml");
  //  serialiser.saveToFile("param_serialisation.json");
    
    serialiser.loadFromFile("param_serialisation.xml");
    
    ofLogNotice("Pos") << pos;
    
}
//--------------------------------------------------------------
void ofApp::update(){
    
    fa_timer->update();
    fb_timer->update();
    
    frame_tweener.update();
    bezier_animator_a.update();
    rand_bezier_animator.update();
    
    if(ofGetFrameNum() % 60 == 0) fps_tracker.mark(); // add a line to mark second of time.
        
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //ofBackgroundGradient(ofColor::lightGray, ofColor::darkGray);
	
	drawBackgroundGrid(24.0f, ofColor(32), ofColor(64));
	
    //ofBackgroundHex(0xAAAAAA);
    
	//    drawCalibration(192, ofColor::white, 4);
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate(), 2) + ", " + getUpTimeStr() + ", " + getUnixTimeStamp(true), 5, 15);
    
    ofSetColor(255);
    
    fps_tracker.draw(5, 100);
    
	testEasing();
    
 //   testTimers();
    
//    testAnimators();
    
	//   testOscillators();
    
  //  testClipboard();
  
    
    // Test smaller utils
    
  /*  ofVec2f ta(100,100);
    ofVec2f tb(600,600);
    
    ofVec2f a = bbc::utils::getPointOnLine(ta, tb, 0.2 );
    ofVec2f b = bbc::utils::getPointOnLine(ta, tb, 0.9 );
    
    ofSetLineWidth(10);
    ofSetColor(ofColor::antiqueWhite, 192);
    ofDrawLine( ta, tb );
    
    ofSetLineWidth(5);
    ofSetColor(ofColor::darkGoldenRod, 192);
    ofDrawLine( a, b );
    
    ofSetColor(ofColor::limeGreen, 192);
	bbc::utils::drawOffsetLine(ta, tb, .33, .33, 8);*/
    
}

//--------------------------------------------------------------
void ofApp::testClipboard() {
    
    // get whats in the clipboard and draw it to screen?
    
    string clip_str = "CLIPBOARD = '" + getClipboard() + "'";
    
    ofSetColor(0);
    ofDrawBitmapString(clip_str, 4, ofGetHeight()-35);
    
    ofSetColor(255);
    ofDrawBitmapString(clip_str, 3, ofGetHeight()-36);
    
}

//--------------------------------------------------------------
void ofApp::testAnimators() {
    
    ofSetColor(255,0, 255);
    ofDrawBitmapString(frame_tweener.toString(), 350, 25);
    
    ofSetColor(255,0, 192);
    ofDrawBitmapString(bezier_animator_a.toString(), 350, 40);
        
    ofSetColor(255,0, 128);
    ofDrawBitmapString(rand_bezier_animator.toString(), 350, 55);
    
    bezier_animator_a.drawDebug(128);
    
    if(bezier_animator_a.isComplete()) {
        bezier_animator_a.repeat();
    }
    
    rand_bezier_animator.drawDebug();
    
}


//--------------------------------------------------------------
void ofApp::testTimers(){
    
    if(a_timer->isExpired()) {
        ofSetColor(255, 0, 255);
        ofDrawCircle(30, 60, 10);
        a_timer->reset();
    }
       
    if(b_timer->isExpired()) {
        ofSetColor(255, 0, 0);
        ofDrawCircle(30, 90, 10);
        b_timer->reset();
    }
    
    ofSetColor(255);
    ofDrawBitmapString(a_timer->toString(), 15, 65);
    ofDrawBitmapString(b_timer->toString(), 15, 80);
    
    
    if(fa_timer->isExpired()) {
        
    }
    
    if(fb_timer->isExpired()) {
        
    }
    
    ofSetColor(0);
    ofDrawBitmapString(fa_timer->toString(), 10, 35);
    
    ofSetColor(0,255,255);
    ofDrawBitmapString(fb_timer->toString(), 10, 50);

}

//--------------------------------------------------------------
void ofApp::testEasing() {
    
    // Test Easing.
	ease_vals.increment(0.002);
	
	// TODO: could draw a line for every path, but with a dot (small circ) at every 5% along?? to show what the plot looks like in a 2 dims
    
    // Back Bounce Circ Cubic Elastic Expo Linear Quad Quart Quint Sine
	int yanchor = ofGetHeight() - 26;
	int x = 20;
	int x_step = 24;
	int crad = 8;
	int xpad = 4;
	int start_y = crad;
	int end_y = ofGetHeight()-crad;
	int angle = -90;
	
	ofColor bg_col(0,0,0);
	ofColor col(255,255,0);
	
	// Log current value
	ofDrawBitmapStringHighlight( "EaseVal.a = " + ofToString(ease_vals.a), 14, ofGetHeight() - 6);
	
	drawRotatedBitmapStringHighlight( "sineIn", x+xpad, yanchor, angle, bg_col, col );
    ofSetColor(col);
	ofDrawCircle( x, ErpEase::sineIn(start_y, end_y, ease_vals.a), crad);
    
	x+=x_step;
	col.set(0,255,255);
	drawRotatedBitmapStringHighlight( "sineOut", x+xpad, yanchor, angle, bg_col, col );
    ofSetColor(col);
    ofDrawCircle( x, ErpEase::sineOut(start_y, end_y, ease_vals.b), crad);
	
	x+=x_step;
	col.set(255,0,255);
	drawRotatedBitmapStringHighlight( "sineInOut", x+xpad, yanchor, angle, bg_col, col );
    ofSetColor(col);
    ofDrawCircle( x, ErpEase::sineInOut(start_y, end_y, ease_vals.c), crad);
    
	
	x+=x_step;
	col.set(255,255,0);
	drawRotatedBitmapStringHighlight( "elasticIn", x+xpad, yanchor, angle, bg_col, col );
    ofSetColor(col);
    ofDrawCircle( x, ErpEase::elasticIn(start_y, end_y, ease_vals.a), crad);
	
	x+=x_step;
	col.set(0,255,255);
	drawRotatedBitmapStringHighlight( "elasticOut", x+xpad, yanchor, angle, bg_col, col );
    ofSetColor(col);
    ofDrawCircle( x, ErpEase::elasticOut(start_y, end_y, ease_vals.b), crad);
    
	x+=x_step;
	col.set(255,0,255);
	drawRotatedBitmapStringHighlight( "elasticInOut", x+xpad, yanchor, angle, bg_col, col );
    ofSetColor(col);
    ofDrawCircle( x, ErpEase::elasticInOut(start_y, end_y, ease_vals.c), crad);
    

	x+=x_step;
	col.set(255,255,0);
	drawRotatedBitmapStringHighlight( "bounceIn", x+xpad, yanchor, angle, bg_col, col );
    ofSetColor(col);
    ofDrawCircle( x, ErpEase::bounceIn(start_y, end_y, ease_vals.a), crad);
	
	x+=x_step;
	col.set(0,255,255);
	drawRotatedBitmapStringHighlight( "bounceOut", x+xpad, yanchor, angle, bg_col, col );
    ofSetColor(col);
    ofDrawCircle( x, ErpEase::bounceOut(start_y, end_y, ease_vals.b), crad);
    
	x+=x_step;
	col.set(255,0,255);
	drawRotatedBitmapStringHighlight( "bounceInOut", x+xpad, yanchor, angle, bg_col, col );
    ofSetColor(col);
    ofDrawCircle( x, ErpEase::bounceInOut(start_y, end_y, ease_vals.c), crad);
    
	
	x+=x_step;
	col.set(128,0,255);
	drawRotatedBitmapStringHighlight( "expoInOut", x+xpad, yanchor, angle, bg_col, col );
	ofSetColor(col);
	ofDrawCircle( x, ErpEase::expoInOut(start_y, end_y, ease_vals.c), crad);
	
	
	x+=x_step;
	col.set(ofColor::limeGreen);
	drawRotatedBitmapStringHighlight( "linearInOut", x+xpad, yanchor, angle, bg_col, col );
	ofSetColor(col);
	ofDrawCircle( x, ErpEase::linearInOut(start_y, end_y, ease_vals.c), crad);
	
	
    // Special ease lookup by type
	x+=x_step;
	col.set(ofColor::pink);
	drawRotatedBitmapStringHighlight( "QuadInOut", x+xpad, yanchor, angle, bg_col, col );
    ofSetColor(col);
    ofDrawCircle( x, ErpEase::easeByKind(EaseKind::QuadInOut, start_y, end_y, ease_vals.c), crad);
	
	
	x+=x_step;
	col.set(ofColor::darkOrange);
	drawRotatedBitmapStringHighlight( "QuartInOut", x+xpad, yanchor, angle, bg_col, col );
	ofSetColor(col);
	ofDrawCircle( x, ErpEase::easeByKind(EaseKind::QuartInOut, start_y, end_y, ease_vals.c), crad);
	
	x+=x_step;
	col.set(ofColor::orange);
	drawRotatedBitmapStringHighlight( "QuintInOut", x+xpad, yanchor, angle, bg_col, col );
    ofSetColor(col);
    ofDrawCircle( x, ErpEase::easeByKind(EaseKind::QuintInOut, start_y, end_y, ease_vals.c), crad);
	
	x+=x_step;
	col.set(ofColor::lemonChiffon);
	drawRotatedBitmapStringHighlight( "BackInOut", x+xpad, yanchor, angle, bg_col, col );
	ofSetColor(col);
	ofDrawCircle( x, ErpEase::easeByKind(EaseKind::BackInOut, start_y, end_y, ease_vals.c), crad);
	
	x+=x_step;
	col.set(ofColor::wheat);
    // Test easeFunc pointer
	drawRotatedBitmapStringHighlight( "CircInOut", x+xpad, yanchor, angle, bg_col, col );
    ofSetColor(col);
    ofDrawCircle( x, testEaseFunc(start_y, end_y, ease_vals.c), crad);
	
	// SloMos
	x+=x_step;
	col.set(ofColor::chocolate);
	drawRotatedBitmapStringHighlight( "SloMo Ex.1", x+xpad, yanchor, angle, bg_col, col );
	ofSetColor(col);
	ofDrawCircle( x, ErpEase::slowMo(start_y, end_y, ease_vals.c, 0.005, 0.7), crad);
	
	x+=x_step;
	col.set(ofColor::cadetBlue);
	drawRotatedBitmapStringHighlight( "SloMo Ex.2", x+xpad, yanchor, angle, bg_col, col );
	ofSetColor(col);
	ofDrawCircle( x, ErpEase::slowMo(start_y, end_y, ease_vals.c, 0.1, 0.4), crad);
		
	// slowMo(float start, float stop, float amt, float linear_ratio = 0.05, float power = 0.5)
	// linear_ratio: smaller this the smoother / slower the ins and outs  0.05; // 0.7;
	// power: higher this the flatter the slomo middle0.5; // 0.7;
	   
	// Stepped ease
	x+=x_step;
	col.set(ofColor::rosyBrown);
	drawRotatedBitmapStringHighlight( "Stepped Ex.1", x+xpad, yanchor, angle, bg_col, col );
	ofSetColor(col);
	ofDrawCircle( x, ErpEase::stepped(start_y, end_y, ease_vals.c, 4), crad); // 32
	
	x+=x_step;
	col.set(ofColor::coral);
	drawRotatedBitmapStringHighlight( "Stepped Ex.2", x+xpad, yanchor, angle, bg_col, col );
	ofSetColor(col);
	ofDrawCircle( x, ErpEase::stepped(start_y, end_y, ease_vals.c, 12), crad); // 12
	
	x+=x_step;
	col.set(ofColor::mediumPurple);
	drawRotatedBitmapStringHighlight( "Stepped Ex.3", x+xpad, yanchor, angle, bg_col, col );
	ofSetColor(col);
	ofDrawCircle( x, ErpEase::stepped(start_y, end_y, ease_vals.c, 24), crad);
	
}

//--------------------------------------------------------------
void ofApp::testOscillators() {
        
    ofPushStyle();
    ofPushMatrix();
    
    float MAX_R = 60; // how big our circle is that shows this value.
    
    int DW = 320+(MAX_R*4.5);
    int DH = 180;
    int PADX = 50;
    int PADY = 50;
        
    ofTranslate( PADX, ofGetHeight()-DH-PADY ); //  ofGetWidth()-DW-
    
    // draw bg box
    ofSetColor(ofColor::white, 64);
    ofFill();
    ofDrawRectangle(0, 0, DW, DH);
    
    ofDrawBitmapStringHighlight( "Oscillators:", 5, -10);
    
    
    float dx = 1 * MAX_R;
    float dy = DH * .5;
    
    float v = sineOscillator.update();
    sinePlotter.add(v);
    
    float r = MAX_R * v;
    ofSetColor(ofColor::pink, 192);
    ofDrawCircle( dx, dy, r ); // d*.5, DH*.5
    ofDrawBitmapStringHighlight( "Sine", dx, DH * .75);
    //ofDrawBitmapStringHighlight(sineOscillator.toString(), 5, DH * .25);
    sinePlotter.draw(dx-sinePlotter.getWidth()/2); // 0, 0); // DH-sinePlotter.getHeight());
    
    
    v = sawOscillator.update();
    sawPlotter.add(v);
    
    r = MAX_R * v;
    ofSetColor(ofColor::lemonChiffon, 192);
    dx += MAX_R * 2;
    ofDrawCircle( dx, dy, r );
    ofDrawBitmapStringHighlight( "Saw", dx, DH * .75);
    //ofDrawBitmapStringHighlight(sawOscillator.toString(), 5, DH * .66);
    sawPlotter.draw(dx-sawPlotter.getWidth()/2); // 0, 0); // DH-sinePlotter.getHeight());
    
    
    v = squareOscillator.update();
    squarePlotter.add(v);
    r = MAX_R * v;
    ofSetColor(ofColor::cadetBlue, 192);
    dx += MAX_R * 2;
    ofDrawCircle( dx, dy, r );
    ofDrawBitmapStringHighlight( "Square", dx, DH * .75);
    //ofDrawBitmapStringHighlight(squareOscillator.toString(), 5, DH * .85);
    squarePlotter.draw(dx-squarePlotter.getWidth()/2);
    
    
    v = noiseOscillator.update();
    noisePlotter.add(v);
    r = MAX_R * v;
    ofSetColor(ofColor::seaGreen, 192);
    dx += MAX_R * 2;
    ofDrawCircle( dx, dy, r );
    ofDrawBitmapStringHighlight( "Noise", dx, DH * .75);
    //ofDrawBitmapStringHighlight(noiseOscillator.toString(), 5, DH * 1);
    noisePlotter.draw(dx-noisePlotter.getWidth()/2);
    
    
    v = noise2Oscillator.update();
    noise2Plotter.add(v);
    r = MAX_R * v;
    ofSetColor(ofColor::gold, 192);
    dx += MAX_R * 2;
    ofDrawCircle( dx, dy, r );
    ofDrawBitmapStringHighlight( "Noise2", dx, DH * .75);
    //ofDrawBitmapStringHighlight(noise2Oscillator.toString(), 5, DH * 1);
    noise2Plotter.draw(dx-noise2Plotter.getWidth()/2);
    
    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
