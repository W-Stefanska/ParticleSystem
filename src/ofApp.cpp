#include "ofApp.h"
#include "ofxPanel.h"
#include <ofxGui.h>

std::unique_ptr<Collider> col = std::make_unique<SphereCollider>();

void ofApp::setup() {
    ofSetFrameRate(60);

	scene.setup();
	manager.setup(colliders, emitters);

	
}

float th = 0;
void ofApp::update() {
    float dt = ofGetLastFrameTime();
    th += dt;
}

void ofApp::draw() {
	scene.begin();
	col->draw();
	scene.end();
    manager.draw();
    
}

void ofApp::exit() {
}