#pragma once

#include "ofMain.h"
#include "emitter.h"

class ofApp : public ofBaseApp {
public:
    emitter emitter1;
    ofLight light;

    void setup();
    void update();
    void draw();
};
