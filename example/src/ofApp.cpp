#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

	if (screenCap.isButtonPressed(VK_LBUTTON)) {
		HWND hWnd = screenCap.getSelectedWindow();
		if (hWnd != NULL) {
			screenCap.capture(hWnd);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(ofColor::white);
    ofDrawBitmapString("press ' ' to capture Desktop.", 20, 30);
    ofDrawBitmapString("left click to capture a window.", 20, 50);

	if (screenCap.captureImage.isAllocated()) {
		screenCap.captureImage.draw(0, 0, 600, 400);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch(key) {
	case ' ':
		screenCap.capture();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
