#pragma once

#include "ofMain.h"
#include "emitter.h"
#include "ofxPanel.h"
#include <ofxSliderGroup.h>

class ofApp : public ofBaseApp {
public:
    int blockMin;
    int blockMax;

    ofEasyCam cam;

    emitter emitter1;
    emitter emitter2;
    emitter e1;
    emitter e2;
    emitter e3;
    emitter red;
    emitter baub;
    emitter snow;
    ofLight light;
    ofColor bg;

    ofxPanel gui;
    ofxIntSlider sizep;
    ofxFloatSlider pS;
    ofxFloatSlider vS;
    ofxIntSlider ml;
    ofxIntSlider mL;
    ofxToggle up;
    ofxToggle wind;
    ofxToggle gravity;
    ofxColorSlider pColor;
    ofParameterGroup params;
    sphere sp;    
    sphere sph;
    ofApp() : sp(100, ofColor(100, 100, 255, 50)), sph(100, ofColor(255, 100, 255, 255)) {}

    void mlChanged(int &val);
    void mLChanged(int &val);

    void setup();
    void update();
    void draw();
    void exit();
};