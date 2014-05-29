#include "ofApp.h"


/*
 
 TODO:
 
 * Test FrameTweener
 * Test BezierAnimator
 * Test RandomBezierAnimator
 
 */


using namespace bbc::utils;

//--------------------------------------------------------------
void ofApp::setup()  {
        
    ofSetWindowTitle("bbcUtils: dev test app");
    
    cout << "type \t\tsize \tmin \t\t\tmax" << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << "bool\t\t" << sizeof(bool) << endl;
    cout << "char\t\t" << sizeof(char) << "\t" << CHAR_MIN << "\t\t\t" << CHAR_MAX << endl;
    cout << "unsigned char\t" << sizeof(unsigned char) << "\t\t\t\t" << UCHAR_MAX << endl;
    cout << "short\t\t" << sizeof(short) << "\t" << INT_MIN << "\t\t" << INT_MAX << endl;
    cout << "int\t\t" << sizeof(int) << "\t" << INT_MIN << "\t\t" << INT_MAX << endl;
    cout << "unsigned int\t" << sizeof(unsigned int) << "\t\t\t\t" << UINT_MAX << endl;
    cout << "float\t\t" << sizeof(float) << "\t" << FLT_MIN << "\t\t" << FLT_MAX << endl;
    cout << "long\t\t" << sizeof(long) << "\t" << LONG_MIN << "\t" << LONG_MAX << endl;
    cout << "double\t\t" << sizeof(double) << "\t" << DBL_MIN << "\t\t" << DBL_MAX << endl;
    cout << "---------------------------------------------------------------" << endl;
    //------------------------------
    
    
    int c = ofHexToInt("ff0000");
    int c1 = ofHexToInt("ffff00");
    int c2 = ofHexToInt("ffffff");
    int c3 = ofHexToInt("000000");
    cout << c << " " << c1 << endl;
    
    //------------------------------
    
   // testConfig();
    
    
    // init timers.
    
	a_timer = new CheckTimer("A_TEST", 1 * 1000);
	b_timer = new CheckTimer("B_TEST", 3 * 1000);
    fa_timer = new FrameTimer(500, true);
    fb_timer = new FrameTimer(320);
    
    frame_tweener.start(600);
    
    ofVec2f start_pos = ofVec2f(200,200);
    ofVec2f end_pos = ofVec2f(ofGetWidth()-200,  ofGetHeight()-200);
    
    //bezier_animator_a.start(start_pos.x, start_pos.y, start_pos.x-50,start_pos.y+50, end_pos.x+50,end_pos.y-50, end_pos.x, end_pos.y, 400);
    bezier_animator_a.start(start_pos, start_pos+300, end_pos-300, end_pos, 500);
    bezier_animator_a.use_ease = true;
    
    
    rand_bezier_animator.setup(10,10,ofGetWidth()-20, ofGetHeight()-20);
    rand_bezier_animator.repeating = true;
    rand_bezier_animator.use_ease = false;
    rand_bezier_animator.start();
   
    int n = INT_MAX;
    int o = INT_MIN;
    
    cout << "int_max=" << n << ", int_min=" << o << endl;
    cout << ++n << ", " << --o << endl;
    
}

void ofApp::testConfig() {

    string s = Config::instance()->getAttribute("config:colors:palette", "values", "empty");
    cout << s << endl;
    
    //string s2 = Config::instance()->getValue("config:colors", "empty");
    //cout << s2 << endl;
    
    bool mpe_enabled = Config::instance()->getAttribute("config:mpereadwillfail", "enabled", 1);
    cout << mpe_enabled << endl;
    
   // printf("mpe_enabled=%i=%i\n",mpe_enabled,12);
    
    mpe_enabled = Config::instance()->getAttribute("config:mpe", "enabled", 1);
    cout << mpe_enabled << endl;
    
    //string xml_str = Config::instance()->getXMLString("config:colors");
    //cout << "'" << xml_str << "'" << endl;
    
   string xml_str;
   TiXmlElement* elem = Config::instance()->getNode("config:colors"); // render_mode
    
   // ofXml xml;
    ofxXmlSettings xmls;
    
    if(elem) {
        //cout << "'" << Config::instance()->makeString(elem) << "'"  << endl;
        int i = 0;
        for (const TiXmlNode* node=elem->FirstChild(); node; node=node->NextSibling(), i++){
            if(Config::instance()->isComment(node)) {
            //if(node->Type() == TiXmlNode::COMMENT){
                cout << "This ones a Comment!" << endl << endl;
            }else{
                Config::instance()->copyToString(node, xml_str);
                
          //      cout << "\t" << xml_str << endl;
             //   xml.loadFromBuffer(xml_str); // convert to ofXML
              //  cout << endl << xml.toString() << endl;
                
                xmls.loadFromBuffer(xml_str);
                // now walk the ofXMLSetings node too.
                
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
    
    cout << i << " parsed." << endl;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    fa_timer->update();
    fb_timer->update();
    
    frame_tweener.update();
    bezier_animator_a.update();
    rand_bezier_animator.update();
    
   /* float seed = sin((float)ofGetFrameNum());
    float seed2 = ofGetElapsedTimeMicros()/10000;
    
    cout << " " << ofNoise(seed, seed2) << " "; // << seed <<  " = "*/
    
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(ofColor::lightGray, ofColor::darkGray);
    
    //ofBackgroundHex(0xAAAAAA);
    
    ofSetColor(255);
    
    testEasing();
    
    testTimers();
    
    testAnimators();
}

void ofApp::testAnimators() {
    
    
    ofSetColor(255,0, 255);
    ofDrawBitmapString(frame_tweener.toString(), 350, 15);
    
    ofDrawBitmapString(bezier_animator_a.toString(), 350, 30);
    
    ofDrawBitmapString(rand_bezier_animator.toString(), 350, 45);
    
    bezier_animator_a.drawDebug(128);
    
    if(bezier_animator_a.isComplete()) {
        bezier_animator_a.repeat();
    }
    
    rand_bezier_animator.drawDebug();
    
}


void ofApp::testTimers(){
    
    if(a_timer->isExpired()) {
        ofSetColor(255, 0, 255);
        ofCircle(30, 60, 10);
        a_timer->reset();
    }
       
    if(b_timer->isExpired()) {
        ofSetColor(255, 0, 0);
        ofCircle(30, 90, 10);
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
    ofDrawBitmapString(fa_timer->toString(), 10, 20);
    ofSetColor(0,255,255);
    ofDrawBitmapString(fb_timer->toString(), 10, 36);    

}


void ofApp::testEasing() {
    
    // Test Easing.
    fa += 0.0025;
    fa = fa > 1.0 ? 0.0 : fa;
    
    fb += 0.0025;
    fb = fb > 1.0 ? 0.0 : fb;
    
    fc += 0.0025;
    fc = fc > 1.0 ? 0.0 : fc;
    
    // Back Bounce Circ Cubic Elastic Expo Linear Quad Quart Quint Sine
    
    ofSetColor(255,255,0);
    ofCircle( 20, ErpEase::sineIn(0, ofGetHeight(), fa), 10);
    
    ofSetColor(0,255,255);
    ofCircle( 40, ErpEase::sineOut(0, ofGetHeight(), fb), 10);
    
    ofSetColor(255,0,255);
    ofCircle( 60, ErpEase::sineInOut(0, ofGetHeight(), fc), 10);
    
    ofSetColor(255,255,0);
    ofCircle( 80, ErpEase::elasticIn(0, ofGetHeight(), fa), 10);
    
    ofSetColor(0,255,255);
    ofCircle( 100, ErpEase::elasticOut(0, ofGetHeight(), fb), 10);
    
    ofSetColor(255,0,255);
    ofCircle( 120, ErpEase::elasticInOut(0, ofGetHeight(), fc), 10);
    
    ofSetColor(255,255,0);
    ofCircle( 140, ErpEase::bounceIn(0, ofGetHeight(), fa), 10);
    
    ofSetColor(0,255,255);
    ofCircle( 160, ErpEase::bounceOut(0, ofGetHeight(), fb), 10);
    
    ofSetColor(255,0,255);
    ofCircle( 180, ErpEase::bounceInOut(0, ofGetHeight(), fc), 10);
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