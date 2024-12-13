#pragma once

#include "ofMain.h"

class particle {
public:
    ofVec3f position;
    ofVec3f velocity;
    float size;
    int col;
    int lifeTime;
    bool isAlive;

    particle() : position(0, 0, 0), velocity(0, 0, 0), size(1.0f), isAlive(false), lifeTime(100) {}

    void update() {
        if (isAlive) {
            lifeTime -= 1;
            position += velocity;
            size *= 0.95f;  // Czasteczki stopniowo zmieniają rozmiar
            kill();
            wake();
        }
    }

    void draw() {
        if (isAlive) {
            ofSetColor(255, 55, 155);
            ofDrawSphere(position, size);
        }
    }

    void wake() {
        if (!isAlive) {
            reset(position);
            reset(velocity);
            size = 1.0f;
            lifeTime = 10;
            isAlive = true;
        }
    }
    
    void kill() {
        if (lifeTime < 0) {
            isAlive = false;
        }
    }

    void reset(const ofVec3f& pos) {
        position = pos;
        velocity.set(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
        size = ofRandom(5, 10);
        isAlive = true;
    }
};
