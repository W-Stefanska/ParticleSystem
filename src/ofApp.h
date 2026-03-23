#pragma once

#include "ofMain.h"
#include "ofxPanel.h"
#include <ofxSliderGroup.h>
#include "emitter.h"
#include "collider.h"
#include "manager.h"
#include "scene.h"

class ofApp : public ofBaseApp {
public:
    int blockMin;
    int blockMax;

	Manager manager;
	Scene scene;

    void setup();
    void update();
    void draw();
    void exit();
};