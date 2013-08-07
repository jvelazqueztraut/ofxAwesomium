#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	web.setup(ofGetWidth(),ofGetHeight());

	web.loadURL("http://www.google.com/");
	web.focus();

}

//--------------------------------------------------------------
void testApp::update(){
	web.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	web.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	web.keyPressed(key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	web.mouseMoved(x,y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	web.mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	web.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	web.mouseReleased(x,y,button);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}