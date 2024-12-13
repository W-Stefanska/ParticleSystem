#pragma once

#include "particle.h"

class emitter {
public:
    ofVec3f position;
    float emissionRate;
    float timeSinceLastEmission;
    std::vector<particle> particles;

    emitter() : position(0, 0, 0), emissionRate(10.0f), timeSinceLastEmission(0) {}
    
    void update(float dt) {
        timeSinceLastEmission += dt;

        // Emisja cząsteczek
        while (timeSinceLastEmission >= 1.0f / emissionRate) {
            for (auto& p : particles) {
                if (!p.isAlive) {
                    p.reset(position);
                    break;
                }
            }
            timeSinceLastEmission -= 1.0f / emissionRate;
        }

        // Aktualizacja cząsteczek
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
    }
};
