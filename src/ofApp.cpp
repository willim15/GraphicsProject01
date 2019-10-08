#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	beat.loadSound("frame.mp3");
	fftSmooth = new float[8192];
	for (int i = 0; i < 8192; i++) {
		fftSmooth[i] = 0;
	}

	bands = 80;
	beat.setLoop(true);
	beat.setVolume(.2);
	

	play.addListener(this, &ofApp::playPressed);
	play.addListener(this, &ofApp::stopPressed);

	ofEnableSmoothing();
	gui.setup();
	gui.add(play.setup("PRESS 1 TO PLAY"));
	gui.add(stop.setup("PRESS 2 TO STOP"));

	
	gui.add(color.setup("COLOR", ofColor(255, 255, 255, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255)));
	gui.add(background.setup("background", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(255, 255, 255)));
	gui.add(size.setup("WIDTH", 3, 1, 8));
	gui.add(btnClear.setup("clear"));

	fbo.allocate(width, height);
	fbo.begin();
	ofClear(255);
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::update() {
	ofBackground(background->x, background->y, background->z);
	float * value = ofSoundGetSpectrum(bands);
	for (int i = 0; i < bands; i++) {
		fftSmooth[i] *= .9f;
		if (fftSmooth[i] < value[i]) {
			fftSmooth[i] = value[i];
		}

	}

	if (btnClear) {
		fbo.begin();
		ofClear(255);
		fbo.end();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	//fbo.draw(0, 0);
	ofNoFill();
	for (int i = 0; i < bands; i++) {
		fbo.draw(-(fftSmooth[i] * 150), -(fftSmooth[i] * 150));
		//ofCircle(ofGetWidth() / 2, ofGetHeight() / 2, -(fftSmooth[i] * 150));
	}
	ofDrawRectangle(0, 0, width, height);
	gui.draw();
}


void ofApp::playPressed() {
	beat.play();
}
void ofApp::stopPressed() {
	beat.stop();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		imgScreenshot.grabScreen(0, 0, fbo.getWidth(), fbo.getHeight());
		string filename = "screenshot_" + ofToString(count, 3, '0') + ".png";
		imgScreenshot.save(filename);
		count++;
	}
	switch (key) {
		case '1':
			beat.play();
			break;
		case '2':
			beat.stop();
		break;


	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	fbo.begin();
	ofSetLineWidth(size);
	ofSetColor(color);
	polyline.addVertex(ofPoint(x, y));
	polyline.draw();
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	fbo.begin();
	polyline.clear();
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}