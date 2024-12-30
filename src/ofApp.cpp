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

    ml.addListener(this, &ofApp::mlChanged);
    mL.addListener(this, &ofApp::mLChanged);

    ofSetColor(255);
    gui.setup();
    gui.add(pS.setup("Size", 10, 1, 100));
    gui.add(vS.setup("Size variation", 2, 0, 100));
    gui.add(ml.setup("Minimal lifetime", 100, 1, 150));
    gui.add(mL.setup("Maximal lifetime", 200, 150, 1000));
    gui.add(pColor.setup("Color", ofColor(255, 0, 0), ofColor(0, 0, 0), ofColor(255, 255, 255), 200, 20));
    gui.add(up.setup("Up / Down"));

    // USTAW KAMERE
    cam.setNearClip(0.1f);
    cam.setFarClip(10000.0f);
    cam.setPosition(0, 0, 1000);
    cam.lookAt(ofVec3f(0, 0, 0));

    // USTAW EMITER
    emitter1.setup(100);
    emitter1.position.set(0, 300, 0);
    
    // USTAW SWIATLO
    light.setPosition(cam.getPosition() + ofVec3f(0, 0, 20));
    light.setDiffuseColor(ofColor(255, 255, 255));
    light.setSpecularColor(ofColor(255, 255, 255));
    ofSetSmoothLighting(true);
    

}

void ofApp::mlChanged(int& x) { mL.setMin(x); }
void ofApp::mLChanged(int& x) { ml.setMax(x); }

float th = 0;
void ofApp::update() {
    float dt = ofGetLastFrameTime();
    th += dt;
    emitter1.gen.emmiterPosUpd(emitter1.position, 1, th);
    emitter1.gen.setter(pS, vS, ml, mL, pColor, up);
    emitter1.update(th);

    sph.setSize(sizep);
    emitter1.gen.setUp(up);

}

void ofApp::draw() {
    ofBackground(bg);
    
    cam.begin();
    ofEnableDepthTest();

    light.enable();
    grid(40, 50);
    emitter1.draw();
    sph.draws(sizep);
    
    light.disable();
    ofDisableDepthTest();
    cam.end();
    
    ofSetColor(255);
    gui.draw();
}

void ofApp::exit() {
    ml.removeListener(this, &ofApp::mlChanged);
    mL.removeListener(this, &ofApp::mLChanged);
}