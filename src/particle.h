#pragma once

#include "ofMain.h"

class particle {
public:
    ofVec3f position;
    ofVec3f velocity;
    float size;
    ofColor col;
    int lifeTime;
    bool isAlive;

    particle() : position(0, 0, 0), velocity(0, 0, 0), size(1.0f), isAlive(false), lifeTime(100) {}

    void update() {
        if (isAlive) {
            lifeTime -= 1;
            position += velocity;
            float lifeRatio = static_cast<float>(lifeTime) / 100.0f;
            //size = 5.0f + 3.0f * sin(lifeRatio * TWO_PI);
            
            kill();
        }
    }

    void draw() {
        if (isAlive) {
            ofSetColor(col);
            ofDrawSphere(position, size);
        }
    }

    void wake() {
        if (!isAlive) {
            position = ofVec3f(0, 0, 0);
            velocity = ofVec3f(0, 0, 0);
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

    void reset(const ofVec3f& pos, ofColor color) {
        position = pos;
        ofSetColor(color);
        isAlive = true;
    }
};

class sphere {
public:
    int size;
    ofVec3f pos;
    ofColor color;

    sphere(int s, ofColor c) : size(s), pos(ofVec3f(0, s, 0)), color(c) {}

    bool check(ofVec3f ppos) const {
        float distance = ppos.distance(pos);
        return (distance >= size) || (distance <= size);
    }

    void bounce(std::vector<particle>& particles) const {
        for (auto& p : particles) {
            if (check(p.position)) {
                ofVec3f r = p.position - pos;

                float distance = r.length();

                if (distance < (size + p.size)) {
                    ofVec3f normal = r.normalize();

                    p.velocity = p.velocity - 2.0f * normal.dot(p.velocity) * normal;

                    float overlap = (size + p.size) - distance;
                    p.position += normal * overlap;
                }
            }
        }
    }

    void draw() const {
        ofSetColor(color);
        ofDrawSphere(pos, size);
    }

    void draws(int size) {
        ofSetColor(color);
        ofDrawSphere(pos, size);
    }

    void setSize(int newSize) {
        ofSetColor(color);
        ofDrawSphere(pos, newSize);
    }
};