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

    ofSetColor(0);

    // USTAW KAMERE
    cam.setNearClip(0.1f);
    cam.setFarClip(10000.0f);
    cam.setPosition(0, 500, 1000);
    cam.lookAt(ofVec3f(0, 300, 0));

    // USTAW EMITER CHOINKA
    emitter1.setup(2000);
    emitter1.position.set(0, 300, 0);
    e1.setup(2000);
    e1.position.set(0, 300, 0);
    e2.setup(2000);
    e2.position.set(0, 300, 0);
    e3.setup(2000);
    e3.position.set(0, 300, 0);

    red.setup(2000);
    red.position.set(0, 300, 0);

    baub.setup(100);
    baub.emissionRate = 0.5;
    baub.position.set(0, 300, 0);
    
    // USTAW EMITTER ŚNIEG
    emitter2.setup(2000);
    emitter2.position.set(0, 1000, 0);

    snow.setup(6000);
    snow.emissionRate = 6000;
    snow.position.set(0, 0, 0);
    snow.gen.setter(50, 20, 20000, 20000, ofColor(255), true);
    snow.gen.emmiterPosUpd(snow.position, 1, 1);
    snow.update(1, 0);

    // USTAW SWIATLO
    light.setPosition(cam.getPosition() + ofVec3f(0, 0, 20));
    light.setDiffuseColor(ofColor(255, 255, 255));
    light.setSpecularColor(ofColor(255, 255, 255));
    ofSetSmoothLighting(true);
}

ofVec3f vec(0, 500, 1000);
float th = 0;
float ex = 0;
void ofApp::update() {
    float dt = ofGetLastFrameTime();
    th += dt;
    ex += 0.05;
    
    vec.x = 1000 * sin(th/2);
    vec.z = 1000 * cos(th/2);
    cam.setPosition(vec);
    cam.lookAt(ofVec3f(0, 300, 0));

    emitter1.gen.emmiterPosUpd(emitter1.position, 3, th/10, emitter1.spiral(150, 600, 5, 0), emitter1.gen.index);
    emitter1.gen.index += ex;
    emitter1.gen.setter(6, 2, 550, 650, ofColor(50, 220, 20), true);
    emitter1.update(th, 1);

    e1.gen.emmiterPosUpd(e1.position, 3, th / 10, e1.spiral(150, 600, 5, PI/2), e1.gen.index);
    e1.gen.index += ex;
    e1.gen.setter(6, 2, 550, 650, ofColor(50, 200, 20), true);
    e1.update(th, 1);

    e2.gen.emmiterPosUpd(e2.position, 3, th / 10, e2.spiral(150, 600, 5, PI), e2.gen.index);
    e2.gen.index += ex;
    e2.gen.setter(6, 2, 550, 650, ofColor(50, 180, 20), true);
    e2.update(th, 1);

    e3.gen.emmiterPosUpd(e3.position, 3, th / 10, e3.spiral(150, 600, 5, 3*PI/2), e3.gen.index);
    e3.gen.index += ex;
    e3.gen.setter(6, 2, 550, 650, ofColor(50, 200, 20), true);
    e3.update(th, 1);

    if (th > 8) {
        red.gen.emmiterPosUpd(red.position, 3, th / 10, red.spiral(150, 600, 5, 3 * PI / 3), red.gen.index);
        red.gen.index += ex+1;
        red.gen.setter(12, 5, 550, 650, ofColor(ofRandom(150, 240), 20, 20), true);
        red.update(th, 1);
        
        baub.gen.emmiterPosUpd(baub.position, 3, th / 10, baub.spiral(150, 600, 5, 3 * PI / 2), baub.gen.index);
        baub.gen.index += ex * 5;
        baub.gen.setter(20, 5, 20, 30, ofColor::fromHsb(ofRandom(0, 255), 255, 255), true);
        baub.update(th, 1);
    }

    emitter2.gen.setter(3, 2, 500, 600, ofColor::white, false);
    emitter2.update(th, 0);

}

void ofApp::draw() {
    ofBackground(ofColor(10,0,30));
    cam.begin();
    ofEnableDepthTest();
    light.enable();
    grid(40, 50);

    emitter1.draw();
    emitter2.draw();
    e1.draw();
    e2.draw();
    e3.draw();
    red.draw();
    baub.draw();
    snow.draw();

    light.disable();
    ofDisableDepthTest();
    cam.end();
    
}

void ofApp::exit() {
}