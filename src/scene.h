#pragma once

class Scene {
private:
	ofEasyCam	camera;
	ofLight		light;
	ofColor		background;

	ofColor 	gridColor;
	bool		showGrid = true;
	bool		showOnlyFlatGrid = true;

	void drawGrid() {
		
	}
public:
	void setup() {
		background = ofColor::aliceBlue;
		
		cameraSetup();
		lightSetup();	

		ofSetSmoothLighting(true);
	}
	void cameraSetup() {
		camera.setNearClip(0.1f);
		camera.setFarClip(10000.0f);
		camera.setPosition(0, 0, 1000);
		camera.lookAt(ofVec3f(0, 0, 0));
	}
	void lightSetup() {
		light.setPosition(camera.getPosition() + ofVec3f(200, 400, 200));
		light.setDiffuseColor(ofColor(255, 235, 200));
		light.setSpecularColor(ofColor(255, 255, 255));
		light.setAmbientColor(ofColor(100, 100, 255));
	}
	
	void begin() {
		ofBackground(background);
		camera.begin();
		ofEnableDepthTest();
		light.enable();
	}
	void end() {
		light.disable();
		ofDisableDepthTest();
		camera.end();
	}
	ofEasyCam* getCamera() {
		return &camera;
	}
};