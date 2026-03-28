#include "ofApp.h"
#include "ofxPanel.h"
#include <ofxGui.h>


void ofApp::setup() {
    ofSetFrameRate(60);

	scene.setup();
	manager.setup(colliders, emitters);

	
}

float th = 0;
void ofApp::update() {
	if (ImGui::GetIO().WantCaptureMouse) {
		scene.getCamera()->disableMouseInput();
	}
	else {
		scene.getCamera()->enableMouseInput();
	}
    float dt = ofGetLastFrameTime();
    th += dt;
}

void ofApp::draw() {
	scene.begin();
	for each(auto &collider in colliders) {
		collider->draw();
	}
	for each(auto &emitter in emitters) {
		emitter->draw();
	}
	scene.end();
    manager.draw();
    
}

void ofApp::exit() {
}