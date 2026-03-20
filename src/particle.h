#pragma once

#include "ofMain.h"

class Particle {
public:
    ofVec3f position;
    ofVec3f velocity;
    float   size;
    float   lifetime;
    bool    isAlive;
    ofColor col;

    Particle() : position(0, 0, 0), velocity(0, 0, 0), size(1.0f), isAlive(false), lifetime(100) {}

    void update(double dt) {
        if (isAlive) {
            lifetime -= 1;
            position += velocity;
            float lifeRatio = static_cast<float>(lifetime) / 100.0f;
            //size = 5.0f + 3.0f * sin(lifeRatio * TWO_PI);
            size += 0.1;
            kill();
        }
    }

    void draw() {
        if (isAlive) {
            ofMaterial mat;
            mat.setDiffuseColor(col);
            mat.setSpecularColor(ofColor(255, 255, 255));
            mat.setShininess(120);
            mat.begin();
            ofDrawSphere(position, size);
            mat.end();
        }
    }

    void wake() {
        if (!isAlive) {
            position = ofVec3f(0, 0, 0);
            velocity = ofVec3f(0, 0, 0);
            size = 1.0f;
            lifetime = 10;
            isAlive = true;
        }
    }
    
    void kill() {
        if (lifetime < 0) {
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

    void bounce(std::vector<Particle>& particles) const {
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
        ofMaterial mat;
        mat.setDiffuseColor(color);
        mat.setSpecularColor(ofColor(255, 255, 255));
        mat.setShininess(120);
        mat.begin();
        ofDrawSphere(pos, size);
        mat.end();
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