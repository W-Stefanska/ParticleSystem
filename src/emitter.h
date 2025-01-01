#pragma once

#include "particle.h"

class pG {
private:
    float parSize = 10;
    float varSize = 5;
    float minLife = 100;
    float maxLife = 200;
    bool up = true;
    ofColor color = ofColor(0, 0, 0);
public:
    // Settery
    void setParSize(float x) { parSize = x; };
    void setVarSize(float x) { varSize = x; };
    void setMinLife(float x) { minLife = x; };
    void setMaxLife(float x) { maxLife = x; };
    void setColor(ofColor x) { color = x; };
    void setUp(bool x) { up = x; };
    void setter(float pS, float vS, float ml, float mL, ofColor c, bool sU) {
        parSize = pS;
        varSize = vS;
        minLife = ml;
        maxLife = mL;
        color = c;
        up = sU;
    }

    ofVec3f generatePosition(const ofVec3f& emitterPosition) {
        return emitterPosition + ofVec3f(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10));
    }

    ofVec3f generateVelocity() {
        return (up ? ofVec3f(ofRandom(-1, 1), ofRandom(0, 2), ofRandom(-1, 1)) : ofVec3f(ofRandom(-1, 1), ofRandom(-2, 0), ofRandom(-1, 1)));
    }

    void emmiterPosUpd(ofVec3f& eP, int type, float dt) {
        switch (type) {
        case 1: 
            eP.x += 2*sin(dt);
            break;
        case 2:
            eP.x += 2*sin(dt);
            eP.y += 2*cos(dt);
            std::cout << "Done";
            break;
        }
    }
    
    float calculateLowestSize() { return (parSize - varSize > 0) ? parSize - varSize : 1; }
    float generateSize() {
        return ofRandom(calculateLowestSize(), parSize + varSize);
    }

    int generateLifeTime() {
        return ofRandom(minLife, maxLife);
    }

    ofColor generateColor() {
        return ofColor(color);
    }
};

class emitter {
public:
    ofVec3f position;
    float emissionRate;
    float timeSinceLastEmission;
    std::vector<particle> particles;
    pG gen;

    emitter() : position(0, 0, 0), emissionRate(2.0f), timeSinceLastEmission(0) {}
    
    void update(float dt) {
        timeSinceLastEmission += dt;

        while (timeSinceLastEmission >= 1.0f / emissionRate) {
            bool emitted = false;
            for (auto& p : particles) {
                if (!p.isAlive) {
                    p.reset(gen.generatePosition(position), gen.generateColor());
                    p.velocity = gen.generateVelocity();
                    p.size = gen.generateSize();
                    p.lifeTime = gen.generateLifeTime();
                    p.col = gen.generateColor();
                    emitted = true;
                    break;
                }
            }
            if (!emitted) break;
            timeSinceLastEmission -= 1.0f / emissionRate;
        }

        for (auto& p : particles) {
            p.update();
        }

    }


    void draw() {
        for (auto& p : particles) {
            p.draw();
        }
    }

    void setup(int maxParticles) {
        particles.resize(maxParticles);
        for (auto& p : particles) {
            p.isAlive = false;
        }
    }

    void wind(bool isWind) {
        if (isWind) {
            for (auto& p : particles) {
                p.velocity += ofVec3f(10, 0, 0);
            }
        }
    }
    
    void gravity(bool isGravity) {
        if (isGravity) {
            for (auto& p : particles) {
                p.velocity += ofVec3f(0, -1, 0);
            }
        }
    }
    
    particle access(int i) {
        return particles[i];
    }


};

