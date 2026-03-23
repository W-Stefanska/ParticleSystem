#include "ofApp.h"
#include "ofxPanel.h"
#include <ofxGui.h>

void ofApp::setup() {
    ofSetFrameRate(60);

	scene.setup();
	manager.setup();
}

float th = 0;
void ofApp::update() {
    float dt = ofGetLastFrameTime();
    th += dt;
}

void ofApp::draw() {
	ofSetDepthTest(true);
	scene.draw();
	ofSetDepthTest(false);
    manager.draw();
    
}

void ofApp::exit() {
}