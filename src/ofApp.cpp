#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    emitter1.setup(1000);  // Zainicjalizowanie emitera z maksymalną liczbą cząsteczek
    emitter1.position.set(ofGetWidth() / 2, ofGetHeight() / 2, 0);  // Ustawienie pozycji emitera na środek ekranu
    light.setPosition(ofVec3f(300, 300, 300));  // Ustawienie pozycji światła
    light.setDiffuseColor(ofColor(255, 255, 155)); // Kolor światła
    light.setSpecularColor(ofColor(155, 255, 255)); // Kolor połysku
    ofSetSmoothLighting(true);

}
float th = 0;
void ofApp::update() {
    float dt = ofGetLastFrameTime();
    th += dt;
    emitter1.update(dt);  // Zaktualizowanie emitera
    emitter1.position.x += 2*cos(th);
    emitter1.position.y += 2*sin(th);
}

void ofApp::draw() {
    ofBackground(155);
    light.enable();
    emitter1.draw();  // Rysowanie cząsteczek
    light.disable();
}
