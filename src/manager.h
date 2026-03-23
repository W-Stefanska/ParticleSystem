#pragma once

class Manager {
private:
	ofxPanel listPanel;
	ofxPanel settingsPanel;
	ofxPanel scenePanel;

	Emitter*	selectedEmitter		= nullptr;
	Collider*	selectedCollider	= nullptr;
public:
	void setup() {
		listPanel.setup("Objects", "", 20, 20);
		settingsPanel.setup("Settings", "", ofGetWidth() - 220, 20);
		scenePanel.setup("Scene", "", 20, listPanel.getHeight() + 20);
	}

	void update(Emitter* e) {
		selectedEmitter = e;
		selectedCollider = nullptr;

		settingsPanel.clear();
		if (e) e->drawSettings(settingsPanel);
	}

	void update(Collider* c) {
		selectedCollider = c;
		selectedEmitter = nullptr;
	
		settingsPanel.clear();
		if (c) c->drawSettings(settingsPanel);
	}
	
	void draw() {
		ofDisableLighting();
		ofSetColor(255);
		
		listPanel.draw();
		settingsPanel.draw();
		scenePanel.draw();
	}
};