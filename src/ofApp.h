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
	Manager manager;
	Scene scene;

	std::vector<std::unique_ptr<Emitter>> emitters;
	std::vector<std::unique_ptr<Collider>> colliders;

    void setup();
    void update();
    void draw();
    void exit();
};