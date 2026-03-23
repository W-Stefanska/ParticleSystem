#include "ofApp.h"
#include "ofxPanel.h"
#include <ofxGui.h>

// SIATKA
static void grid(float size, int steps) {
    ofSetColor(200);
    for (int i = -steps; i <= steps; i++) {
        ofDrawLine(-size * steps, 0, i * size, size * steps, 0, i * size);
        ofDrawLine(i * size, 0, -size * steps, i * size, 0, size * steps);
    }
}

void ofApp::setup() {
    ofSetFrameRate(60);
    bg.aliceBlue;

    // USTAW KAMERE
    cam.setNearClip(0.1f);
    cam.setFarClip(10000.0f);
    cam.setPosition(0, 0, 1000);
    cam.lookAt(ofVec3f(0, 0, 0));
    
    // USTAW SWIATLO
    light.setPosition(cam.getPosition() + ofVec3f(200, 200, 200));
    light.setDiffuseColor(ofColor(255, 200, 100));
    light.setSpecularColor(ofColor(255, 200, 100));
	light.setAmbientColor(ofColor(50, 50, 200));
    ofSetSmoothLighting(true);
}

float th = 0;
void ofApp::update() {
    float dt = ofGetLastFrameTime();
    th += dt;
}

void ofApp::draw() {
    ofBackground(bg);
    cam.begin();
    ofEnableDepthTest();
    light.enable();
    grid(40, 50);
    
    light.disable();
    ofDisableDepthTest();
    cam.end();
}

void ofApp::exit() {
}