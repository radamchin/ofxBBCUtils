#include "ofApp.h"

using namespace bbc::utils;

//--------------------------------------------------------------

ofApp::ofApp():iApp("BBC_UTILS_DEV_TEST", BBC_UTILS_DEV_VERSION, false) {
    // How to pass configurable values into iApp, not great.
}

void ofApp::setup()  {        
    ofSetWindowTitle("bbcUtils: dev test app");
    
    testConfig();
    
    // init timers.
    fa = fb = fc = 0;

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
    
    fps_tracker.setup();

}

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
    
    mpe_enabled = CONFIG_GET("mpe", "enabled", 1); //Config::instance()->getAttribute("config:mpe", "enabled", 1);
    cout << "mpe_enabled=" << mpe_enabled << endl;
    
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
    
    if(ofGetFrameNum() % 60 == 0) fps_tracker.mark(); // add a line to mark second of time.
        
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(ofColor::lightGray, ofColor::darkGray);
    //ofBackgroundHex(0xAAAAAA);
    
    drawCalibration(192);
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate(), 2) + ", " + getUpTimeStr() + ", " + getUnixTimeStamp(true), 5, 15);
    
    ofSetColor(255);
    
    fps_tracker.draw(5, 100);
    
    testEasing();
    
    testTimers();
    
    testAnimators();
    
    testClipboard();
    
}

void ofApp::testClipboard() {
    
    // get whats in the clipboard and draw it to screen?
    
    string clip_str = "CLIPBOARD = '" + getClipboard() + "'";
    
    ofSetColor(0);
    ofDrawBitmapString(clip_str, 4, ofGetHeight()-35);
    
    ofSetColor(255);
    ofDrawBitmapString(clip_str, 3, ofGetHeight()-36);
    
}

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
    ofDrawBitmapString(fa_timer->toString(), 10, 35);
    
    ofSetColor(0,255,255);
    ofDrawBitmapString(fb_timer->toString(), 10, 50);

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