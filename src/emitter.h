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
    int index = 0;
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

    ofVec3f generatePosition(const ofVec3f& emitterPosition, double scale) {
        return emitterPosition + ofVec3f(ofRandom(-10*scale, 10*scale), ofRandom(-10, 10), ofRandom(-10*scale, 10*scale));
    }

    ofVec3f generatePosition(const ofVec3f& emitterPosition, int x, int y, int z) {
        return emitterPosition + ofVec3f(ofRandom(-x, x), ofRandom(-y, y), ofRandom(-z, z));
    }

    ofVec3f generateVelocity() {
        return (up ? ofVec3f(ofRandom(-0, 0), ofRandom(0, 0), ofRandom(-0, 0)) : ofVec3f(ofRandom(-1, 1), ofRandom(-2, 0), ofRandom(-1, 1)));
    }

    int emmiterPosUpd(ofVec3f& eP, int type, float dt, std::vector<ofVec3f> vec, int& index) {
        switch (type) {
        case 1: 
            eP.x += 2*sin(dt);
            break;
        case 2:
            eP.x += 2*sin(dt);
            eP.y += 2*cos(dt);
            std::cout << "Done";
            break;
        case 3:
            if (!vec.empty()) {
                index = (index + 1) % vec.size();
                eP = vec[index];
            }
            break;
        }
        return index;
    }

    void emmiterPosUpd(ofVec3f& eP, int type, float dt) {
        switch (type) {
        case 1:
            eP.x += 2 * sin(dt);
            break;
        case 2:
            eP.x += 2 * sin(dt);
            eP.y += 2 * cos(dt);
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

    emitter() : position(0, 0, 0), emissionRate(1.0f), timeSinceLastEmission(0) {}
    
    void setER(float er) {
        emissionRate = er;
    }

    void update(float dt, int ctrl) {
        timeSinceLastEmission += dt;

        while (timeSinceLastEmission >= 1.0f / emissionRate) {
            bool emitted = false;
            for (auto& p : particles) {
                if (!p.isAlive) {
                    ctrl == 1 ? p.reset(gen.generatePosition(position, 0.5), gen.generateColor()) : p.reset(gen.generatePosition(position, 200), gen.generateColor());
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

    std::vector<ofVec3f> spiral(float baseRadius, int height, int turns, float start) {
        std::vector<ofVec3f> points;
        float n = 1000;

        float angleIncrement = 2 * PI * turns / n;
        float heightIncrement = height / n;
        float radiusDecrement = baseRadius / n;

        float theta = start;
        float r = baseRadius;
        float y = 0.0f;

        for (int i = 0; i <= n; ++i) {

            float x = r * std::cos(theta);
            float z = r * std::sin(theta);
            points.emplace_back(x, y, z);

            theta += angleIncrement;
            y += heightIncrement;
            r -= radiusDecrement;
            if (r < 0) r = 0;
        }
        return points;
    }
};