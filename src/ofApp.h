#pragma once

#include "ofMain.h"
#include "ofxPanel.h"
#include <ofxSliderGroup.h>
#include "emitter.h"
#include "collider.h"

class ofApp : public ofBaseApp {
public:
    int blockMin;
    int blockMax;

    ofEasyCam cam;
    ofLight light;
    ofColor bg;

    void setup();
    void update();
    void draw();
    void exit();
};